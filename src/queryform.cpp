#include "queryform.h"
#include "ui_queryform.h"

#include <QFile>

queryForm::queryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::queryForm)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint, true);
    setFixedSize(width(), height());
    close();
}

queryForm::~queryForm()
{
    delete ui;
}

