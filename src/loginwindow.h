#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QFile>
#include <QSettings>
#include <QWidget>
#include "customWidgets/qlineeditwithbutton.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void setBlackUI();

    void setWhiteUI();

    void setSystemUI();

    void on_forgotPasswordButton_clicked();

    void loginClearButtonCliked();

    void passwordVisibilityButtonClicked();

    void on_loginButton_clicked();

private:
    Ui::LoginWindow *ui;

    bool isPasswordHidden;

    QString styleType;

public slots:
    void setTheme(const QString &style);
    void startAuthozation();

signals:
    void signalLogin(const QString);
};

#endif // LOGINWINDOW_H
