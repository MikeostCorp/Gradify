#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>
#include <QSqlDatabase>
#include <QFile>
#include "customWidgets/qlineeditwithbutton.h"
#include <QSettings>

namespace Ui {
class authorization;
}

class authorization : public QWidget
{
    Q_OBJECT

public:
    explicit authorization(QWidget *parent = nullptr);
    ~authorization();

private slots:
    void setBlackUI();

    void setWhiteUI();

    void setSystemUI();

    void on_forgotPasswordButton_clicked();

    void loginClearButtonCliked();

    void passwordVisibilityButtonClicked();

    void on_loginButton_clicked();

    void on_rememberCheckBox_stateChanged(int arg1);



private:
    Ui::authorization *ui;

    QSqlDatabase authorizationDB;

    bool isPasswordHidden;

    QString styleType;

public slots:
    void setThemeAuthorUI(const QString style);
    void startAuthozation();

signals:
    void signalLogin(const QString);
};

#endif // AUTHORIZATION_H
