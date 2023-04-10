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

    ui->loginLineEdit->setPlaceholderText("Логін");
    ui->passwordLineEdit->setPlaceholderText("Пароль");
}


authorization::~authorization()
{
    delete ui;
}

void authorization::startAuthozation()
{
    on_loginButton_clicked();
}


void authorization::on_loginClearButton_clicked()
{
    ui->loginLineEdit->clear();
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

        authorizationDB = QSqlDatabase::addDatabase("QMYSQL");
        // https://gradify.online/

        authorizationDB.setHostName("141.136.44.252");
        authorizationDB.setUserName("GradifyAdmin");
        authorizationDB.setPassword("P433w0rD!");
        authorizationDB.setDatabaseName("accounts_db");

        if (!authorizationDB.open())
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
            emit signalLogin(login);
            ui->loginLineEdit->clear();
            ui->passwordLineEdit->clear();
            ui->loginLineEdit->setFocus();
            ui->authorizationErrorLabel->setVisible(false);
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
    ui->loginClearButton->setIcon(QIcon(":/img/whiteMenuIcon/clearLoginIco.png"));
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
    ui->loginClearButton->setIcon(QIcon(":/img/blackMenuIcon/clearLoginIco.png"));
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


void authorization::on_rememberCheckBox_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        // КОД ЕСЛИ НЕ ЗАПОМНИТЬ ЮЗЕРА
    }
    else
    {
        // КОД ЗАПОМНИТЬ ЮЗЕРА !!!
    }
}

