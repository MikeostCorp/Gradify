#include "appsettingswindow.h"
#include "ui_appsettingswindow.h"

#include <QDir>
#include <QMessageBox>
#include <mainwindow.h>

AppSettingsWindow::AppSettingsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppSettingsWindow)
{
    ui->setupUi(this);
    setWindowTitle("Налаштування");
    //setWindowFlags(Qt::WindowStaysOnTopHint);

    show();
    close();

    setMinimumSize(width(), height());

    ui->succSaveSettings->setVisible(false);

    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf",
                             QSettings::IniFormat);
    if (settingsConfig.contains("url") and settingsConfig.contains("username")
        and settingsConfig.contains("password") and settingsConfig.contains("databasename")) {
        ui->dburlLineEdit->setText(settingsConfig.value("url").toString());
        ui->dbloginLineEdit->setText(settingsConfig.value("username").toString());
        ui->dbpasswordLineEdit->setText(settingsConfig.value("password").toString());
        ui->dbnameLineEdit->setText(settingsConfig.value("databasename").toString());
    }
}

AppSettingsWindow::~AppSettingsWindow()
{
    delete ui;
}

void AppSettingsWindow::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::ActivationChange) {
        if (not isActiveWindow()) {
            ui->succSaveSettings->setVisible(false);
        }
    }
}

void AppSettingsWindow::setBlackUI()
{
    QFile file(":/styles/black/AppSettingsWindow/AppSettingsWindow.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
    ui->selectBlackUIRadioButton->setChecked(true);
}

void AppSettingsWindow::setWhiteUI()
{
    QFile file(":/styles/white/AppSettingsWindow/AppSettingsWindow.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
    ui->selectWhiteUIRadioButton->setChecked(true);
}

void AppSettingsWindow::setSystemUI()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(),
                                      1 - baseColor.greenF(),
                                      1 - baseColor.blueF());

    if (newBase.name() == "#000000") {
        setWhiteUI();
        emit changeThemeApp("white");
    } else {
        setBlackUI();
        emit changeThemeApp("black");
    }

    ui->selectSystemUIRadioButton->setChecked(true);
}

void AppSettingsWindow::on_selectWhiteUIButton_clicked()
{
    emit changeThemeApp("white");
    setWhiteUI();
    ui->selectWhiteUIRadioButton->setChecked(true);
}

void AppSettingsWindow::on_selectBlackUIButton_clicked()
{
    emit changeThemeApp("black");
    setBlackUI();
    ui->selectBlackUIRadioButton->setChecked(true);
}

void AppSettingsWindow::on_selectWhiteUIRadioButton_clicked()
{
    emit changeThemeApp("white");
    setWhiteUI();
}

void AppSettingsWindow::on_selectBlackUIRadioButton_clicked()
{
    emit changeThemeApp("black");
    setBlackUI();
}

void AppSettingsWindow::on_selectSystemUIButton_clicked()
{
    setSystemUI();
    ui->selectSystemUIRadioButton->setChecked(true);
}

void AppSettingsWindow::on_selectSystemUIRadioButton_clicked()
{
    setSystemUI();
}

void AppSettingsWindow::setTheme(const QString &style)
{
    if (style == "black") {
        setBlackUI();
    } else if (style == "white") {
        setWhiteUI();
    } else {
        setSystemUI();
    }
}

void AppSettingsWindow::on_saveDBSettings_clicked()
{
    if (ui->dburlLineEdit->text().isEmpty()) {
        QMessageBox::information(this, "URL", "Введіть URL бази даних!");
        ui->dburlLineEdit->setFocus();
        return;
    }
    if (ui->dbloginLineEdit->text().isEmpty()) {
        QMessageBox::information(this, "Логін", "Введіть логін!");
        ui->dbloginLineEdit->setFocus();
        return;
    }
    if (ui->dbpasswordLineEdit->text().isEmpty()) {
        QMessageBox::information(this, "Пароль", "Введіть пароль!");
        ui->dbpasswordLineEdit->setFocus();
        return;
    }
    if (ui->dbnameLineEdit->text().isEmpty()) {
        QMessageBox::information(this, "Назва БД", "Введіть назву БД!");
        ui->dbnameLineEdit->setFocus();
        return;
    }

    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf",
                             QSettings::IniFormat);
    settingsConfig.setValue("url", ui->dburlLineEdit->text());
    settingsConfig.setValue("username", ui->dbloginLineEdit->text());
    settingsConfig.setValue("password", ui->dbpasswordLineEdit->text());
    settingsConfig.setValue("databasename", ui->dbnameLineEdit->text());

    ui->succSaveSettings->setVisible(true);

    emit logoutSignal();
}
