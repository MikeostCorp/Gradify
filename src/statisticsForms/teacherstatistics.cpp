#include "teacherstatistics.h"
#include "ui_teacherstatistics.h"

#include <QFile>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QChartView>
#include <QValueAxis>
#include <QBarCategoryAxis>

teacherStatistics::teacherStatistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacherStatistics)
{
    ui->setupUi(this);
    setWindowTitle("Статистика викладачів");
}


teacherStatistics::~teacherStatistics()
{
    delete ui;
}


void teacherStatistics::setBlackUI()
{
    QFile file(":/styles/black/statisticsForms/statisticsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void teacherStatistics::setWhiteUI()
{
    QFile file(":/styles/white/statisticsForms/statisticsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void teacherStatistics::setSystemUI()
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


void teacherStatistics::setTheme(const QString &style)
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
