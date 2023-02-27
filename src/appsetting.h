#ifndef APPSETTING_H
#define APPSETTING_H

#include <QWidget>
#include <QFile>
#include <QByteArray>

namespace Ui {
class appSetting;
}

class appSetting : public QWidget
{
    Q_OBJECT

public:
    explicit appSetting(QWidget *parent = nullptr);
    ~appSetting();
    void changeEvent(QEvent *event) override;

private slots:
    void on_setWhiteStyle_clicked();

    void on_setBlackStyle_clicked();

private:
    Ui::appSetting *ui;

signals:
    void changeThemeApp(int);
};

#endif // APPSETTING_H
