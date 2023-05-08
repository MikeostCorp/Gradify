#include "groupstatistics.h"
#include "ui_groupstatistics.h"

groupStatistics::groupStatistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupStatistics)
{
    ui->setupUi(this);
    setWindowTitle("Статистика груп");
}

groupStatistics::~groupStatistics()
{
    delete ui;
}
