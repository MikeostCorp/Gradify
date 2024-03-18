#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QEvent>
#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <QMainWindow>
#include <QMap>
#include <QMessageBox>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QString>
#include <QTableView>
#include "QtWidgets/qpushbutton.h"

#include <QTranslator>

#include <aboutappwindow.h>
#include <appsettingswindow.h>
#include <filterwindow.h>
#include <loginwindow.h>
#include <querywindow.h>

#include <RecordsWindows/gradewindow.h>
#include <RecordsWindows/groupwindow.h>
#include <RecordsWindows/studentwindow.h>
#include <RecordsWindows/subjectwindow.h>
#include <RecordsWindows/teacherwindow.h>

#include <StatisticsWindows/gradestatistics.h>
#include <StatisticsWindows/groupstatistics.h>
#include <StatisticsWindows/studentstatistics.h>
#include <StatisticsWindows/subjectstatistics.h>
#include <StatisticsWindows/teacherstatistics.h>

#include <DatabaseHandler/databasehandler.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeEvent(QEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    enum TableType { Teachers, Subjects, Students, Grades, Groups, None };
    Q_ENUM(TableType);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;

    DatabaseHandler *dbHandler;

    QTranslator translator;

    AppSettingsWindow *appSettingsWindow;
    LoginWindow *loginWindow;
    FilterWindow *filterWindow;
    QueryWindow *queryWindow;
    AboutAppWindow *aboutAppWindow;

    GradeWindow *gradeWindow;
    GroupWindow *groupWindow;
    StudentWindow *studentWindow;
    SubjectWindow *subjectWindow;
    TeacherWindow *teacherWindow;

    GradeStatisticsWindow *gradeStatisticsWindow;
    GroupStatisticsWindow *groupStatisticsWindow;
    StudentStatisticsWindow *studentStatisticsWindow;
    SubjectStatisticsWindow *subjectStatisticsWindow;
    TeacherStatisticsWindow *teacherStatisticsWindow;

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

    TableType currentSelectTable;

    bool isLogin;

public slots:
    void setTheme(const QString &style);
    void authorization(const QString &login);
    void setFilterForTable(const QString &filterQuery, const QString &currentColumnFilter);
    void clearFilterForTable();
    void goSearch();
    void setDataToModel(QStringList dataList, bool isNewRow);
    void setQueryForTable(QString query);
    void openTable(TableType tableType, const QString &tableName);
    void fillTable(const QStringList &columns, const QJsonArray &data);
    void handleReply(const QByteArray &data, const QStringList &headers);

private slots:
    void initDatabaseHandler();
    void initWindowsObjects();
    void initPopUpWindowsGraphics();
    void setDefaultMainWindowState();
    void setTableWidgetSettings();
    void connectThemeChangeSignals();
    void connectLoginLogoutSignals();
    void connectFiltersAndRequests();
    void connectCloseEvents();
    void connectButtonsAndActions();
    void openTeachersTable();
    void openSubjectsTable();
    void openStudentsTable();
    void openGradesTable();
    void openGroupsTable();

    void clearStyleButtonTable();

    void openSettingsWindow();

    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

    void setCurrentIconAction();
    void initMainWindow();
    void initConfigDefault();
    void initConfig();
    void writeConfig(const QString &key, const QVariant &value);
    void logoutUser();

    void handleLogin();
    void addRowToTable();
    void editRowInTable();
    void deleteRowFromTable();
    void on_tableView_clicked(const QModelIndex &index);

    void clearSelectTable();
    void closeAllPopUpWindow();
    void closeAllEditForms();
    void closeAllStatisticsForm();

    void setEnabledButtons(const bool &status);
    void setEnabledActions(const bool &status);
    void setEnabledEditButton(const bool &status);

    void generateStudentsGroupReport();
    void generateTeachersReport();
    void generateGradesReport();
    void generateGroupsReport();
    void generateSubjectsReport();

    void openManual();

    void generateCurrentTableReport();

    void openAboutWindow();
    void toggleFilterWindow();
    void toggleQueryWindow();

    void printDocumentToPDF(const QString path, const QString html);
    void printDocumentToHTML(const QString path, const QString html);

    QString getHeaderHTML();
    void fillHTMLTable(QString &textHTML, QTableView *tableView);

    QGraphicsDropShadowEffect *paintDropShadowEffect();

    QMap<QString, QString> getColumnsNamesAndDatatypes(const QString &tableName);

    QStringList getCurrentItemTable();
    QStringList getRowData(const int &row);
    QStringList getGroupsNames();
    QStringList getGroupsSpecial();
    QStringList getStudentsNames();
    QStringList getTeachersNames();
    QStringList getSubjectsNames();
    QStringList getSubjectsTypes();
    QStringList getCategoryTeachers();

    void openStatisticsWindow();

    QString modelDataToString(QAbstractItemModel *model);

    void exportDataToCSV();
    void exportDataToTXT();

    void on_actionEnglish_Translate_triggered();

    void on_actionUkrainian_Translate_triggered();

signals:
    void setThemeSettingsUI(const QString);
    void statusAuthorization(const bool);
    void changedGradeTable(const int);
    void setTableForFilter(const QMap<QString, QString>);
    void setDataEditForm(QString, QStringList);
    void sendGroupsList(QStringList);
    void sendTeachersList(QStringList);
    void sendStudentsList(QStringList);
    void sendCurrentGroup(QString);
    void sendSubjectsList(QStringList);
    void createNewRow();
    void updateStatisticsSignal();
    void updateStatisticsComboBoxSignal();
    void clearInputFields();
};
#endif // MAINWINDOW_H
