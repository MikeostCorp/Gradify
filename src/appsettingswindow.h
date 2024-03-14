#ifndef APPSETTINGSWINDOW_H
#define APPSETTINGSWINDOW_H

#include <QByteArray>
#include <QFile>
#include <QSettings>
#include <QWidget>

namespace Ui {
class AppSettingsWindow;
}

class AppSettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AppSettingsWindow(QWidget *parent = nullptr);
    ~AppSettingsWindow();
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
    void on_saveDBSettings_clicked();

private:
    Ui::AppSettingsWindow *ui;

signals:
    void changeThemeApp(const QString);
    void logoutSignal();

public slots:
    void setTheme(const QString &style);
};

#endif // APPSETTINGSWINDOW_H
