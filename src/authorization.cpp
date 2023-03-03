#include "authorization.h"
#include "ui_authorization.h"

#include <QMessageBox>

authorization::authorization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
    this->setWindowTitle("Авторизація");
    this->setFixedSize(this->width(), this->height());
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    connect(ui->lineEditLogin, SIGNAL(QLineEdit::focusInEvent), this, SLOT(clearLineLogin(bool)));
    connect(ui->lineEditPassword, SIGNAL(QLineEdit::focusInEvent), this, SLOT(clearLinePassword(bool)));

    this->show();
    this->close();

    ui->authorizationErrorLabel->setVisible(false);
}

authorization::~authorization()
{
    delete ui;
}


void authorization::on_pushButtonForgetPassword_clicked()
{
    QMessageBox::information(this,"Увага","У випадку якщо ви забулі пароль або логін зверніться по пошті:"
                                          "\nandreyizbash228@gmail.com"
                                          "\nmishaEmail");
}


void authorization::on_lineEditLogin_selectionChanged()
{
    if(ui->lineEditLogin->text() == "Логін")
    {
        ui->lineEditLogin->clear();
    }
}


void authorization::on_lineEditLogin_editingFinished()
{
    if(ui->lineEditLogin->text().isEmpty())
    {
        ui->lineEditLogin->setText("Логін");
    }
}


void authorization::on_lineEditPassword_selectionChanged()
{
    if(ui->lineEditPassword->text() == "Пароль")
    {
        ui->lineEditPassword->clear();
        ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    }
}


void authorization::on_lineEditPassword_editingFinished()
{
    if(ui->lineEditPassword->text().isEmpty())
    {
        ui->lineEditPassword->setText("Пароль");
        ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
    }
}

void authorization::clearLineLogin(bool status)
{
    if (!status and ui->lineEditLogin->text().isEmpty())
    {
        ui->lineEditLogin->setText("Логін");
    }
}

void authorization::clearLinePassword(bool status)
{
    if (!status and ui->lineEditPassword->text().isEmpty())
    {
        ui->lineEditPassword->setText("Пароль");
        ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
    }
}


void authorization::on_pushButtonWatchPassword_clicked()
{
    if (!noWatchPassword and ui->lineEditPassword->text() != "Пароль")
    {
        noWatchPassword = true;
        ui->lineEditPassword->setEchoMode(QLineEdit::Normal);
        if (styleType == "white")
        {
            ui->pushButtonWatchPassword->setIcon(QIcon(":/img/whiteMenuIcon/noWatchPass.png"));
        }
        else
        {
            ui->pushButtonWatchPassword->setIcon(QIcon(":/img/blackMenuIcon/noWatchPass.png"));
        }
    }
    else if(ui->lineEditPassword->text() != "Пароль")
    {
        noWatchPassword = false;
        ui->lineEditPassword->setEchoMode(QLineEdit::Password);
        if (styleType == "white")
        {
            ui->pushButtonWatchPassword->setIcon(QIcon(":/img/whiteMenuIcon/watchPass.png"));
        }
        else
        {
            ui->pushButtonWatchPassword->setIcon(QIcon(":/img/blackMenuIcon/watchPass.png"));
        }
    }
}

void authorization::setThemeAuthorUI(QString style)
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


void authorization::setBlackUI()
{
    styleType = "black";
    this->setStyleSheet("authorization{background-color: rgb(41,45,48);}");
    ui->pushButtonWatchPassword->setStyleSheet("background-color: rgb(41,45,48);border: 0px;");
    ui->pushButtonLogin->setStyleSheet("QPushButton{"
                                       "border-radius:  8px;"
                                       "background-color: rgb(61,65,68);"
                                       "color:  rgb(255, 255, 255);} "
                                       "QPushButton:hover{background-color:  rgb(88, 88, 88);}");
    ui->loginLabel->setStyleSheet("font: 34px;color: rgb(255,255,255);");
    ui->lineEditLogin->setStyleSheet("color:#989898;background-color: rgb(29, 31, 32);border-radius: 8px;");
    ui->lineEditPassword->setStyleSheet("color:#989898;background-color: rgb(29, 31, 32);border-radius: 8px;");
    ui->pushButtonForgetPassword->setStyleSheet("color: rgb(255,255,255);");
    ui->imageLabel->setPixmap(QPixmap(":/img/whiteMenuIcon/cloud.png"));
    ui->pushButtonWatchPassword->setIcon(QIcon(":/img/blackMenuIcon/watchPass.png"));
    ui->lineEditLogin->setText("Логін");
    ui->lineEditPassword->setText("Пароль");
    ui->authorizationErrorLabel->setVisible(false);
}

void authorization::setWhiteUI()
{
    styleType = "white";
    this->setStyleSheet("authorization{background-color: rgb(231,224,223);}");
    ui->pushButtonWatchPassword->setStyleSheet("background-color: rgb(231,224,223);border: 0px;");
    ui->pushButtonLogin->setStyleSheet("QPushButton{"
                                       "border-radius:  8px;"
                                       "background-color: rgb(241,234,233);"
                                       "color: rgb(61, 60, 59);} "
                                       "QPushButton:hover{background-color:  rgb(221, 214, 213);}");
    ui->loginLabel->setStyleSheet("font: 34px;color: rgb(0,0,0);");
    ui->lineEditLogin->setStyleSheet("color:#989898;background-color: rgb(255, 255, 255);border-radius: 8px;");
    ui->lineEditPassword->setStyleSheet("color:#989898;background-color: rgb(255, 255, 255);border-radius: 8px;");
    ui->pushButtonForgetPassword->setStyleSheet("color: rgb(61, 60, 59);");
    ui->imageLabel->setPixmap(QPixmap(":/img/blackMenuIcon/cloud.png"));
    ui->pushButtonWatchPassword->setIcon(QIcon(":/img/whiteMenuIcon/watchPass.png"));
    ui->lineEditLogin->setText("Логін");
    ui->lineEditPassword->setText("Пароль");
    ui->authorizationErrorLabel->setVisible(false);
}

void authorization::on_pushButtonLogin_clicked()
{
    //
    // Код для проверки правильности введения и в случае чего высвечивать надпись
    // про ошибку ввода пароля
    //



    ui->authorizationErrorLabel->setVisible(true);
}

