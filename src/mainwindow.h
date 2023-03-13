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

private slots:
    void on_studentsTableButton_clicked();

    void on_teachersTableButton_clicked();

    void on_gradesTableButton_clicked();

    void on_groupsTableButton_clicked();

    void clearStyleButtonTable();

    void on_settingsButton_clicked();

    void setBlackUI();

    void setWhiteUI();

    void mainWindowInit();

    void configDefault();

    void configRead();

    void configInit();

    void configWrite();

    void on_authorizationButton_clicked();

    void on_addRowButton_clicked();

    void on_deleteRowButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_itemTableButton_clicked();

private:
    Ui::MainWindow *ui;
    appSetting *openSetting;
    authorization *openAuthorization;

    QString defaultButtonTableStyle;
    QString selectButtonTableStyle;
    QString defaultSettingButtonStyle;

    QMap<QString, QString> config;

    QFile cfgFile;

    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    int row;

public slots:
    void setThemeUI(const QString style);

signals:
    void setThemeSettingsUI(const QString);
};
#endif // MAINWINDOW_H
