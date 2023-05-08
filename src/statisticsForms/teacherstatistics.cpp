#include "teacherstatistics.h"
#include "ui_teacherstatistics.h"

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
