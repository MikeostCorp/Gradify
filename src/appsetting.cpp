#include "appsetting.h"
#include "ui_appsetting.h"

#include <mainwindow.h>

appSetting::appSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::appSetting)
{
    ui->setupUi(this);

    this->setWindowTitle("Налаштування");

}

appSetting::~appSetting()
{
    delete ui;
}

void appSetting::changeEvent(QEvent *event)
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


void appSetting::on_setBlackStyle_clicked()
{
    emit changeThemeApp(0);
    this->setStyleSheet("appSetting { background-color: rgb(29, 31, 32); }");
}


void appSetting::on_setWhiteStyle_clicked()
{
    emit changeThemeApp(1);
    this->setStyleSheet("appSetting { background-color: rgb(226, 224, 223); }");
}



