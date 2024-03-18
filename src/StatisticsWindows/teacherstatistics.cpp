#include "teacherstatistics.h"
#include "ui_teacherstatistics.h"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QFile>
#include <QValueAxis>

TeacherStatisticsWindow::TeacherStatisticsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::teacherStatistics)
{
    ui->setupUi(this);
    setWindowTitle("Статистика викладачів по категоріям");

    series = new QPieSeries();

    chart = new QChart();
    chart->addSeries(series);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTitle("Статистика викладачів по категоріям");

    chart->legend()->setVisible(true);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(450);

    ui->specialChartL->addWidget(chartView);
}

TeacherStatisticsWindow::~TeacherStatisticsWindow()
{
    delete ui;
}

void TeacherStatisticsWindow::closeEvent(QCloseEvent *event)
{
    if (event->Close) {
        series->clear();
    }
}

void TeacherStatisticsWindow::fillChart()
{
    /*
    QSqlQueryModel *virtualQueryModel = new QSqlQueryModel();
    QTableView *virtualTableView = new QTableView();

    virtualQueryModel->setQuery("SELECT `Викладачі`.`Спеціалізація`, COUNT(*)"
                                "FROM `Викладачі`"
                                "GROUP BY(`Викладачі`.`Спеціалізація`);");

    virtualTableView->setModel(virtualQueryModel);

    for (int row = 0; row < virtualTableView->model()->rowCount(); ++row) {
        series->append(virtualTableView->model()->index(row, 0).data().toString(),
                       virtualTableView->model()->index(row, 1).data().toInt());
    }
    series->setLabelsVisible(true);
    */
}

void TeacherStatisticsWindow::setBlackUI()
{
    QFile file(":/styles/black/StatisticsWindows/StatisticsWindows.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeDark);
    chartView->chart()->setBackgroundBrush(QColor(49, 51, 52));
}

void TeacherStatisticsWindow::setWhiteUI()
{
    QFile file(":/styles/white/StatisticsWindows/StatisticsWindows.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeLight);
    chartView->chart()->setBackgroundBrush(QColor(255, 255, 255));
}

void TeacherStatisticsWindow::setSystemUI()
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

void TeacherStatisticsWindow::setTheme(const QString &style)
{
    if (style == "black") {
        setBlackUI();
    } else if (style == "white") {
        setWhiteUI();
    } else {
        setSystemUI();
    }
}
