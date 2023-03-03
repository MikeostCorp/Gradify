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

    void on_pushButtonForgetPassword_clicked();

    void on_lineEditLogin_selectionChanged();

    void on_lineEditLogin_editingFinished();

    void on_lineEditPassword_selectionChanged();

    void on_lineEditPassword_editingFinished();

    void clearLineLogin(bool status);

    void clearLinePassword(bool status);

    void on_pushButtonWatchPassword_clicked();

    void on_pushButtonLogin_clicked();

private:
    Ui::authorization *ui;
    bool noWatchPassword;
    QString styleType;

public slots:
    void setThemeAuthorUI(QString style);
};

#endif // AUTHORIZATION_H
