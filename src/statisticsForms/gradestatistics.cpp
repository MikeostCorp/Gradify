#include "gradestatistics.h"
#include "ui_gradestatistics.h"

#include <QFile>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QChartView>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QMessageBox>

gradeStatistics::gradeStatistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gradeStatistics)
{
    ui->setupUi(this);
    setWindowTitle("Статистика оцінок");
}


gradeStatistics::~gradeStatistics()
{
    delete ui;
}


void gradeStatistics::setBlackUI()
{
    QFile file(":/styles/black/statisticsForms/statisticsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void gradeStatistics::setWhiteUI()
{
    QFile file(":/styles/white/statisticsForms/statisticsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

}


void gradeStatistics::setSystemUI()
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


void gradeStatistics::setTheme(const QString &style)
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
