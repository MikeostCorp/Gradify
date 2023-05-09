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

studentStatistics::studentStatistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentStatistics)
{
    ui->setupUi(this);
    setWindowTitle("Статистика студента");

    QBarSet *set0 = new QBarSet("Jane");
    QBarSet *set1 = new QBarSet("John");
    QBarSet *set2 = new QBarSet("Axel");
    QBarSet *set3 = new QBarSet("Mary");
    QBarSet *set4 = new QBarSet("Samantha");

    set0->setColor(QColor(70, 0, 255));
    set1->setColor(QColor(136, 91, 255));
    set2->setColor(QColor(254, 202, 100));
    set3->setColor(QColor(255, 95, 95));
    set4->setColor(QColor(1, 209, 255));

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(450);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,15);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

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
}


void studentStatistics::setWhiteUI()
{
    QFile file(":/styles/white/statisticsForms/statisticsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeLight);
    chartView->chart()->setBackgroundBrush(QColor (255, 255, 255));
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
    }
    else
    {
        ui->nameLabel->setText("Статистика за: " + ui->studentComboBox->currentText()
                               + " [" + ui->groupComboBox->currentText() + "]");
        setWindowTitle("Статистика " + ui->studentComboBox->currentText());
    }
}


