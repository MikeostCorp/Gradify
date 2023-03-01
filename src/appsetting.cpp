#include "appsetting.h"
#include "ui_appsetting.h"

#include <mainwindow.h>
#include <QDir>

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


void appSetting::setBlackUI()
{
    this->setStyleSheet("appSetting { background-color: rgb(29, 31, 32); }");
    ui->setBlackStyleRadioButton->setStyleSheet("color: rgb(255,255,255)");
    ui->setWhiteStyleRadioButton->setStyleSheet("color: rgb(255,255,255)");
    ui->setBlackStyleRadioButton->setChecked(true);
}

void appSetting::setWhiteUI()
{
    this->setStyleSheet("appSetting { background-color: rgb(255, 255, 255); }");
    ui->setBlackStyleRadioButton->setStyleSheet("color: rgb(0,0,0)");
    ui->setWhiteStyleRadioButton->setStyleSheet("color: rgb(0,0,0)");
    ui->setWhiteStyleRadioButton->setChecked(true);
}


void appSetting::on_pushSelectWhiteUIButton_clicked()
{
    emit changeThemeApp(1);
    setWhiteUI();
    ui->setWhiteStyleRadioButton->setChecked(true);
}


void appSetting::on_pushSelectBlackUIButton_clicked()
{
    emit changeThemeApp(0);
    setBlackUI();
    ui->setBlackStyleRadioButton->setChecked(true);
}

void appSetting::setThemeSettingUI(int style)
{
    if(style == 0)
    {
        setBlackUI();
    }
    else
    {
        setWhiteUI();
    }
}

void appSetting::on_setWhiteStyleRadioButton_clicked()
{
    emit changeThemeApp(1);
    setWhiteUI();
    ui->setWhiteStyleRadioButton->setChecked(true);
}


void appSetting::on_setBlackStyleRadioButton_clicked()
{
    emit changeThemeApp(0);
    setBlackUI();
    ui->setBlackStyleRadioButton->setChecked(true);
}

