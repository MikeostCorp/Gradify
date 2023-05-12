#include "subjectstatistics.h"
#include "ui_subjectstatistics.h"

#include <QFile>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QChartView>
#include <QValueAxis>
#include <QBarCategoryAxis>

subjectStatistics::subjectStatistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subjectStatistics)
{
    ui->setupUi(this);
    setWindowTitle("Статистика предметів по типам");

    series = new QPieSeries();

    chart = new QChart();
    chart->addSeries(series);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTitle("Статистика предметів по типам");

    chart->legend()->setVisible(true);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(450);

    ui->specialChart->addWidget(chartView);
}


subjectStatistics::~subjectStatistics()
{
    delete ui;
}

void subjectStatistics::closeEvent(QCloseEvent *event)
{
    if (event->Close)
    {
        series->clear();
    }
}

void subjectStatistics::fillChart()
{
    QSqlQueryModel *virtualQueryModel = new QSqlQueryModel();
    QTableView *virtualTableView = new QTableView();

    virtualQueryModel->setQuery("SELECT `Предмети`.`Тип`, COUNT(*)"
                                "FROM `Предмети`"
                                "GROUP BY(`Предмети`.`Тип`);");

    virtualTableView->setModel(virtualQueryModel);

    for (int row = 0; row < virtualTableView->model()->rowCount(); ++row)
    {
        series->append(virtualTableView->model()->index(row, 0).data().toString(),
                       virtualTableView->model()->index(row, 1).data().toInt());
    }
    series->setLabelsVisible(true);
}

void subjectStatistics::setBlackUI()
{
    QFile file(":/styles/black/statisticsForms/statisticsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeDark);
    chartView->chart()->setBackgroundBrush(QColor(49, 51, 52));
}


void subjectStatistics::setWhiteUI()
{
    QFile file(":/styles/white/statisticsForms/statisticsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeLight);
    chartView->chart()->setBackgroundBrush(QColor(255, 255, 255));
}


void subjectStatistics::setSystemUI()
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


void subjectStatistics::setTheme(const QString &style)
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
