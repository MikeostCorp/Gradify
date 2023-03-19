#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QEvent>
#include <QFile>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QCloseEvent>

#include <appsetting.h>
#include <authorization.h>

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
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_studentsTableButton_clicked();

    void on_teachersTableButton_clicked();

    void on_gradesTableButton_clicked();

    void on_groupsTableButton_clicked();

    void clearStyleButtonTable();

    void on_settingsButton_clicked();

    void setBlackUI();

    void setWhiteUI();

    void setSystemUI();

    void mainWindowInit();

    void configDefault();

    void configRead();

    void configInit();

    void configWrite();

    void on_authorizationButton_clicked();

    void on_addRowButton_clicked();

    void on_deleteRowButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_subjectsTableButton_clicked();

    void clearSelectTable();

    void setEnabledButtons(bool status);

    void setEnabledActions(bool status);

    void on_addRowAction_triggered();

    void on_deleteRowAction_triggered();

    void on_editRowAction_triggered();

    void on_editRowButton_clicked();

    void on_openStudTabAction_triggered();

    void on_openTeachTabAction_triggered();

    void on_openGradesTabAction_triggered();

    void on_openGroupTabAction_triggered();

    void on_openSubjTabAction_triggered();

    void on_studentsReportButton_clicked();

    void on_teachersReportButton_clicked();

    void on_gradesReportButton_clicked();

    void on_groupsReportButton_clicked();

    void on_subjectsReportButton_clicked();

    void on_openManual_triggered();

    void on_studentsReportAction_triggered();

    void on_teachersReportAction_triggered();

    void on_groupsReportAction_triggered();

    void on_gradesReportAction_triggered();

    void on_subjectsReportAction_triggered();

private:
    Ui::MainWindow *ui;
    appSetting *settingWindow;
    authorization *authorizationWindow;

    QString defaultButtonTableStyle;
    QString selectButtonTableStyle;
    QString defaultSettingButtonStyle;
    QString defaultFilterButtonStyle;

    QMap<QString, QString> config;

    QFile cfgFile;
    QFile styleF;

    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;

    int row;
    int selectTable;

    bool isLogin;


public slots:
    void setThemeUI(const QString style);
    void succesfullyAuthorization(const QString login);

signals:
    void setThemeSettingsUI(const QString);
    void statusAuthorization(const bool);
};
#endif // MAINWINDOW_H
