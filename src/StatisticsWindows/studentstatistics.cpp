#include "studentstatistics.h"
#include "ui_studentstatistics.h"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QFile>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTableView>
#include <QValueAxis>

StudentStatisticsWindow::StudentStatisticsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentStatisticsWindow)
{
    ui->setupUi(this);

    setWindowTitle("Статистика студента");

    set0 = new QBarSet("Незадовільно");
    set1 = new QBarSet("Задовільно");
    set2 = new QBarSet("Добре");
    set3 = new QBarSet("Відмінно");
    clearChartSets();

    series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Кількість оцінок за рік");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(450);
    chartView = new QChartView(chart);

    QStringList categories;
    categories << "Січень"
               << "Лютий"
               << "Березень"
               << "Квітень"
               << "Травень"
               << "Червень"
               << "Липень"
               << "Серпень"
               << "Вересень"
               << "Жовтень"
               << "Листопад"
               << "Грудень";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTickCount(5);
    axisY->setLabelFormat("%.0f");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    chart->axes(Qt::Vertical).first()->setRange(0, 30);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->specialChart->addWidget(chartView);
}

StudentStatisticsWindow::~StudentStatisticsWindow()
{
    delete ui;
}

void StudentStatisticsWindow::setBlackUI()
{
    QFile file(":/styles/black/StatisticsWindows/StatisticsWindows.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeDark);
    chartView->chart()->setBackgroundBrush(QColor(49, 51, 52));

    set0->setColor(QColor(255, 95, 95));
    set1->setColor(QColor(254, 202, 100));
    set2->setColor(QColor(28, 211, 163));
    set3->setColor(QColor(136, 91, 255));
}

void StudentStatisticsWindow::setWhiteUI()
{
    QFile file(":/styles/white/StatisticsWindows/StatisticsWindows.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeLight);
    chartView->chart()->setBackgroundBrush(QColor(255, 255, 255));

    set0->setColor(QColor(255, 102, 152));
    set1->setColor(QColor(245, 179, 67));
    set2->setColor(QColor(40, 208, 71));
    set3->setColor(QColor(170, 114, 192));
}

void StudentStatisticsWindow::setSystemUI()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(),
                                      1 - baseColor.greenF(),
                                      1 - baseColor.blueF());

    if (newBase.name() == "#000000") {
        setWhiteUI();
    } else {
        setBlackUI();
    }
}

void StudentStatisticsWindow::setTheme(const QString &style)
{
    if (style == "black") {
        setBlackUI();
    } else if (style == "white") {
        setWhiteUI();
    } else {
        setSystemUI();
    }
}

void StudentStatisticsWindow::updateGroupComboBox()
{
    QStringList groupList;
    QSqlQueryModel *virualQueryModel = new QSqlQueryModel();
    QTableView *virtualTable = new QTableView();

    virualQueryModel->setQuery("SELECT `Назва`"
                               "FROM `Групи`");

    virtualTable->setModel(virualQueryModel);

    for (int row = 0; row < virualQueryModel->rowCount(); ++row) {
        groupList.append(virtualTable->model()->index(row, 0).data().toString());
    }

    ui->groupComboBox->clear();
    ui->groupComboBox->addItem("Оберіть групу", 0);
    ui->groupComboBox->insertSeparator(1);
    ui->groupComboBox->addItems(groupList);
}

void StudentStatisticsWindow::on_groupComboBox_currentIndexChanged(int index)
{
    clearChartSets();
    chart->setTitle("Кількість оцінок за рік");

    if (index == 0) {
        ui->studentComboBox->setEnabled(false);
        ui->studentComboBox->clear();
        ui->studentComboBox->addItem("Студенти групи відсутні", 0);
    } else {
        ui->studentComboBox->setEnabled(true);

        QStringList studentList;
        QSqlQueryModel *virualQueryModel = new QSqlQueryModel();
        QTableView *virtualTable = new QTableView();

        virualQueryModel->setQuery("SELECT `Прізвище`, `Ім'я`, `По батькові`"
                                   "FROM `Студенти`"
                                   "WHERE `Студенти`.`Група` = '"
                                   + ui->groupComboBox->currentText() + "'");

        virtualTable->setModel(virualQueryModel);

        if (virualQueryModel->rowCount() > 0) {
            for (int row = 0; row < virualQueryModel->rowCount(); ++row) {
                studentList.append(virtualTable->model()->index(row, 0).data().toString() + " "
                                   + virtualTable->model()->index(row, 1).data().toString() + " "
                                   + virtualTable->model()->index(row, 2).data().toString());
            }

            ui->studentComboBox->clear();
            ui->studentComboBox->addItem("Оберіть студента", 0);
            ui->studentComboBox->insertSeparator(1);
            ui->studentComboBox->addItems(studentList);
        } else {
            ui->studentComboBox->clear();
            ui->studentComboBox->addItem("Студенти групи відсутні", 0);
        }

        virualQueryModel->setQuery("SELECT `Рік початку навчання`, `Рік закінчення навчання`"
                                   "FROM `Групи`"
                                   "WHERE `Групи`.`Назва` = '"
                                   + ui->groupComboBox->currentText() + "'");

        virtualTable->setModel(virualQueryModel);

        ui->yearSpinBox->setMinimum(virtualTable->model()->index(0, 0).data().toInt());
        ui->yearSpinBox->setValue(virtualTable->model()->index(0, 0).data().toInt());
        ui->yearSpinBox->setMaximum(virtualTable->model()->index(0, 1).data().toInt());
    }

    setWindowTitle("Статистика студента");
}

void StudentStatisticsWindow::on_studentComboBox_currentIndexChanged(int index)
{
    if (index == 0) {
        clearChartSets();
        ui->nameLabel->setText("Статистика за:");
        setWindowTitle("Статистика студента");
    } else if (index > 0) {
        setCurrentChart();
    }
}

void StudentStatisticsWindow::clearChartSets()
{
    set0->remove(0, set0->count());
    set1->remove(0, set1->count());
    set2->remove(0, set2->count());
    set3->remove(0, set3->count());
}

void StudentStatisticsWindow::setCurrentChart()
{
    clearChartSets();

    ui->nameLabel->setText("Статистика за: " + ui->studentComboBox->currentText() + " ["
                           + ui->groupComboBox->currentText() + "]");
    setWindowTitle("Статистика " + ui->studentComboBox->currentText());

    QSqlQueryModel *virualQueryModel = new QSqlQueryModel(this);
    QTableView *virtualTable = new QTableView(this);

    virualQueryModel->setQuery("SELECT `Оцінка`, MONTH(`Дата виставлення`)"
                               "FROM `Оцінки`"
                               "WHERE `Оцінки`.`Отримувач` = '"
                               + ui->studentComboBox->currentText()
                               + "'"
                                 " AND YEAR(`Дата виставлення`) = '"
                               + QString::number(ui->yearSpinBox->value()) + "'");
    virtualTable->setModel(virualQueryModel);

    int maxCount = 0;

    for (int i = 0; i < 12; ++i) {
        int sum0 = 0;
        int sum1 = 0;
        int sum2 = 0;
        int sum3 = 0;

        for (int j = 0; j < virualQueryModel->rowCount(); ++j) {
            if (virtualTable->model()->index(j, 0).data().toInt() == 2
                and (virtualTable->model()->index(j, 1).data().toInt() - 1) == i) {
                sum0++;

                if (sum0 > maxCount) {
                    maxCount = sum0;
                }
            } else if (virtualTable->model()->index(j, 0).data().toInt() == 3
                       and (virtualTable->model()->index(j, 1).data().toInt() - 1) == i) {
                sum1++;

                if (sum1 > maxCount) {
                    maxCount = sum1;
                }
            } else if (virtualTable->model()->index(j, 0).data().toInt() == 4
                       and (virtualTable->model()->index(j, 1).data().toInt() - 1) == i) {
                sum2++;

                if (sum2 > maxCount) {
                    maxCount = sum2;
                }
            } else if (virtualTable->model()->index(j, 0).data().toInt() == 5
                       and (virtualTable->model()->index(j, 1).data().toInt() - 1) == i) {
                sum3++;

                if (sum3 > maxCount) {
                    maxCount = sum3;
                }
            }
        }
        *set0 << sum0;
        *set1 << sum1;
        *set2 << sum2;
        *set3 << sum3;
    }

    virualQueryModel->setQuery("SELECT MAX(`Оцінка`)"
                               "FROM `Оцінки`"
                               "WHERE `Оцінки`.`Отримувач` = '"
                               + ui->studentComboBox->currentText()
                               + "'"
                                 " AND  YEAR(`Дата виставлення`) = '"
                               + QString::number(ui->yearSpinBox->value()) + "'");
    virtualTable->setModel(virualQueryModel);
    chart->axes(Qt::Vertical).first()->setRange(0, maxCount + 1);
    chart->setTitle("Кількість оцінок за " + QString::number(ui->yearSpinBox->value()) + " рік");
}

void StudentStatisticsWindow::on_yearSpinBox_valueChanged(int arg1)
{
    if (ui->studentComboBox->currentIndex() > 0) {
        setCurrentChart();
    }
}
