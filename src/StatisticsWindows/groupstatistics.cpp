#include "groupstatistics.h"
#include "ui_groupstatistics.h"

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

GroupStatisticsWindow::GroupStatisticsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GroupStatisticsWindow)
{
    ui->setupUi(this);

    setWindowTitle("Статистика групи");

    series = new QPieSeries();

    chart = new QChart();
    chart->addSeries(series);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chart->legend()->setVisible(true);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(450);

    ui->specialChart->addWidget(chartView);
    clearPieChart();
}

GroupStatisticsWindow::~GroupStatisticsWindow()
{
    delete ui;
}

void GroupStatisticsWindow::setBlackUI()
{
    QFile file(":/styles/black/StatisticsWindows/StatisticsWindows.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeDark);
    chartView->chart()->setBackgroundBrush(QColor(49, 51, 52));
}

void GroupStatisticsWindow::setWhiteUI()
{
    QFile file(":/styles/white/StatisticsWindows/StatisticsWindows.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeLight);
    chartView->chart()->setBackgroundBrush(QColor(255, 255, 255));
}

void GroupStatisticsWindow::setSystemUI()
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

void GroupStatisticsWindow::setTheme(const QString &style)
{
    if (style == "black") {
        setBlackUI();
    } else if (style == "white") {
        setWhiteUI();
    } else {
        setSystemUI();
    }
}

void GroupStatisticsWindow::setGroupComboBox()
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

void GroupStatisticsWindow::on_groupComboBox_currentIndexChanged(int index)
{
    clearPieChart();

    if (index > 0) {
        series->clear();

        QSqlQueryModel *virualQueryModel = new QSqlQueryModel();
        QTableView *virtualTable = new QTableView();

        virualQueryModel->setQuery("SELECT COUNT(*)"
                                   "FROM `Студенти`"
                                   "WHERE `Студенти`.`Група` = '"
                                   + ui->groupComboBox->currentText()
                                   + "'"
                                     "GROUP BY `Студенти`.`Група`");
        virtualTable->setModel(virualQueryModel);
        int countCurrentGroupStudent = virtualTable->model()->index(0, 0).data().toInt();

        virualQueryModel->setQuery("SELECT COUNT(*)"
                                   "FROM `Студенти`");
        virtualTable->setModel(virualQueryModel);
        int allCountStudent = virtualTable->model()->index(0, 0).data().toInt();

        if (allCountStudent not_eq 0 and countCurrentGroupStudent not_eq 0) {
            series->append("Кількість студентів інших груп ["
                               + QString::number(allCountStudent - countCurrentGroupStudent) + "]",
                           allCountStudent - countCurrentGroupStudent);

            series->append("Кількість студентів групи " + ui->groupComboBox->currentText() + "["
                               + QString::number(countCurrentGroupStudent) + "]",
                           countCurrentGroupStudent);
        } else if (allCountStudent not_eq 0) {
            series->append("Загальна кількість студентів", allCountStudent);
        }

        series->setLabelsVisible(true);
    }
}

void GroupStatisticsWindow::clearPieChart()
{
    setWindowTitle("Статистика груп");
    series->clear();
    series->append("Приклад", 1);
}
