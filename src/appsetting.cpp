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


void appSetting::on_setBlackStyleButton_clicked()
{
    emit changeThemeApp(0);
    this->setStyleSheet("appSetting { background-color: rgb(29, 31, 32); }");
    QString filename = QDir::currentPath() + "/../../../../src/config/cfg";
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "app-style: 0" << Qt::endl;
    }
}


void appSetting::on_setWhiteStyleButton_clicked()
{
    emit changeThemeApp(1);
    this->setStyleSheet("appSetting { background-color: rgb(226, 224, 223); }");
    QString filename = QDir::currentPath() + "/../../../../src/config/cfg";
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "app-style: 1" << Qt::endl;
    }
}



