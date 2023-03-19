#include "authorization.h"
#include "ui_authorization.h"

#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTableView>
#include <QDir>

authorization::authorization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
    setWindowTitle("Авторизація");
    setFixedSize(width(), height());
    setWindowFlag(Qt::WindowStaysOnTopHint);

    connect(ui->loginLineEdit, SIGNAL(QLineEdit::focusInEvent), this, SLOT(clearLineLogin(bool)));
    connect(ui->passwordLineEdit, SIGNAL(QLineEdit::focusInEvent), this, SLOT(clearLinePassword(bool)));
    connect(ui->loginLineEdit, &QLineEdit::returnPressed, this, &authorization::startAuthozation);
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, this, &authorization::startAuthozation);

    show();
    close();

    ui->authorizationErrorLabel->setVisible(false);

}


authorization::~authorization()
{
    delete ui;
}

void authorization::startAuthozation()
{
    on_loginButton_clicked();
}


void authorization::on_forgotPasswordButton_clicked()
{
    QMessageBox::information(this, "Увага", "У випадку якщо ви забулі пароль або логін зверніться по пошті:"
                                            "\nandreyizbash228@gmail.com"
                                            "\nmikeostashenko@gmail.com");
}


void authorization::on_passwordVisibilityButton_clicked()
{
    if (!isPasswordHidden)
    {
        isPasswordHidden = true;
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
        if (styleType == "white")
        {
            ui->passwordVisibilityButton->setIcon(QIcon(":/img/blackMenuIcon/noWatchPass.png"));
        }
        else
        {
            ui->passwordVisibilityButton->setIcon(QIcon(":/img/whiteMenuIcon/noWatchPass.png"));
        }
    }
    else
    {
        isPasswordHidden = false;
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
        if (styleType == "white")
        {
            ui->passwordVisibilityButton->setIcon(QIcon(":/img/blackMenuIcon/watchPass.png"));
        }
        else
       {
            ui->passwordVisibilityButton->setIcon(QIcon(":/img/whiteMenuIcon/watchPass.png"));
        }
    }
}


void authorization::setThemeAuthorUI(const QString style)
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


void authorization::on_loginButton_clicked()
{
    if (ui->loginLineEdit->text().isEmpty())
    {
        ui->loginLineEdit->setFocus();
        //
        // ДОБАВИТЬ КРАСНЫЙ ФОКУС НА ЛЕЙБЛЫ
        //
        //ui->loginLabel->setStyleSheet("color: red;");
    }
    else if (ui->passwordLineEdit->text().isEmpty())
    {
        ui->passwordLineEdit->setFocus();
        //ui->passwordLabel->setStyleSheet("color: red;");
    }
    else
    {
        //
        // Код для проверки правильности введения и в случае чего высвечивать надпись
        // про ошибку ввода пароля
        //
        //authorizationDB = QSqlDatabase::addDatabase("QSQLITE");
        //authorizationDB.setDatabaseName(QDir::currentPath() + "/../../../../src/passLog.db");
        //authorizationDB.setDatabaseName("/Users/andrii/Desktop/Gradify/src/passLog.db");

        // QMessageBox::information(this, "test", );

        authorizationDB = QSqlDatabase::addDatabase("QMYSQL");
        // https://gradify.online/
        // maybe fix & put normal hostname
        authorizationDB.setHostName("45.84.207.102"); // 45.84.207.129
        authorizationDB.setUserName("u838940490_admin");
        authorizationDB.setPassword("Password1");
        authorizationDB.setDatabaseName("u838940490_accounts");



        QString login = ui->loginLineEdit->text();
        QString password = ui->passwordLineEdit->text();

        authorizationDB.open();
        QSqlQueryModel *queryModel = new QSqlQueryModel(this);
        QTableView *tableView = new QTableView(this);
        queryModel->setQuery("SELECT * "
                             "FROM Акаунти "
                             "WHERE Логін = '" + login + "'"
                             " AND Пароль = '" + password + "'");
        tableView->setModel(queryModel);

        if (tableView->model()->rowCount() > 0)
        {
            emit signalLogin(login);
            ui->loginLineEdit->clear();
            ui->passwordLineEdit->clear();
            ui->loginLineEdit->setFocus();
            authorizationDB.close();
            close();
        }
        else
        {
            ui->authorizationErrorLabel->setVisible(true);
        }
    }
}


void authorization::setBlackUI()
{
    QFile file(":/styles/black/authorization/authorization.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    styleType = "black";
    isPasswordHidden = false;
    ui->imageLabel->setPixmap(QPixmap(":/img/whiteMenuIcon/cloud.png"));
    ui->passwordVisibilityButton->setIcon(QIcon(":/img/whiteMenuIcon/watchPass.png"));
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}


void authorization::setWhiteUI()
{
    QFile file(":/styles/white/authorization/authorization.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    styleType = "white";
    isPasswordHidden = false;
    ui->imageLabel->setPixmap(QPixmap(":/img/blackMenuIcon/cloud.png"));
    ui->passwordVisibilityButton->setIcon(QIcon(":/img/blackMenuIcon/watchPass.png"));
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}


void authorization::setSystemUI()
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
