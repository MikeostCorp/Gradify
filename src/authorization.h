#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>

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

    void on_forgotPasswordButton_clicked();

    void on_loginLineEdit_selectionChanged();

    void on_loginLineEdit_editingFinished();

    void on_passwordLineEdit_selectionChanged();

    void on_passwordLineEdit_editingFinished();

    void clearLineLogin(bool status);

    void clearLinePassword(bool status);

    void on_passwordVisibilityButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::authorization *ui;
    bool isPasswordHidden;
    QString styleType;

public slots:
    void setThemeAuthorUI(QString style);
};

#endif // AUTHORIZATION_H
