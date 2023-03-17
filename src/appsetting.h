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

    void setSystemUI();

    void on_selectWhiteUIButton_clicked();

    void on_selectBlackUIButton_clicked();

    void on_selectWhiteUIRadioButton_clicked();

    void on_selectBlackUIRadioButton_clicked();

    void on_selectSystemUIButton_clicked();

    void on_selectSystemUIRadioButton_clicked();

private:
    Ui::appSetting *ui;

signals:
    void changeThemeApp(const QString);

public slots:
    void setThemeSettingUI(const QString style);

};

#endif // APPSETTING_H
