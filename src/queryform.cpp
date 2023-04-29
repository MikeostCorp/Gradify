#include "queryform.h"
#include "ui_queryform.h"

#include <QMessageBox>

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


void queryForm::on_mySQLPushButton_clicked()
{
    QMessageBox::information(this, "", "hello vinegret!\nIt's test!");
    ui->mySQLPushButton->setFocus();
    show();
}

