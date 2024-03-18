#include "subjectstatistics.h"
#include "ui_subjectstatistics.h"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QFile>
#include <QValueAxis>

SubjectStatisticsWindow::SubjectStatisticsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SubjectStatisticsWindow)
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

SubjectStatisticsWindow::~SubjectStatisticsWindow()
{
    delete ui;
}

void SubjectStatisticsWindow::closeEvent(QCloseEvent *event)
{
    if (event->Close) {
        series->clear();
    }
}

void SubjectStatisticsWindow::fillChart()
{
    /*
    QSqlQueryModel *virtualQueryModel = new QSqlQueryModel();
    QTableView *virtualTableView = new QTableView();

    virtualQueryModel->setQuery("SELECT `Предмети`.`Тип`, COUNT(*)"
                                "FROM `Предмети`"
                                "GROUP BY(`Предмети`.`Тип`);");

    virtualTableView->setModel(virtualQueryModel);

    for (int row = 0; row < virtualTableView->model()->rowCount(); ++row) {
        series->append(virtualTableView->model()->index(row, 0).data().toString(),
                       virtualTableView->model()->index(row, 1).data().toInt());
    }
    series->setLabelsVisible(true);
    */
}

void SubjectStatisticsWindow::setBlackUI()
{
    QFile file(":/styles/black/StatisticsWindows/StatisticsWindows.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeDark);
    chartView->chart()->setBackgroundBrush(QColor(49, 51, 52));
}

void SubjectStatisticsWindow::setWhiteUI()
{
    QFile file(":/styles/white/StatisticsWindows/StatisticsWindows.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeLight);
    chartView->chart()->setBackgroundBrush(QColor(255, 255, 255));
}

void SubjectStatisticsWindow::setSystemUI()
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

void SubjectStatisticsWindow::setTheme(const QString &style)
{
    if (style == "black") {
        setBlackUI();
    } else if (style == "white") {
        setWhiteUI();
    } else {
        setSystemUI();
    }
}
