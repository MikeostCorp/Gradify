#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtWidgets/qpushbutton.h"
#include <QMainWindow>
#include <QString>
#include <QEvent>
#include <QFile>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QCloseEvent>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QSettings>

#include <appsetting.h>
#include <authorization.h>
#include <filterform.h>
#include <queryform.h>
#include <aboutapp.h>
#include <customWidgets/qsearchbar.h>

#include <editForms/editgrade.h>
#include <editForms/editgroup.h>
#include <editForms/editstudent.h>
#include <editForms/editsubject.h>
#include <editForms/editteacher.h>

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

protected:
    void mousePressEvent(QMouseEvent *event) override;

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

    void setCurrentIconAction();

    void mainWindowInit();

    void configDefault();

    void configInit();

    void configWrite(const QString &key, const QVariant &value);

    void userLogout();

    void on_authorizationButton_clicked();

    void on_addRowButton_clicked();

    void on_deleteRowButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_subjectsTableButton_clicked();

    void clearSelectTable();

    void closeAllPopUpWindow();

    void closeAllEditForm();

    void setEnabledButtons(bool status);

    void setEnabledActions(bool status);

    void setEnabledEditButton(bool status);

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

    void on_currentTableReportAction_triggered();

    void on_currentTableReportButton_clicked();

    void on_about_triggered();

    void on_filterButton_clicked();

    void on_queryButton_clicked();

    QGraphicsDropShadowEffect *paintDropShadowEffect();

    QMap<QString, QString> getColumnsAndDatatypes(const QString &tableName);

    QStringList getCurrentItemTable();

    QStringList getRowDate(int row);

private:
    Ui::MainWindow *ui;

    appSetting *settingWindow;
    authorization *authorizationWindow;
    filterForm *filterWindow;
    queryForm *queryWindow;
    aboutApp *aboutAppAction;

    editGrade *gradeEditForm;
    editGroup *groupEditForm;
    editStudent *studentEditForm;
    editSubject *subjectEditForm;
    editTeacher *teacherEditForm;

    QString selectButtonTableStyle;
    QString selectButtonAuthStyle;
    QString theme;

    QFile cfgFile;
    QFile styleF;

    QSqlDatabase db;
    QSqlQuery *query;
    QSqlQueryModel *queryModel;
    QSqlTableModel *model;

    QMessageBox logoutMessageBox;
    QPushButton *yesButton;

    QGraphicsDropShadowEffect *effect;

    int row;
    int currentSelectTable;

    bool isLogin;

public slots:
    void setThemeUI(const QString style);
    void succesfullyAuthorization(const QString login);
    void setFilterForTable(const QString filterQuery, const QString currentColumnFilter);
    void clearFilterForTable();
    void goSearch();

signals:
    void setThemeSettingsUI(const QString);
    void statusAuthorization(const bool);
    void setTableForFilter(const QMap<QString, QString>);
    void setDataEditForm(QString, QStringList);
};
#endif // MAINWINDOW_H
