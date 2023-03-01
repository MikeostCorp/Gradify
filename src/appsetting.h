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

private:
    Ui::appSetting *ui;

signals:
    void changeThemeApp(int);

public slots:
    void setThemeSettingUI(int style);
};

#endif // APPSETTING_H
