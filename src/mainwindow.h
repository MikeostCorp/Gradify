#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QEvent>
#include <QFile>

#include <appsetting.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeEvent(QEvent *event) override;

private slots:
    void on_studentsTableButton_clicked();

    void on_teachersTableButton_clicked();

    void on_gradesTableButton_clicked();

    void on_groupsTableButton_clicked();

    void clearStyleButtonTable();

    void on_settingsButton_clicked();

    void setBlackUI();

    void setWhiteUI();

private:
    Ui::MainWindow *ui;
    appSetting *openSetting;

    int appThemeStyle; // if 0 - dark, 1 - white;
    QString defaultButtonTableStyle;
    QString selectButtonTableStyle;
    QString defaultSettingButtonStyle;

    QFile cfgFile;
    QString cfgData;


public slots:
    void setThemeUI(int style);

};
#endif // MAINWINDOW_H
