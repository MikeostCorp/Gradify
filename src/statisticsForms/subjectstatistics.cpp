#include "subjectstatistics.h"
#include "ui_subjectstatistics.h"

subjectStatistics::subjectStatistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subjectStatistics)
{
    ui->setupUi(this);
    setWindowTitle("Статистика предметів");
}

subjectStatistics::~subjectStatistics()
{
    delete ui;
}
