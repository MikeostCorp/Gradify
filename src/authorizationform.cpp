#include "authorizationform.h"
#include "ui_authorizationform.h"

#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTableView>
#include <QDir>

authorizationForm::authorizationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authorizationForm)
{
    ui->setupUi(this);
    setWindowTitle("Авторизація");
    setFixedSize(width(), height());
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    connect(ui->loginLineEdit, SIGNAL(QLineEdit::focusInEvent), this, SLOT(clearLineLogin(bool)));
    connect(ui->loginLineEdit, &QLineEdit::returnPressed, this, &authorizationForm::startAuthozation);
    connect(ui->loginLineEdit, &QLineEditWithButton::buttonClicked, this, &authorizationForm::loginClearButtonCliked);

    connect(ui->passwordLineEdit, SIGNAL(QLineEdit::focusInEvent), this, SLOT(clearLinePassword(bool)));
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, this, &authorizationForm::startAuthozation);
    connect(ui->passwordLineEdit, &QLineEditWithButton::buttonClicked, this, &authorizationForm::passwordVisibilityButtonClicked);

    show();
    close();

    ui->authorizationErrorLabel->setVisible(false);

    ui->loginLineEdit->setPlaceholderText("Логін");
    ui->passwordLineEdit->setPlaceholderText("Пароль");
}


authorizationForm::~authorizationForm()
{
    delete ui;
}


void authorizationForm::startAuthozation()
{
    on_loginButton_clicked();
}


void authorizationForm::on_forgotPasswordButton_clicked()
{
    QMessageBox::information(this, "Увага", "У випадку якщо ви забулі пароль або логін зверніться по пошті:"
                                            "\nsupport@gradify.online");
}


void authorizationForm::loginClearButtonCliked()
{
    ui->loginLineEdit->clear();
}


void authorizationForm::passwordVisibilityButtonClicked()
{
    if (not isPasswordHidden)
    {
        isPasswordHidden = true;
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
        if (styleType == "white")
        {
            ui->passwordLineEdit->setIconButton(QIcon(":/img/blackMenuIcon/noWatchPass.png"));
        }
        else
        {
            ui->passwordLineEdit->setIconButton(QIcon(":/img/whiteMenuIcon/noWatchPass.png"));
        }
    }
    else
    {
        isPasswordHidden = false;
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
        if (styleType == "white")
        {
            ui->passwordLineEdit->setIconButton(QIcon(":/img/blackMenuIcon/watchPass.png"));
        }
        else
        {
            ui->passwordLineEdit->setIconButton(QIcon(":/img/whiteMenuIcon/watchPass.png"));
        }
    }
}


void authorizationForm::setTheme(const QString &style)
{
    if (style == "black")
    {
        styleType = "black";
        setBlackUI();
    }
    else if (style == "white")
    {
        styleType = "white";
        setWhiteUI();
    }
    else
    {
        setSystemUI();
    }
}


void authorizationForm::on_loginButton_clicked()
{
    if (ui->loginLineEdit->text().isEmpty())
    {
        ui->loginLineEdit->setFocus();
    }
    else if (ui->passwordLineEdit->text().isEmpty())
    {
        ui->passwordLineEdit->setFocus();
    }
    else
    {
        authorizationDB = QSqlDatabase::addDatabase("QMYSQL");
        // https://gradify.online/
        authorizationDB.setHostName("141.136.44.252");
        authorizationDB.setUserName("GradifyAdmin");
        authorizationDB.setPassword("P433w0rD!");
        authorizationDB.setDatabaseName("accounts_db");

        if (not authorizationDB.open())
        {
            QMessageBox::information(this, "Увага", "Перевірте інтернет з'єднання");
            return;
        }

        QString login = ui->loginLineEdit->text();
        QString password = ui->passwordLineEdit->text();

        QSqlQueryModel *queryModel = new QSqlQueryModel(this);
        QTableView *tableView = new QTableView(this);
        queryModel->setQuery("SELECT * "
                             "FROM Акаунти "
                             "WHERE Логін = '" + login + "'"
                             " AND Пароль = '" + password + "'");

        tableView->setModel(queryModel);

        if (tableView->model()->rowCount() > 0)
        {
            ui->loginLineEdit->clear();
            ui->passwordLineEdit->clear();
            ui->loginLineEdit->setFocus();
            ui->authorizationErrorLabel->setVisible(false);

            if (ui->rememberCheckBox->isChecked())
            {
                QSettings settingsConfig(QDir::currentPath() + "/gradify.conf", QSettings::IniFormat);
                settingsConfig.setValue("userlogin", login);
            }
            else
            {
                QSettings settingsConfig(QDir::currentPath() + "/gradify.conf", QSettings::IniFormat);
                settingsConfig.remove("userlogin");
            }

            authorizationDB.close();
            QSqlDatabase::removeDatabase(authorizationDB.connectionName());
            emit signalLogin(login);
            close();
        }
        else
        {
            ui->authorizationErrorLabel->setVisible(true);
        }
    }
}


void authorizationForm::setBlackUI()
{
    QFile file(":/styles/black/authorizationForm/authorizationForm.qss");
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


void authorizationForm::setWhiteUI()
{
    QFile file(":/styles/white/authorizationForm/authorizationForm.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    styleType = "white";
    isPasswordHidden = false;
    ui->imageLabel->setPixmap(QPixmap(":/img/blackMenuIcon/cloud.png"));

    ui->loginLineEdit->setIconButton(QIcon(":/img/blackMenuIcon/clearLoginIco.png"));
    ui->loginLineEdit->setIconSize(QSize(13, 13));

    ui->passwordLineEdit->setIconButton(QIcon(":/img/blackMenuIcon/watchPass.png"));
    ui->passwordLineEdit->setIconSize(QSize(16, 16)  );
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}


void authorizationForm::setSystemUI()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(), 1 - baseColor.greenF(), 1 - baseColor.blueF());

    if (newBase.name() == "#000000")
    {
        styleType = "white";
        setWhiteUI();
    }
    else
    {
        styleType = "black";
        setBlackUI();
    }
}


