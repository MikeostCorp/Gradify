#include "appsetting.h"
#include "ui_appsetting.h"

#include <mainwindow.h>
#include <QDir>
#include <QMessageBox>

appSetting::appSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::appSetting)
{
    ui->setupUi(this);
    setWindowTitle("Налаштування");
    show();
    close();
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
            close();
        }
    }
}


void appSetting::setBlackUI()
{
    setStyleSheet("appSetting { background-color: rgb(29, 31, 32); }");
    ui->selectBlackUIRadioButton->setStyleSheet("color: rgb(255,255,255)");
    ui->selectWhiteUIRadioButton->setStyleSheet("color: rgb(255,255,255)");
    ui->selectBlackUIRadioButton->setChecked(true);
}

void appSetting::setWhiteUI()
{
    setStyleSheet("appSetting { background-color: rgb(255, 255, 255); }");
    ui->selectBlackUIRadioButton->setStyleSheet("color: rgb(0,0,0)");
    ui->selectWhiteUIRadioButton->setStyleSheet("color: rgb(0,0,0)");
    ui->selectWhiteUIRadioButton->setChecked(true);
}


void appSetting::on_selectWhiteUIButton_clicked()
{
    emit changeThemeApp("white");
    setWhiteUI();
    ui->selectWhiteUIRadioButton->setChecked(true);
}


void appSetting::on_selectBlackUIButton_clicked()
{
    emit changeThemeApp("black");
    setBlackUI();
    ui->selectBlackUIRadioButton->setChecked(true);
}


void appSetting::on_selectWhiteUIRadioButton_clicked()
{
    emit changeThemeApp("white");
    setWhiteUI();
}


void appSetting::on_selectBlackUIRadioButton_clicked()
{
    emit changeThemeApp("black");
    setBlackUI();
}


void appSetting::setThemeSettingUI(const QString style)
{
    if (style == "black")
    {
        setBlackUI();
    }
    else
    {
        setWhiteUI();
    }
}
