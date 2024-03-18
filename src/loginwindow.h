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

    void loginProcessing();

private:
    Ui::LoginWindow *ui;

    bool isPasswordHidden;

    QString styleType;

public slots:
    void setTheme(const QString &style);
    void startAuthozation();
    void loginFailed();
    void loginSuccessful();
    void clearInputFields();

signals:
    void signalLogin(const QString &login);
    void loginAttempt(const QString &login, const QString &password);
};

#endif // LOGINWINDOW_H
