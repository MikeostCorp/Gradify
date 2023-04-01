#include "filterform.h"
#include "ui_filterform.h"

#include <QFile>

filterForm::filterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::filterForm)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint, true);
    setFixedSize(width(), height());
    close();
}

filterForm::~filterForm()
{
    delete ui;
}
