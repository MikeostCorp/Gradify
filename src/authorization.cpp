#include "authorization.h"
#include "ui_authorization.h"

authorization::authorization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
    this->setWindowTitle("Авторизація");
    this->setFixedSize(this->width(), this->height());
}

authorization::~authorization()
{
    delete ui;
}

void authorization::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::ActivationChange)
    {
        if (!isActiveWindow())
        {
            this->close();
        }
    }
}
