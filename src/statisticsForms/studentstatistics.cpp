#include "studentstatistics.h"
#include "ui_studentstatistics.h"

#include <QFile>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QChartView>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QSqlQueryModel>
#include <QTableView>
#include <QMessageBox>

studentStatistics::studentStatistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentStatistics)
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
    chart->setTitle("");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(450);
    chartView = new QChartView(chart);


    QStringList categories;
    categories << "Вересень" << "Жовтень" << "Листопад"
               << "Грудень" << "Січень" << "Лютий"
               << "Березень" << "Квітень" << "Травень"
               << "Червень"  << "Липень"  << "Серпень";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    chart->axes(Qt::Vertical).first()->setRange(0, 30);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->specialChart->addWidget(chartView);


    /*
    QPieSeries *series1 = new QPieSeries();
    series1->append("Jane", 1);
    series1->append("Joe", 2);
    series1->append("Andy", 3);
    series1->append("Barbara", 4);
    series1->append("Axel", 5);

    QChart *charts = new QChart();
    charts->addSeries(series1);

    QChartView *chartView1 = new QChartView(charts);
    //chartView->setBackgroundBrush(Qt::red);
    chartView1->setRenderHint(QPainter::Antialiasing);
    //ui->specialChart_2->addWidget(chartView1);

    //setCentralWidget(chartView1);
    */
}


studentStatistics::~studentStatistics()
{
    delete ui;
}


void studentStatistics::setBlackUI()
{
    QFile file(":/styles/black/statisticsForms/statisticsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeDark);
    chartView->chart()->setBackgroundBrush(QColor (49, 51, 52));

    set0->setColor(QColor(255, 95, 95));
    set1->setColor(QColor(254, 202, 100));
    set2->setColor(QColor(28, 211, 163));
    set3->setColor(QColor(136, 91, 255));
}


void studentStatistics::setWhiteUI()
{
    QFile file(":/styles/white/statisticsForms/statisticsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeLight);
    chartView->chart()->setBackgroundBrush(QColor (255, 255, 255));

    set0->setColor(QColor(255, 102, 152));
    set1->setColor(QColor(245, 179, 67));
    set2->setColor(QColor(40, 208, 71));
    set3->setColor(QColor(170, 114, 192));
}


void studentStatistics::setSystemUI()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(), 1 - baseColor.greenF(), 1 - baseColor.blueF());

    if (newBase.name() == "#000000")
    {
        setWhiteUI();
    }
    else
    {
        setBlackUI();
    }
}


void studentStatistics::setTheme(const QString &style)
{
    if (style == "black")
    {
        setBlackUI();
    }
    else if (style == "white")
    {
        setWhiteUI();
    }
    else
    {
        setSystemUI();
    }
}


void studentStatistics::updateGroupComboBox()
{
    QStringList groupList;
    QSqlQueryModel *virualQueryModel = new QSqlQueryModel();
    QTableView *virtualTable = new QTableView();

    virualQueryModel->setQuery("SELECT `Назва`"
                               "FROM `Групи`");

    virtualTable->setModel(virualQueryModel);

    for (int row = 0; row < virualQueryModel->rowCount(); ++row)
    {
        groupList.append(virtualTable->model()->index(row, 0).data().toString());
    }

    ui->groupComboBox->clear();
    ui->groupComboBox->addItem("Оберіть групу", 0);
    ui->groupComboBox->insertSeparator(1);
    ui->groupComboBox->addItems(groupList);

}


void studentStatistics::on_groupComboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->studentComboBox->setEnabled(false);
        ui->studentComboBox->clear();
        ui->studentComboBox->addItem("Студенти групи відсутні", 0);

        clearChartSets();
    }
    else
    {
        ui->studentComboBox->setEnabled(true);

        QStringList studentList;
        QSqlQueryModel *virualQueryModel = new QSqlQueryModel();
        QTableView *virtualTable = new QTableView();

        virualQueryModel->setQuery("SELECT `Прізвище`, `Ім'я`, `По батькові`"
                                   "FROM `Студенти`"
                                   "WHERE `Студенти`.`Група` = '" + ui->groupComboBox->currentText() + "'");

        virtualTable->setModel(virualQueryModel);

        if (virualQueryModel->rowCount() > 0)
        {
            for (int row = 0; row < virualQueryModel->rowCount(); ++row)
            {
                studentList.append(virtualTable->model()->index(row, 0).data().toString() + " "
                                   + virtualTable->model()->index(row, 1).data().toString() + " "
                                   + virtualTable->model()->index(row, 2).data().toString());
            }

            ui->studentComboBox->clear();
            ui->studentComboBox->addItem("Оберіть студента", 0);
            ui->studentComboBox->insertSeparator(1);
            ui->studentComboBox->addItems(studentList);
        }
        else
        {
            ui->studentComboBox->clear();
            ui->studentComboBox->addItem("Студенти групи відсутні", 0);
        }
    }

    setWindowTitle("Статистика студента");
}


void studentStatistics::on_studentComboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->nameLabel->setText("Статистика за:");
        setWindowTitle("Статистика студента");
        clearChartSets();
    }
    else if (index > 0)
    {
        ui->nameLabel->setText("Статистика за: " + ui->studentComboBox->currentText()
                               + " [" + ui->groupComboBox->currentText() + "]");
        setWindowTitle("Статистика " + ui->studentComboBox->currentText());

        QSqlQueryModel *virualQueryModel = new QSqlQueryModel(this);
        QTableView *virtualTable = new QTableView(this);

        //virualQueryModel->setQuery("SELECT MONTH(`Дата виставлення`), СOUNT(`Оцінка`)"
        //                           " FROM `Оцінки`"
        //                           " WHERE `Оцінки`.`Отримувач` = '" + ui->studentComboBox->currentText() + "'"
        //                           " GROUP BY MONTH(`Дата виставлення`), `Оцінка`");


        virualQueryModel->setQuery("SELECT `Оцінка`, MONTH(`Дата виставлення`)"
                                   "FROM `Оцінки`"
                                   "WHERE `Оцінки`.`Отримувач` = '" + ui->studentComboBox->currentText() + "'");
        virtualTable->setModel(virualQueryModel);


        //ui->tableView->setModel(virualQueryModel);

        QVector<int> grades(12);

        int maxValue = 0;

        for (int i = 0; i < 12; ++i)
        {
            for (int j = 0; j < virualQueryModel->rowCount(); ++j)
            {
                if (virtualTable->model()->index(j, 0).data().toInt() == 2
                    and (virtualTable->model()->index(j, 1).data().toInt() + 1) == i)
                {

                }
            }
        }


        // for example
        *set0 << 15 << 5 << 0 << 0 << 10 << 15 << 0 << 0 << 0 << 6 << 0 << 0;
        *set1 << 8 << 2 << 7 << 0 << 0 << 0 << 40 << 0 << 2 << 0 << 0 << 0;
        *set2 << 5 << 3 << 5 << 0 << 0 << 30 << 0 << 5 << 0 << 2 << 0 << 0;
        *set3 << 7 << 3 << 0 << 26 << 0 << 23 << 0 << 0 << 4 << 0 << 0 << 12;

        maxValue = 40; // задавать за макисмальным количеством оценки
        chart->axes(Qt::Vertical).first()->setRange(0, maxValue +  2);


    }
}

void studentStatistics::clearChartSets()
{
    set0->remove(0 , 12);
    set1->remove(0 , 12);
    set2->remove(0 , 12);
    set3->remove(0 , 12);
}

