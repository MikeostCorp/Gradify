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
    void setBlackUI();

    void setWhiteUI();

    void on_pushSelectWhiteUIButton_clicked();

    void on_pushSelectBlackUIButton_clicked();

    void on_setWhiteStyleRadioButton_clicked();

    void on_setBlackStyleRadioButton_clicked();

private:
    Ui::appSetting *ui;

signals:
    void changeThemeApp(QString);

public slots:
    void setThemeSettingUI(QString style);
};

#endif // APPSETTING_H
