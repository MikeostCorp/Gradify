#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QMessageBox>
#include <QTableView>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowTitle("Вхід");
    setFixedSize(width(), height());
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    connect(ui->loginLineEdit, SIGNAL(QLineEdit::focusInEvent), this, SLOT(clearLineLogin(bool)));
    connect(ui->loginLineEdit,
            &QLineEdit::returnPressed,
            this,
            &LoginWindow::startAuthozation);
    connect(ui->loginLineEdit,
            &QLineEditWithButton::buttonClicked,
            this,
            &LoginWindow::loginClearButtonCliked);

    connect(ui->passwordLineEdit,
            SIGNAL(QLineEdit::focusInEvent),
            this,
            SLOT(clearLinePassword(bool)));
    connect(ui->passwordLineEdit,
            &QLineEdit::returnPressed,
            this,
            &LoginWindow::startAuthozation);
    connect(ui->passwordLineEdit,
            &QLineEditWithButton::buttonClicked,
            this,
            &LoginWindow::passwordVisibilityButtonClicked);

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::loginProcessing);

    show();
    close();

    ui->authorizationErrorLabel->setVisible(false);

    ui->loginLineEdit->setPlaceholderText("Логін");
    ui->passwordLineEdit->setPlaceholderText("Пароль");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::startAuthozation()
{
    loginProcessing();
}

void LoginWindow::loginFailed()
{
    ui->authorizationErrorLabel->setVisible(true);
}

void LoginWindow::loginSuccessful()
{
    ui->authorizationErrorLabel->setVisible(false);

    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf",
                             QSettings::IniFormat);

    QString email;

    if (settingsConfig.contains("userlogin")) {
        email = settingsConfig.value("userlogin").toString();
    } else {
        email = ui->loginLineEdit->text();

        if (ui->rememberCheckBox->isChecked()) {
            QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf",
                                     QSettings::IniFormat);
            settingsConfig.setValue("userlogin", email);
            settingsConfig.setValue("userpassword", ui->passwordLineEdit->text());
        } else {
            QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf",
                                     QSettings::IniFormat);
            settingsConfig.remove("userlogin");
            settingsConfig.remove("userpassword");
        }
    }

    QString login = email.left(email.indexOf('@'));

    emit signalLogin(login);
    close();
}

void LoginWindow::clearInputFields()
{
    ui->loginLineEdit->clear();
    ui->passwordLineEdit->clear();

    ui->loginLineEdit->setFocus();

    ui->authorizationErrorLabel->setVisible(false);

    ui->rememberCheckBox->setChecked(false);
}

void LoginWindow::on_forgotPasswordButton_clicked()
{
    QMessageBox::information(this,
                             "Увага",
                             "У випадку якщо ви забулі пароль або логін зверніться по пошті:"
                             "\nsupport@gradify.online");
}

void LoginWindow::loginClearButtonCliked()
{
    ui->loginLineEdit->clear();
}

void LoginWindow::passwordVisibilityButtonClicked()
{
    if (not isPasswordHidden) {
        isPasswordHidden = true;
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
        if (styleType == "white") {
            ui->passwordLineEdit->setIconButton(QIcon(":/img/blackMenuIcon/noWatchPass.png"));
        } else {
            ui->passwordLineEdit->setIconButton(QIcon(":/img/whiteMenuIcon/noWatchPass.png"));
        }
    } else {
        isPasswordHidden = false;
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
        if (styleType == "white") {
            ui->passwordLineEdit->setIconButton(QIcon(":/img/blackMenuIcon/watchPass.png"));
        } else {
            ui->passwordLineEdit->setIconButton(QIcon(":/img/whiteMenuIcon/watchPass.png"));
        }
    }
}

void LoginWindow::setTheme(const QString &style)
{
    if (style == "black") {
        styleType = "black";
        setBlackUI();
    } else if (style == "white") {
        styleType = "white";
        setWhiteUI();
    } else {
        setSystemUI();
    }
}

void LoginWindow::loginProcessing()
{
    if (ui->loginLineEdit->text().isEmpty()) {
        ui->loginLineEdit->setFocus();
    } else if (ui->passwordLineEdit->text().isEmpty()) {
        ui->passwordLineEdit->setFocus();
    } else {
        QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf",
                                 QSettings::IniFormat);

        if (not settingsConfig.contains("url") or not settingsConfig.contains("apiKey")) {
            QMessageBox::information(this,
                                     "Увага",
                                     "Перевірте налаштування: всі параметри повинні бути заповнені!");
            return;
        }

        QString login = ui->loginLineEdit->text();
        QString password = ui->passwordLineEdit->text();

        emit loginAttempt(login, password);
    }
}

void LoginWindow::setBlackUI()
{
    QFile file(":/styles/black/LoginWindow/LoginWindow.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    styleType = "black";
    isPasswordHidden = false;
    ui->imageLabel->setPixmap(QPixmap(":/img/whiteMenuIcon/cloud.png"));

    ui->loginLineEdit->setIconButton(QIcon(":/img/whiteMenuIcon/clearLoginIco.png"));
    ui->loginLineEdit->setIconSize(QSize(13, 13));

    ui->passwordLineEdit->setIconButton(QIcon(":/img/whiteMenuIcon/watchPass.png"));
    ui->passwordLineEdit->setIconSize(QSize(16, 16));
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

void LoginWindow::setWhiteUI()
{
    QFile file(":/styles/white/LoginWindow/LoginWindow.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    styleType = "white";
    isPasswordHidden = false;
    ui->imageLabel->setPixmap(QPixmap(":/img/blackMenuIcon/cloud.png"));

    ui->loginLineEdit->setIconButton(QIcon(":/img/blackMenuIcon/clearLoginIco.png"));
    ui->loginLineEdit->setIconSize(QSize(13, 13));

    ui->passwordLineEdit->setIconButton(QIcon(":/img/blackMenuIcon/watchPass.png"));
    ui->passwordLineEdit->setIconSize(QSize(16, 16));
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

void LoginWindow::setSystemUI()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(),
                                      1 - baseColor.greenF(),
                                      1 - baseColor.blueF());

    if (newBase.name() == "#000000") {
        styleType = "white";
        setWhiteUI();
    } else {
        styleType = "black";
        setBlackUI();
    }
}
