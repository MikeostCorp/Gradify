#include "gradestatistics.h"
#include "ui_gradestatistics.h"

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
