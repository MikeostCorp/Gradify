#include "studentstatistics.h"
#include "ui_studentstatistics.h"

#include <QFile>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QChartView>
#include <QValueAxis>
#include <QBarCategoryAxis>

studentStatistics::studentStatistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentStatistics)
{
    ui->setupUi(this);
    setWindowTitle("Статистика студентів");

    QBarSet *set0 = new QBarSet("Jane");
    QBarSet *set1 = new QBarSet("John");
    QBarSet *set2 = new QBarSet("Axel");
    QBarSet *set3 = new QBarSet("Mary");
    QBarSet *set4 = new QBarSet("Samantha");




    set4->setSelectedColor(QColor(122,122,250));

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
    chart->setTitle("Тайтл текст");
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

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    //chartView->setBackgroundBrush(QBrush(QColor(76,76,241)));
    //chart->setBackgroundBrush(QBrush(Qt::darkGray));
    //chart->setTitleBrush(QBrush(QColor(228,121,121)));

    chartView->chart()->setTheme(QChart::ChartThemeDark);
    chartView->chart()->setBackgroundBrush(QColor (123,52, 234));
    //QChart::ChartThemeDark
    //QChart::ChartThemeLight

    ui->specialChart->addWidget(chartView);// -> add to window */



    /* Pie chart
     * QPieSeries *series1 = new QPieSeries();
    series1->append("Jane", 1);
    series1->append("Joe", 2);
    series1->append("Andy", 3);
    series1->append("Barbara", 4);
    series1->append("Axel", 5);

    QChart *charts = new QChart();
    charts->addSeries(series1);

    QChartView *chartView1 = new QChartView(charts);
    //chartView->setBackgroundBrush(Qt::red);
    chartView->setRenderHint(QPainter::Antialiasing); */

    //setCentralWidget(chartView1);


    //printer.setOutputFileName(path);

    //document->setPageSize(QSizeF(927, 1402.5));
    //document->print(&printer);

    //QDesktopServices::openUrl(QUrl("file://" + path, QUrl::TolerantMode));
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
}


void studentStatistics::setWhiteUI()
{
    QFile file(":/styles/white/statisticsForms/statisticsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
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
