#include "authorization.h"
#include "ui_authorization.h"

#include <QMessageBox>

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

    show();
    close();

    ui->authorizationErrorLabel->setVisible(false);


}

authorization::~authorization()
{
    delete ui;
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
    if(style == "black")
    {
        styleType = "black";
        setBlackUI();
    }
    else
    {
        styleType = "white";
        setWhiteUI();
    }
}

void authorization::setStatusAuthorization(const bool status)
{
    if(status)
    {
        ui->authorizationErrorLabel->setVisible(false);
        close();
    }
    else
    {
        ui->authorizationErrorLabel->setVisible(true);
    }
}

void authorization::setBlackUI()
{
    styleType = "black";
    setStyleSheet("authorization{background-color: rgb(41,45,48);}");
    ui->passwordVisibilityButton->setStyleSheet("background-color: rgb(41,45,48);border: 0px;");

    styleF.setFileName(":/styles/black/authorizationButton.qss");
    styleF.open(QFile::ReadOnly);
    ui->loginButton->setStyleSheet(styleF.readAll());
    ui->forgotPasswordButton->setStyleSheet(ui->loginButton->styleSheet());

    ui->loginLabel->setStyleSheet("font: 34px;color: rgb(255,255,255);");
    ui->loginLineEdit->setStyleSheet("color: white;background-color: rgb(29, 31, 32);border-radius: 8px;");
    ui->passwordLineEdit->setStyleSheet("color:white;background-color: rgb(29, 31, 32);border-radius: 8px;");
    ui->imageLabel->setPixmap(QPixmap(":/img/whiteMenuIcon/cloud.png"));
    ui->passwordVisibilityButton->setIcon(QIcon(":/img/whiteMenuIcon/watchPass.png"));

    isPasswordHidden = false;
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);}

void authorization::setWhiteUI()
{
    styleType = "white";
    setStyleSheet("authorization{background-color: rgb(231,224,223);}");
    ui->passwordVisibilityButton->setStyleSheet("background-color: rgb(231,224,223);border: 0px;");

    styleF.setFileName(":/styles/white/authorizationButton.qss");
    styleF.open(QFile::ReadOnly);
    ui->loginButton->setStyleSheet(styleF.readAll());
    ui->forgotPasswordButton->setStyleSheet(ui->loginButton->styleSheet());

    ui->loginLabel->setStyleSheet("font: 34px;color: rgb(61, 60, 59);");
    ui->loginLineEdit->setStyleSheet("color:rgb(61, 60, 59);background-color: rgb(255, 255, 255);border-radius: 8px;");
    ui->passwordLineEdit->setStyleSheet("color:rgb(61, 60, 59);background-color: rgb(255, 255, 255);border-radius: 8px;");
    ui->imageLabel->setPixmap(QPixmap(":/img/blackMenuIcon/cloud.png"));
    ui->passwordVisibilityButton->setIcon(QIcon(":/img/blackMenuIcon/watchPass.png"));

    isPasswordHidden = false;
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

void authorization::on_loginButton_clicked()
{
    //
    // Код для проверки правильности введения и в случае чего высвечивать надпись
    // про ошибку ввода пароля
    //

    if(!ui->passwordLineEdit->text().isEmpty() and !ui->loginLineEdit->text().isEmpty())
    {
        emit signalPasswordLogin(ui->loginLineEdit->text(), ui->passwordLineEdit->text());
    }
    else
    {
        ui->authorizationErrorLabel->setVisible(true);
    }
}

