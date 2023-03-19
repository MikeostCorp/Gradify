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
    QMessageBox::information(this,"Увага","У випадку якщо ви забулі пароль або логін зверніться по пошті:"
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
        authorizationDB = QSqlDatabase::addDatabase("QSQLITE");
        authorizationDB.setDatabaseName(QDir::currentPath() + "/../../../../src/passLog.db");
        //authorizationDB.setDatabaseName("/Users/andrii/Desktop/Gradify/src/passLog.db");



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
    styleType = "black";
    setStyleSheet("authorization{background-color: rgb(41,45,48);}");
    ui->passwordVisibilityButton->setStyleSheet("background-color: rgb(41,45,48);border: 0px;");

    styleF.setFileName(":/styles/black/authorization/authorizationButton.qss");
    styleF.open(QFile::ReadOnly);
    ui->loginButton->setStyleSheet(styleF.readAll());
    ui->forgotPasswordButton->setStyleSheet(ui->loginButton->styleSheet());
    styleF.close();

    styleF.setFileName(":/styles/black/authorization/LineEdit.qss");
    styleF.open(QFile::ReadOnly);
    ui->loginLineEdit->setStyleSheet(styleF.readAll());
    ui->passwordLineEdit->setStyleSheet(ui->loginLineEdit->styleSheet());
    styleF.close();

    ui->headTitleLabel->setStyleSheet("font: 34px;color: rgb(255,255,255);");
    ui->imageLabel->setPixmap(QPixmap(":/img/whiteMenuIcon/cloud.png"));
    ui->passwordVisibilityButton->setIcon(QIcon(":/img/whiteMenuIcon/watchPass.png"));

    isPasswordHidden = false;
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}


void authorization::setWhiteUI()
{
    styleType = "white";
    setStyleSheet("authorization{background-color: rgb(231,224,223);}");
    ui->passwordVisibilityButton->setStyleSheet("background-color: rgb(231,224,223);border: 0px;");

    styleF.setFileName(":/styles/white/authorization/authorizationButton.qss");
    styleF.open(QFile::ReadOnly);
    ui->loginButton->setStyleSheet(styleF.readAll());
    styleF.close();
    ui->forgotPasswordButton->setStyleSheet(ui->loginButton->styleSheet());

    styleF.setFileName(":/styles/white/authorization/LineEdit.qss");
    styleF.open(QFile::ReadOnly);
    ui->loginLineEdit->setStyleSheet(styleF.readAll());
    ui->passwordLineEdit->setStyleSheet(ui->loginLineEdit->styleSheet());
    styleF.close();

    ui->headTitleLabel->setStyleSheet("font: 34px;color: rgb(61, 60, 59);");
    ui->imageLabel->setPixmap(QPixmap(":/img/blackMenuIcon/cloud.png"));
    ui->passwordVisibilityButton->setIcon(QIcon(":/img/blackMenuIcon/watchPass.png"));

    isPasswordHidden = false;
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
