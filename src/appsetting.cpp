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
    //setWindowFlags(Qt::WindowStaysOnTopHint);

    show();
    close();

    setMinimumSize(width(), height());

    ui->succSaveSettings->setVisible(false);

    QSettings settingsConfig(QDir::currentPath() + "/gradify.conf", QSettings::IniFormat);
    if (settingsConfig.contains("hostname") and
        settingsConfig.contains("username") and
        settingsConfig.contains("password") and
        settingsConfig.contains("databasename"))
    {
        ui->dbhostnameLineEdit->setText(settingsConfig.value("hostname").toString());
        ui->dbloginLineEdit->setText(settingsConfig.value("username").toString());
        ui->dbpasswordLineEdit->setText(settingsConfig.value("password").toString());
        ui->dbnameLineEdit->setText(settingsConfig.value("databasename").toString());
    }
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
            ui->succSaveSettings->setVisible(false);
        }
    }
}


void appSetting::setBlackUI()
{
    QFile file(":/styles/black/appSetting/appSetting.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
    ui->selectBlackUIRadioButton->setChecked(true);
}


void appSetting::setWhiteUI()
{
    QFile file(":/styles/white/appSetting/appSetting.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
    ui->selectWhiteUIRadioButton->setChecked(true);
}


void appSetting::setSystemUI()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(), 1 - baseColor.greenF(), 1 - baseColor.blueF());

    if (newBase.name() == "#000000")
    {
        setWhiteUI();
        emit changeThemeApp("white");
    }
    else
    {
        setBlackUI();
        emit changeThemeApp("black");
    }

    ui->selectSystemUIRadioButton->setChecked(true);
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


void appSetting::on_selectSystemUIButton_clicked()
{
    setSystemUI();
    ui->selectSystemUIRadioButton->setChecked(true);
}


void appSetting::on_selectSystemUIRadioButton_clicked()
{
    setSystemUI();
}


void appSetting::setTheme(const QString &style)
{
    if (style == "black")
    {
        setBlackUI();
    }
    else if (style == "white")
    {
        setWhiteUI();
    }
    else
    {
        setSystemUI();
    }
}

void appSetting::on_saveDBSettings_clicked()
{
    if (ui->dbhostnameLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "Хост", "Введіть хост!");
        ui->dbhostnameLineEdit->setFocus();
        return;
    }
    if (ui->dbloginLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "Логін", "Введіть логін!");
        ui->dbloginLineEdit->setFocus();
        return;
    }
    if (ui->dbpasswordLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "Пароль", "Введіть пароль!");
        ui->dbpasswordLineEdit->setFocus();
        return;
    }
    if (ui->dbnameLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "Назва БД", "Введіть назву БД!");
        ui->dbnameLineEdit->setFocus();
        return;
    }

    QSettings settingsConfig(QDir::currentPath() + "/gradify.conf", QSettings::IniFormat);
    settingsConfig.setValue("hostname", ui->dbhostnameLineEdit->text());
    settingsConfig.setValue("username", ui->dbloginLineEdit->text());
    settingsConfig.setValue("password", ui->dbpasswordLineEdit->text());
    settingsConfig.setValue("databasename", ui->dbnameLineEdit->text());

    ui->succSaveSettings->setVisible(true);

    emit logoutSignal();
}

