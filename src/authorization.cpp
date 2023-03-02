#include "authorization.h"
#include "ui_authorization.h"

authorization::authorization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
    this->setWindowTitle("Авторизація");
    this->setFixedSize(this->width(), this->height());
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
}

authorization::~authorization()
{
    delete ui;
}
