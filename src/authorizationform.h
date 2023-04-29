#ifndef authorizationFormFORM_H
#define authorizationFormFORM_H

#include <QWidget>
#include <QSqlDatabase>
#include <QFile>
#include "customWidgets/qlineeditwithbutton.h"
#include <QSettings>

namespace Ui {
class authorizationForm;
}

class authorizationForm : public QWidget
{
    Q_OBJECT

public:
    explicit authorizationForm(QWidget *parent = nullptr);
    ~authorizationForm();

private slots:
    void setBlackUI();

    void setWhiteUI();

    void setSystemUI();

    void on_forgotPasswordButton_clicked();

    void loginClearButtonCliked();

    void passwordVisibilityButtonClicked();

    void on_loginButton_clicked();

private:
    Ui::authorizationForm *ui;

    QSqlDatabase authorizationFormDB;

    bool isPasswordHidden;

    QString styleType;

public slots:
    void setTheme(const QString &style);
    void startAuthozation();

signals:
    void signalLogin(const QString);
};

#endif // authorizationFormFORM_H
