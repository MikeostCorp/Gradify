#include "studentstatistics.h"
#include "ui_studentstatistics.h"

studentStatistics::studentStatistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentStatistics)
{
    ui->setupUi(this);
    setWindowTitle("Статистика студентів");
}

studentStatistics::~studentStatistics()
{
    delete ui;
}
