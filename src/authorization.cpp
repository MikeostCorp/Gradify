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

void authorization::on_loginLineEdit_selectionChanged()
{
    if (ui->loginLineEdit->text() == "Логін")
    {
        ui->loginLineEdit->clear();

        if (styleType == "white")
        {
            ui->loginLineEdit->setStyleSheet("color: rgb(61, 60, 59);background-color: rgb(255, 255, 255);border-radius: 8px;");
        }
        else
        {
            ui->loginLineEdit->setStyleSheet("color: white;background-color: rgb(29, 31, 32);border-radius: 8px;");
        }
    }
}

void authorization::on_loginLineEdit_editingFinished()
{
    if (ui->loginLineEdit->text().isEmpty())
    {
        ui->loginLineEdit->setText("Логін");

        if (styleType == "white")
        {
            ui->loginLineEdit->setStyleSheet("color:#989898;background-color: rgb(255, 255, 255);border-radius: 8px;");
        }
        else
        {
            ui->loginLineEdit->setStyleSheet("color:#989898;background-color: rgb(29, 31, 32);border-radius: 8px;");
        }
    }
}

void authorization::on_passwordLineEdit_selectionChanged()
{
    if (ui->passwordLineEdit->text() == "Пароль")
    {
        ui->passwordLineEdit->clear();
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
        isPasswordHidden = false;

        if (styleType == "white")
        {
            ui->passwordLineEdit->setStyleSheet("color: rgb(61, 60, 59);background-color: rgb(255, 255, 255);border-radius: 8px;");
            ui->passwordVisibilityButton->setIcon(QIcon(":/img/blackMenuIcon/watchPass.png"));
        }
        else
        {
            ui->passwordLineEdit->setStyleSheet("color: white;background-color: rgb(29, 31, 32);border-radius: 8px;");
            ui->passwordVisibilityButton->setIcon(QIcon(":/img/whiteMenuIcon/watchPass.png"));
        }
    }
}

void authorization::on_passwordLineEdit_editingFinished()
{
    if (ui->passwordLineEdit->text().isEmpty())
    {
        ui->passwordLineEdit->setText("Пароль");
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
        isPasswordHidden = false;

        if (styleType == "white")
        {
            ui->passwordLineEdit->setStyleSheet("color:#989898;background-color: rgb(255, 255, 255);border-radius: 8px;");
            ui->passwordVisibilityButton->setIcon(QIcon(":/img/blackMenuIcon/watchPass.png"));

        }
        else
        {
            ui->passwordLineEdit->setStyleSheet("color:#989898;background-color: rgb(29, 31, 32);border-radius: 8px;");
            ui->passwordVisibilityButton->setIcon(QIcon(":/img/whiteMenuIcon/watchPass.png"));
        }
    }
}

void authorization::clearLineLogin(const bool status)
{
    if (!status and ui->loginLineEdit->text().isEmpty())
    {
        ui->loginLineEdit->setText("Логін");

        if (styleType == "white")
        {
            ui->loginLineEdit->setStyleSheet("color:#989898;background-color: rgb(255, 255, 255);border-radius: 8px;");
        }
        else
        {
            ui->loginLineEdit->setStyleSheet("color:#989898;background-color: rgb(29, 31, 32);border-radius: 8px;");
        }
    }
}

void authorization::clearLinePassword(const bool status)
{
    if (!status and ui->passwordLineEdit->text().isEmpty())
    {
        ui->passwordLineEdit->setText("Пароль");
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    }
}

void authorization::on_passwordVisibilityButton_clicked()
{
    if (!isPasswordHidden and ui->passwordLineEdit->text() != "Пароль")
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
    else if (ui->passwordLineEdit->text() != "Пароль")
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

void authorization::setBlackUI()
{
    styleType = "black";
    setStyleSheet("authorization{background-color: rgb(41,45,48);}");
    ui->passwordVisibilityButton->setStyleSheet("background-color: rgb(41,45,48);border: 0px;");
    ui->loginButton->setStyleSheet("QPushButton{"
                                       "border-radius:  8px;"
                                       "background-color: rgb(61,65,68);"
                                       "color:  rgb(255, 255, 255);} "
                                       "QPushButton:hover{background-color:  rgb(88, 88, 88);}");
    ui->forgotPasswordButton->setStyleSheet("QPushButton{"
                                            "border-radius:  8px;"
                                            "background-color: rgb(61,65,68);"
                                            "color:  rgb(255, 255, 255);} "
                                            "QPushButton:hover{background-color:  rgb(88, 88, 88);}");
    ui->loginLabel->setStyleSheet("font: 34px;color: rgb(255,255,255);");
    ui->loginLineEdit->setStyleSheet("color:#989898;background-color: rgb(29, 31, 32);border-radius: 8px;");
    ui->passwordLineEdit->setStyleSheet("color:#989898;background-color: rgb(29, 31, 32);border-radius: 8px;");
    ui->imageLabel->setPixmap(QPixmap(":/img/whiteMenuIcon/cloud.png"));
    ui->passwordVisibilityButton->setIcon(QIcon(":/img/whiteMenuIcon/watchPass.png"));
    ui->loginLineEdit->setText("Логін");
    ui->passwordLineEdit->setText("Пароль");
    ui->authorizationErrorLabel->setVisible(false);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
}

void authorization::setWhiteUI()
{
    styleType = "white";
    setStyleSheet("authorization{background-color: rgb(231,224,223);}");
    ui->passwordVisibilityButton->setStyleSheet("background-color: rgb(231,224,223);border: 0px;");
    ui->loginButton->setStyleSheet("QPushButton{"
                                       "border-radius:  8px;"
                                       "background-color: rgb(251,244,243);"
                                       "color: rgb(61, 60, 59);} "
                                       "QPushButton:hover{background-color:  rgb(221, 214, 213);}");
    ui->forgotPasswordButton->setStyleSheet("QPushButton{"
                                            "border-radius:  8px;"
                                            "background-color: rgb(251,244,243);"
                                            "color: rgb(61, 60, 59);} "
                                            "QPushButton:hover{background-color:  rgb(221, 214, 213);}");
    ui->loginLabel->setStyleSheet("font: 34px;color: rgb(61, 60, 59);");
    ui->loginLineEdit->setStyleSheet("color:#989898;background-color: rgb(255, 255, 255);border-radius: 8px;");
    ui->passwordLineEdit->setStyleSheet("color:#989898;background-color: rgb(255, 255, 255);border-radius: 8px;");
    ui->imageLabel->setPixmap(QPixmap(":/img/blackMenuIcon/cloud.png"));
    ui->passwordVisibilityButton->setIcon(QIcon(":/img/blackMenuIcon/watchPass.png"));
    ui->loginLineEdit->setText("Логін");
    ui->passwordLineEdit->setText("Пароль");
    ui->authorizationErrorLabel->setVisible(false);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
}

void authorization::on_loginButton_clicked()
{
    //
    // Код для проверки правильности введения и в случае чего высвечивать надпись
    // про ошибку ввода пароля
    //



    ui->authorizationErrorLabel->setVisible(true);
}

