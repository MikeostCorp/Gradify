#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeyEvent>
#include <QPageSize>
#include <QPrinter>
#include <QStandardPaths>
#include <QTextDocument>

#include <DatabaseHandler/databasehandler.h>
#include <customWidgets/qsearchbar.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMainWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMainWindow()
{
    setWindowTitle("Gradify");

    initDatabaseHandler();
    initWindowsObjects();
    initPopUpWindowsGraphics();
    setDefaultMainWindowState();
    setTableWidgetSettings();

    connectThemeChangeSignals();

    // update statistics
    connect(this,
            &MainWindow::updateStatisticsSignal,
            studentStatisticsWindow,
            &StudentStatisticsWindow::updateGroupComboBox);
    connect(this,
            &MainWindow::updateStatisticsComboBoxSignal,
            groupStatisticsWindow,
            &GroupStatisticsWindow::setGroupComboBox);

    initConfig();

    connectLoginLogoutSignals();

    connectFiltersAndRequests();

    // clear searchbar & filter
    connect(ui->searchLineEdit,
            &QSearchBar::clickedClearButton,
            this,
            &MainWindow::clearFilterForTable);

    connectCloseEvents();

    // close popup windows on click menubar
    connect(ui->menuBar, &QMenuBar::triggered, this, &MainWindow::closeAllPopUpWindow);
    connect(ui->searchLineEdit, &QSearchBar::haveFocus, this, &MainWindow::closeAllPopUpWindow);
    connect(ui->searchLineEdit, &QSearchBar::buttonSearchClick, this, &MainWindow::goSearch);
    connect(ui->searchLineEdit, &QLineEdit::returnPressed, this, &MainWindow::goSearch);

    // send list to edit form
    connect(this, &MainWindow::sendGroupsList, studentWindow, &StudentWindow::setComboBox);

    // get data from edit form
    connect(gradeWindow, &GradeWindow::sendData, this, &MainWindow::setDataToModel);
    connect(groupWindow, &GroupWindow::sendData, this, &MainWindow::setDataToModel);
    connect(studentWindow, &StudentWindow::sendData, this, &MainWindow::setDataToModel);
    connect(subjectWindow, &SubjectWindow::sendData, this, &MainWindow::setDataToModel);
    connect(teacherWindow, &TeacherWindow::sendData, this, &MainWindow::setDataToModel);

    // custom message box
    logoutMessageBox.setIcon(QMessageBox::Question);
    yesButton = logoutMessageBox.addButton(tr("Так"), QMessageBox::YesRole);
    logoutMessageBox.addButton(tr("Ні"), QMessageBox::NoRole);
    logoutMessageBox.setDefaultButton(yesButton);
    logoutMessageBox.setWindowTitle("Разлогін");
    logoutMessageBox.setText("Ви дійсно хочете вийти з аккаунта?");

    connectButtonsAndActions();

    connect(loginWindow, &LoginWindow::loginAttempt, dbHandler, &DatabaseHandler::signUserIn);
    connect(appSettingsWindow, &AppSettingsWindow::setAPI, dbHandler, &DatabaseHandler::setAPIKey);

    connect(dbHandler, &DatabaseHandler::loginFailed, loginWindow, &LoginWindow::loginFailed);
    connect(dbHandler, &DatabaseHandler::loginSuccessful, loginWindow, &LoginWindow::loginSuccessful);

    connect(this, &MainWindow::clearInputFields, loginWindow, &LoginWindow::clearInputFields);
}

void MainWindow::initDatabaseHandler()
{
    dbHandler = new DatabaseHandler(this);
    connect(dbHandler, &DatabaseHandler::replyReceived, this, &MainWindow::handleReply);
}

void MainWindow::initWindowsObjects()
{
    appSettingsWindow = new AppSettingsWindow();
    loginWindow = new LoginWindow();
    filterWindow = new FilterWindow(this);
    queryWindow = new QueryWindow(this);
    aboutAppWindow = new AboutAppWindow();

    gradeWindow = new GradeWindow();
    groupWindow = new GroupWindow();
    studentWindow = new StudentWindow();
    subjectWindow = new SubjectWindow();
    teacherWindow = new TeacherWindow();

    gradeStatisticsWindow = new GradeStatisticsWindow();
    groupStatisticsWindow = new GroupStatisticsWindow();
    studentStatisticsWindow = new StudentStatisticsWindow();
    subjectStatisticsWindow = new SubjectStatisticsWindow();
    teacherStatisticsWindow = new TeacherStatisticsWindow();
}

void MainWindow::initPopUpWindowsGraphics()
{
    filterWindow->setGraphicsEffect(paintDropShadowEffect());
    queryWindow->setGraphicsEffect(paintDropShadowEffect());
    ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::setDefaultMainWindowState()
{
    isLogin = false;
    currentSelectTable = TableType::None;
    setEnabledButtons(false);
    setEnabledActions(false);
    setEnabledEditButton(false);
}

void MainWindow::setTableWidgetSettings()
{
    ui->tableWidget->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::connectThemeChangeSignals()
{
    // theme change after config init
    connect(this, &MainWindow::setThemeSettingsUI, appSettingsWindow, &AppSettingsWindow::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, loginWindow, &LoginWindow::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, aboutAppWindow, &AboutAppWindow::setTheme);

    connect(this, &MainWindow::setThemeSettingsUI, gradeWindow, &GradeWindow::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, groupWindow, &GroupWindow::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, studentWindow, &StudentWindow::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, subjectWindow, &SubjectWindow::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, teacherWindow, &TeacherWindow::setTheme);

    connect(this,
            &MainWindow::setThemeSettingsUI,
            gradeStatisticsWindow,
            &GradeStatisticsWindow::setTheme);
    connect(this,
            &MainWindow::setThemeSettingsUI,
            groupStatisticsWindow,
            &GroupStatisticsWindow::setTheme);
    connect(this,
            &MainWindow::setThemeSettingsUI,
            studentStatisticsWindow,
            &StudentStatisticsWindow::setTheme);
    connect(this,
            &MainWindow::setThemeSettingsUI,
            subjectStatisticsWindow,
            &SubjectStatisticsWindow::setTheme);
    connect(this,
            &MainWindow::setThemeSettingsUI,
            teacherStatisticsWindow,
            &TeacherStatisticsWindow::setTheme);

    // theme change in settings window
    connect(appSettingsWindow, &AppSettingsWindow::changeThemeApp, this, &MainWindow::setTheme);
    connect(appSettingsWindow,
            &AppSettingsWindow::changeThemeApp,
            loginWindow,
            &LoginWindow::setTheme);
    connect(appSettingsWindow,
            &AppSettingsWindow::changeThemeApp,
            aboutAppWindow,
            &AboutAppWindow::setTheme);

    connect(appSettingsWindow,
            &AppSettingsWindow::changeThemeApp,
            gradeWindow,
            &GradeWindow::setTheme);
    connect(appSettingsWindow,
            &AppSettingsWindow::changeThemeApp,
            groupWindow,
            &GroupWindow::setTheme);
    connect(appSettingsWindow,
            &AppSettingsWindow::changeThemeApp,
            studentWindow,
            &StudentWindow::setTheme);
    connect(appSettingsWindow,
            &AppSettingsWindow::changeThemeApp,
            subjectWindow,
            &SubjectWindow::setTheme);
    connect(appSettingsWindow,
            &AppSettingsWindow::changeThemeApp,
            teacherWindow,
            &TeacherWindow::setTheme);

    connect(appSettingsWindow,
            &AppSettingsWindow::changeThemeApp,
            gradeStatisticsWindow,
            &GradeStatisticsWindow::setTheme);
    connect(appSettingsWindow,
            &AppSettingsWindow::changeThemeApp,
            groupStatisticsWindow,
            &GroupStatisticsWindow::setTheme);
    connect(appSettingsWindow,
            &AppSettingsWindow::changeThemeApp,
            studentStatisticsWindow,
            &StudentStatisticsWindow::setTheme);
    connect(appSettingsWindow,
            &AppSettingsWindow::changeThemeApp,
            subjectStatisticsWindow,
            &SubjectStatisticsWindow::setTheme);
    connect(appSettingsWindow,
            &AppSettingsWindow::changeThemeApp,
            teacherStatisticsWindow,
            &TeacherStatisticsWindow::setTheme);
}

void MainWindow::connectLoginLogoutSignals()
{
    connect(loginWindow, &LoginWindow::signalLogin, this, &MainWindow::authorization);
    connect(appSettingsWindow, &AppSettingsWindow::logoutSignal, this, &MainWindow::logoutUser);
}

void MainWindow::connectFiltersAndRequests()
{
    connect(filterWindow, &FilterWindow::sendFilter, this, &MainWindow::setFilterForTable);
    connect(filterWindow, &FilterWindow::clearFilter, this, &MainWindow::clearFilterForTable);
    connect(this, &MainWindow::setTableForFilter, filterWindow, &FilterWindow::setListTable);
    connect(queryWindow, &QueryWindow::sendQuery, this, &MainWindow::setQueryForTable);
    connect(queryWindow, &QueryWindow::sendFilter, this, &MainWindow::setFilterForTable);
    connect(queryWindow, &QueryWindow::clearFilter, this, &MainWindow::clearFilterForTable);
    connect(this, &MainWindow::changedGradeTable, queryWindow, &QueryWindow::selectedGradeTable);
}

void MainWindow::connectCloseEvents()
{
    // close pop-up windows on click tableView (need fix empty space)
    connect(ui->tableWidget->horizontalHeader(),
            &QHeaderView::sectionClicked,
            this,
            &MainWindow::closeAllPopUpWindow);
    connect(ui->tableWidget->verticalHeader(),
            &QHeaderView::sectionClicked,
            this,
            &MainWindow::closeAllPopUpWindow);
    connect(ui->tableWidget, &QAbstractItemView::clicked, this, &MainWindow::closeAllPopUpWindow);
    connect(ui->tableWidget, &QTableWidget::clicked, this, &MainWindow::closeAllPopUpWindow);

    // close pop-up windows on click any buttons
    for (QPushButton *button : findChildren<QPushButton *>()) {
        if (button->objectName() not_eq "filterButton" and button->objectName() not_eq "queryButton"
            and button->objectName() not_eq "filterPushButton"
            and button->objectName() not_eq "succesStudentPushButton"
            and button->objectName() not_eq "avgScorePushButton"
            and button->objectName() not_eq "clearFilterPushButton"
            and button->objectName() not_eq "mySQLPushButton"
            and button->objectName() not_eq "searchGradeStudentButton") {
            connect(button, &QPushButton::clicked, this, &MainWindow::closeAllPopUpWindow);
        }
        if (button->objectName() not_eq "editRowButton"
            and button->objectName() not_eq "settingsButton"
            and button->objectName() not_eq "addRowButton") {
            connect(button, &QPushButton::clicked, this, &MainWindow::closeAllEditForms);
        }
    }
}

void MainWindow::connectButtonsAndActions()
{
    connect(ui->studentsTableButton, &QPushButton::clicked, this, &MainWindow::openStudentsTable);
    connect(ui->teachersTableButton, &QPushButton::clicked, this, &MainWindow::openTeachersTable);
    connect(ui->gradesTableButton, &QPushButton::clicked, this, &MainWindow::openGradesTable);
    connect(ui->groupsTableButton, &QPushButton::clicked, this, &MainWindow::openGroupsTable);
    connect(ui->subjectsTableButton, &QPushButton::clicked, this, &MainWindow::openSubjectsTable);

    connect(ui->addRowAction, &QAction::triggered, this, &MainWindow::addRowToTable);
    connect(ui->addRowButton, &QPushButton::clicked, this, &MainWindow::addRowToTable);

    connect(ui->authorizationButton, &QPushButton::clicked, this, &MainWindow::handleLogin);
    connect(ui->deleteRowAction, &QAction::triggered, this, &MainWindow::deleteRowFromTable);
    connect(ui->deleteRowButton, &QPushButton::clicked, this, &MainWindow::deleteRowFromTable);

    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::openSettingsWindow);

    connect(ui->editRowButton, &QPushButton::clicked, this, &MainWindow::editRowInTable);
    connect(ui->editRowAction, &QAction::triggered, this, &MainWindow::editRowInTable);

    connect(ui->openTeachTabAction, &QAction::triggered, this, &MainWindow::openTeachersTable);
    connect(ui->openStudTabAction, &QAction::triggered, this, &MainWindow::openStudentsTable);
    connect(ui->openSubjTabAction, &QAction::triggered, this, &MainWindow::openSubjectsTable);
    connect(ui->openGradesTabAction, &QAction::triggered, this, &MainWindow::openGradesTable);
    connect(ui->openGroupTabAction, &QAction::triggered, this, &MainWindow::openGroupsTable);

    connect(ui->currentTableReportAction,
            &QAction::triggered,
            this,
            &MainWindow::generateCurrentTableReport);
    connect(ui->currentTableReportButton,
            &QPushButton::clicked,
            this,
            &MainWindow::generateCurrentTableReport);
    connect(ui->studentsReportAction,
            &QAction::triggered,
            this,
            &MainWindow::generateStudentsGroupReport);
    connect(ui->studentsReportButton,
            &QPushButton::clicked,
            this,
            &MainWindow::generateStudentsGroupReport);
    connect(ui->teachersReportAction,
            &QAction::triggered,
            this,
            &MainWindow::generateTeachersReport);
    connect(ui->teachersReportButton,
            &QPushButton::clicked,
            this,
            &MainWindow::generateTeachersReport);
    connect(ui->gradesReportAction, &QAction::triggered, this, &MainWindow::generateGradesReport);
    connect(ui->gradesReportButton, &QPushButton::clicked, this, &MainWindow::generateGradesReport);
    connect(ui->groupsReportAction, &QAction::triggered, this, &MainWindow::generateGroupsReport);
    connect(ui->groupsReportButton, &QPushButton::clicked, this, &MainWindow::generateGroupsReport);
    connect(ui->subjectsReportAction,
            &QAction::triggered,
            this,
            &MainWindow::generateSubjectsReport);
    connect(ui->subjectsReportButton,
            &QPushButton::clicked,
            this,
            &MainWindow::generateSubjectsReport);

    connect(ui->openManual, &QAction::triggered, this, &MainWindow::openManual);
    connect(ui->about, &QAction::triggered, this, &MainWindow::openAboutWindow);
    connect(ui->filterButton, &QPushButton::clicked, this, &MainWindow::toggleFilterWindow);
    connect(ui->queryButton, &QPushButton::clicked, this, &MainWindow::toggleQueryWindow);
    connect(ui->statisticsButton, &QPushButton::clicked, this, &MainWindow::openStatisticsWindow);

    connect(ui->actionCSV, &QAction::triggered, this, &MainWindow::exportDataToCSV);
    connect(ui->actionTXT, &QAction::triggered, this, &MainWindow::exportDataToTXT);
}

void MainWindow::initConfigDefault()
{
    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf",
                             QSettings::IniFormat);

    settingsConfig
        .setValue("url", "https://gradifydatabase-default-rtdb.europe-west1.firebasedatabase.app/");
    settingsConfig
        .setValue("apiKey", "AIzaSyBH39ltGfdl_kbgLbBHfAMz8fyZaJk8q6g");
    settingsConfig.setValue("theme", "system");
}

void MainWindow::initConfig()
{
    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf",
                             QSettings::IniFormat);

    if (settingsConfig.allKeys().empty()) {
        initConfigDefault();
    }

    if (settingsConfig.contains("theme")) {
        setTheme(settingsConfig.value("theme").toString());

        emit setThemeSettingsUI(theme);
    }

    if (settingsConfig.contains("apiKey")) {
        dbHandler->setAPIKey(settingsConfig.value("apiKey").toString());
    } else {
        return;
    }

    if (settingsConfig.contains("userlogin") and settingsConfig.contains("userpassword")) {
        dbHandler->signUserIn(settingsConfig.value("userlogin").toString(), settingsConfig.value("userpassword").toString());
    }
}

void MainWindow::writeConfig(const QString &key, const QVariant &value)
{
    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf",
                             QSettings::IniFormat);
    settingsConfig.setValue(key, value);
}

void MainWindow::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::ActivationChange) {
        if (isActiveWindow()) {
            setWindowOpacity(1);
        } else {
            setWindowOpacity(0.97);
        }
    } else if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (event->Close) {
        QApplication::closeAllWindows();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton and filterWindow->isVisible()
        and not filterWindow->underMouse()) {
        filterWindow->close();
    } else if (event->button() == Qt::LeftButton and queryWindow->isVisible()
               and not queryWindow->underMouse()) {
        queryWindow->close();
    }
}

void MainWindow::fillTable(const QStringList &columns, const QJsonArray &data)
{
    qsizetype rowCount = data.size();
    qsizetype columnCount = columns.size();

    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(columnCount);
    ui->tableWidget->setHorizontalHeaderLabels(columns);

    for (qsizetype i = 0; i < rowCount; ++i) {
        QJsonObject item = data[i].toObject();
        for (qsizetype j = 0; j < columnCount; ++j) {
            QString columnName = columns[j];
            QTableWidgetItem *tableItem = new QTableWidgetItem(item.value(columnName).toString());
            ui->tableWidget->setItem(i, j, tableItem);
        }
    }
}

void MainWindow::openTable(TableType tableType, const QString &tableName)
{
    clearSelectTable();

    setWindowTitle("Gradify - (" + tableName + ")");
    currentSelectTable = tableType;
    clearStyleButtonTable();
    setEnabledEditButton(true);

    ui->searchLineEdit->clear();

    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf",
                             QSettings::IniFormat);

    if (settingsConfig.value("url").isNull()) {
        qDebug() << "Gradify - " << tableName << " - URL IS NULL";
        return;
    }

    QStringList headers;

    switch (tableType) {
    case TableType::Teachers:
        ui->teachersTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/teachersIco.png"));
        ui->teachersTableButton->setStyleSheet(selectButtonTableStyle);
        headers = {"Прізвище",
                   "Ім'я",
                   "По батькові",
                   "Номер телефона",
                   "Дата народження",
                   "Адреса проживання",
                   "Категорія",
                   "Спеціалізація"};
        break;
    case TableType::Subjects:
        ui->subjectsTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/subjectsIco.png"));
        ui->subjectsTableButton->setStyleSheet(selectButtonTableStyle);
        headers = {"Назва",
                   "Тип",
                   "Викладач",
                   "Всього годин",
                   "Кількість лекційних годин",
                   "Кількість лабораторних годин",
                   "Кількість семінарних годин",
                   "Кількість годин на самостійні роботи",
                   "Семестр в якому вивчається",
                   "Семестровий контроль"};
        break;
    case TableType::Students:
        ui->studentsTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/studentsIco.png"));
        ui->studentsTableButton->setStyleSheet(selectButtonTableStyle);
        headers = {"Прізвище",
                   "Ім'я",
                   "По батькові",
                   "Дата народження",
                   "Адреса проживання",
                   "Номер телефона",
                   "Номер паспорту",
                   "Група",
                   "ІНН"};
        break;
    case TableType::Grades:
        ui->gradesTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/gradesIco.png"));
        ui->gradesTableButton->setStyleSheet(selectButtonTableStyle);
        headers = {"Предмет", "Отримувач", "Оцінка", "Тип оцінки", "Дата отримання"};
        break;
    case TableType::Groups:
        ui->groupsTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/groupsIco.png"));
        ui->groupsTableButton->setStyleSheet(selectButtonTableStyle);
        headers = {"Назва",
                   "Спеціальність",
                   "Рік початку навчання",
                   "Рік закінчення навчання",
                   "Куратор",
                   "Староста"};
        break;
    case TableType::None:
        break;
    }

    dbHandler->getReply(tableName, headers);

    //emit setTableForFilter(getColumnsNamesAndDatatypes(tableName));
    //emit changedGradeTable(tableType);
}

void MainWindow::handleReply(const QByteArray &data, const QStringList &headers)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (!doc.isNull() && doc.isArray()) {
        fillTable(headers, doc.array());
    }
}

void MainWindow::openTeachersTable()
{
    openTable(TableType::Teachers, "Викладачі");
}

void MainWindow::openSubjectsTable()
{
    openTable(TableType::Subjects, "Предмети");
}

void MainWindow::openStudentsTable()
{
    openTable(TableType::Students, "Студенти");
}

void MainWindow::openGradesTable()
{
    openTable(TableType::Grades, "Оцінки");
}

void MainWindow::openGroupsTable()
{
    openTable(TableType::Groups, "Групи");
}

void MainWindow::clearSelectTable()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    currentSelectTable = TableType::None;
}

void MainWindow::closeAllPopUpWindow()
{
    filterWindow->close();
    queryWindow->close();
}

void MainWindow::closeAllEditForms()
{
    gradeWindow->close();
    groupWindow->close();
    studentWindow->close();
    subjectWindow->close();
    teacherWindow->close();
}

void MainWindow::closeAllStatisticsForm()
{
    gradeStatisticsWindow->close();
    groupStatisticsWindow->close();
    studentStatisticsWindow->close();
    subjectStatisticsWindow->close();
    teacherStatisticsWindow->close();
}

void MainWindow::setEnabledButtons(const bool &status)
{
    ui->subjectsReportButton->setEnabled(status);
    ui->gradesReportButton->setEnabled(status);
    ui->groupsReportButton->setEnabled(status);
    ui->teachersReportButton->setEnabled(status);
    ui->studentsReportButton->setEnabled(status);
    ui->currentTableReportButton->setEnabled(status);

    ui->gradesTableButton->setEnabled(status);
    ui->studentsTableButton->setEnabled(status);
    ui->subjectsTableButton->setEnabled(status);
    ui->teachersTableButton->setEnabled(status);
    ui->groupsTableButton->setEnabled(status);
}

void MainWindow::setEnabledActions(const bool &status)
{
    ui->openGradesTabAction->setEnabled(status);
    ui->openGroupTabAction->setEnabled(status);
    ui->openStudTabAction->setEnabled(status);
    ui->openSubjTabAction->setEnabled(status);
    ui->openTeachTabAction->setEnabled(status);

    ui->currentTableReportAction->setEnabled(status);
    ui->gradesReportAction->setEnabled(status);
    ui->groupsReportAction->setEnabled(status);
    ui->studentsReportAction->setEnabled(status);
    ui->teachersReportAction->setEnabled(status);
    ui->subjectsReportAction->setEnabled(status);

    ui->menu_2->setEnabled(status);
}

void MainWindow::setEnabledEditButton(const bool &status)
{
    ui->addRowAction->setEnabled(status);
    ui->editRowAction->setEnabled(status);
    ui->deleteRowAction->setEnabled(status);

    ui->addRowButton->setEnabled(status);
    ui->editRowButton->setEnabled(status);
    ui->deleteRowButton->setEnabled(status);
    ui->filterButton->setEnabled(status);
    ui->searchLineEdit->setEnabled(status);
    ui->queryButton->setEnabled(status);
    ui->statisticsButton->setEnabled(status);
}

void MainWindow::clearStyleButtonTable()
{
    ui->studentsTableButton->setStyleSheet("");
    ui->teachersTableButton->setStyleSheet("");
    ui->gradesTableButton->setStyleSheet("");
    ui->groupsTableButton->setStyleSheet("");
    ui->subjectsTableButton->setStyleSheet("");

    ui->studentsTableButton->setIcon(QIcon(":/img/blueMenuIcon/studentsIco.png"));
    ui->teachersTableButton->setIcon(QIcon(":/img/blueMenuIcon/teachersIco.png"));
    ui->gradesTableButton->setIcon(QIcon(":/img/blueMenuIcon/gradesIco.png"));
    ui->groupsTableButton->setIcon(QIcon(":/img/blueMenuIcon/groupsIco.png"));
    ui->subjectsTableButton->setIcon(QIcon(":/img/blueMenuIcon/subjectsIco.png"));
}

void MainWindow::setTheme(const QString &style)
{
    if (style == "black") {
        theme = "black";
        setBlackUI();
    } else if (style == "white") {
        theme = "white";
        setWhiteUI();
    } else {
        theme = "system";
        setSystemUI();
    }

    writeConfig("theme", theme);
}

void MainWindow::authorization(const QString &login)
{
    setEnabledButtons(true);
    setEnabledActions(true);

    ui->authorizationButton->setText(" Привіт, " + login + "!");
    ui->authorizationButton->setStyleSheet(selectButtonAuthStyle);

    isLogin = true;
}

void MainWindow::setFilterForTable(const QString &filterQuery, const QString &currentColumnFilter)
{
    model->setFilter(filterQuery);
    //ui->tableWidget->setModel(model);

    for (int i = 0; i < ui->tableWidget->model()->columnCount(); ++i) {
        if (ui->tableWidget->model()->headerData(i, Qt::Horizontal).toString()
            == currentColumnFilter) {
            ui->tableWidget->selectColumn(i);
            break;
        }
    }

    // debug
    //QMessageBox::information(this, "", filterQuery);
}

void MainWindow::openSettingsWindow()
{
    appSettingsWindow->show();

    if (appSettingsWindow->isVisible()) {
        appSettingsWindow->raise();
    }
}

void MainWindow::logoutUser()
{
    isLogin = false;
    setEnabledButtons(false);
    setEnabledEditButton(false);

    clearSelectTable();
    clearStyleButtonTable();
    closeAllEditForms();
    ui->searchLineEdit->clear();

    setWindowTitle("Gradify");
    ui->authorizationButton->setText("Вхід");
    ui->authorizationButton->setStyleSheet("");

    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf",
                             QSettings::IniFormat);
    settingsConfig.remove("userlogin");

    emit clearInputFields();
}

void MainWindow::handleLogin()
{
    qDebug() << QString("handleLogin()");
    // return;

    if (not isLogin) {
        loginWindow->show();
    } else {
        logoutMessageBox.exec();
        if (logoutMessageBox.clickedButton() == yesButton) {
            logoutUser();
        }
    }
}

void MainWindow::addRowToTable()
{
    qDebug() << QString("addRowToTable()");
    return;

    switch (currentSelectTable) {
    case TableType::Students:
        connect(this, &MainWindow::createNewRow, studentWindow, &StudentWindow::newRow);

        emit sendGroupsList(getGroupsNames());
        emit createNewRow();

        disconnect(this, &MainWindow::createNewRow, studentWindow, &StudentWindow::newRow);
        studentWindow->show();
        break;
    case TableType::Teachers:
        connect(this, &MainWindow::createNewRow, teacherWindow, &TeacherWindow::newRow);

        emit createNewRow();

        disconnect(this, &MainWindow::createNewRow, teacherWindow, &TeacherWindow::newRow);
        teacherWindow->show();
        break;
    case TableType::Grades:
        connect(this, &MainWindow::createNewRow, gradeWindow, &GradeWindow::newRow);
        connect(this,
                &MainWindow::sendStudentsList,
                gradeWindow,
                &GradeWindow::setDataStudentComboBox);
        connect(this,
                &MainWindow::sendSubjectsList,
                gradeWindow,
                &GradeWindow::setDataSubjectComboBox);

        emit sendSubjectsList(getSubjectsNames());
        emit sendStudentsList(getStudentsNames());
        emit sendTeachersList(getTeachersNames());
        emit createNewRow();

        disconnect(this,
                   &MainWindow::sendSubjectsList,
                   gradeWindow,
                   &GradeWindow::setDataSubjectComboBox);
        disconnect(this,
                   &MainWindow::sendStudentsList,
                   gradeWindow,
                   &GradeWindow::setDataStudentComboBox);
        disconnect(this, &MainWindow::createNewRow, gradeWindow, &GradeWindow::newRow);
        gradeWindow->show();
        break;
    case TableType::Groups:
        connect(this, &MainWindow::createNewRow, groupWindow, &GroupWindow::newRow);
        connect(this,
                &MainWindow::sendTeachersList,
                groupWindow,
                &GroupWindow::setDataCuratorComboBox);
        connect(this,
                &MainWindow::sendCurrentGroup,
                groupWindow,
                &GroupWindow::setDataHeadManComboBox);

        emit createNewRow();
        emit sendTeachersList(getTeachersNames());
        emit sendCurrentGroup("NULL");

        disconnect(this,
                   &MainWindow::sendTeachersList,
                   groupWindow,
                   &GroupWindow::setDataCuratorComboBox);
        disconnect(this,
                   &MainWindow::sendCurrentGroup,
                   groupWindow,
                   &GroupWindow::setDataHeadManComboBox);
        disconnect(this, &MainWindow::createNewRow, groupWindow, &GroupWindow::newRow);
        groupWindow->show();
        break;
    case TableType::Subjects:
        connect(this, &MainWindow::createNewRow, subjectWindow, &SubjectWindow::newRow);
        connect(this,
                &MainWindow::sendTeachersList,
                subjectWindow,
                &SubjectWindow::setTeacherComboBox);

        emit sendTeachersList(getTeachersNames());
        emit createNewRow();

        disconnect(this,
                   &MainWindow::sendTeachersList,
                   subjectWindow,
                   &SubjectWindow::setTeacherComboBox);
        disconnect(this, &MainWindow::createNewRow, subjectWindow, &SubjectWindow::newRow);
        subjectWindow->show();
        break;
    case TableType::None:
        QMessageBox::information(this, "Попередження", "Оберіть таблицю!");
        break;
    }
}

void MainWindow::deleteRowFromTable()
{
    qDebug() << QString("deleteRowFromTable()");
    return;

    ui->searchLineEdit->clearFocus();
    closeAllPopUpWindow();

    if (ui->tableWidget->model()->rowCount() > 0) {
        bool ok;
        QString selectedItem = QInputDialog::getItem(this,
                                                     tr("Видалення запису"),
                                                     tr("Оберіть запис для видалення:"),
                                                     getCurrentItemTable(),
                                                     ui->tableWidget->currentIndex().row(),
                                                     false,
                                                     &ok);

        if (ok) {
            model->removeRow(selectedItem.left(selectedItem.indexOf('.')).toInt() - 1);
            model->select();
        }
    } else {
        QMessageBox::critical(this, "", "Не знайдено записів для видалення!");
    }
}

void MainWindow::editRowInTable()
{
    qDebug() << QString("editRowInTable()");
    return;

    ui->searchLineEdit->clearFocus();
    closeAllPopUpWindow();

    if (ui->tableWidget->model()->rowCount() > 0) {
        bool ok;
        QString selectedItem = QInputDialog::getItem(this,
                                                     tr("Редагування запису"),
                                                     tr("Оберіть запис для редагування:"),
                                                     getCurrentItemTable(),
                                                     ui->tableWidget->currentIndex().row(),
                                                     false,
                                                     &ok);

        if (ok) {
            switch (currentSelectTable) {
            case TableType::Students:
                connect(this, &MainWindow::setDataEditForm, studentWindow, &StudentWindow::setData);

                emit sendGroupsList(getGroupsNames());
                emit setDataEditForm(selectedItem,
                                     getRowData(
                                         selectedItem.QString::left(selectedItem.indexOf('.'))
                                             .toInt()));

                disconnect(this,
                           &MainWindow::setDataEditForm,
                           studentWindow,
                           &StudentWindow::setData);
                studentWindow->show();
                break;
            case TableType::Teachers:
                connect(this, &MainWindow::setDataEditForm, teacherWindow, &TeacherWindow::setData);

                emit setDataEditForm(selectedItem,
                                     getRowData(
                                         selectedItem.left(selectedItem.indexOf('.')).toInt()));

                disconnect(this,
                           &MainWindow::setDataEditForm,
                           teacherWindow,
                           &TeacherWindow::setData);
                teacherWindow->show();
                break;
            case TableType::Grades:
                connect(this, &MainWindow::setDataEditForm, gradeWindow, &GradeWindow::setData);
                connect(this,
                        &MainWindow::sendStudentsList,
                        gradeWindow,
                        &GradeWindow::setDataStudentComboBox);
                connect(this,
                        &MainWindow::sendSubjectsList,
                        gradeWindow,
                        &GradeWindow::setDataSubjectComboBox);

                emit sendSubjectsList(getSubjectsNames());
                emit sendStudentsList(getStudentsNames());
                emit setDataEditForm(selectedItem,
                                     getRowData(
                                         selectedItem.left(selectedItem.indexOf('.')).toInt()));

                disconnect(this,
                           &MainWindow::sendSubjectsList,
                           gradeWindow,
                           &GradeWindow::setDataSubjectComboBox);
                disconnect(this,
                           &MainWindow::sendStudentsList,
                           gradeWindow,
                           &GradeWindow::setDataStudentComboBox);
                disconnect(this, &MainWindow::setDataEditForm, gradeWindow, &GradeWindow::setData);
                gradeWindow->show();
                break;
            case TableType::Groups:
                connect(this, &MainWindow::setDataEditForm, groupWindow, &GroupWindow::setData);
                connect(this,
                        &MainWindow::sendTeachersList,
                        groupWindow,
                        &GroupWindow::setDataCuratorComboBox);
                connect(this,
                        &MainWindow::sendCurrentGroup,
                        groupWindow,
                        &GroupWindow::setDataHeadManComboBox);

                emit sendTeachersList(getTeachersNames());
                emit sendCurrentGroup(selectedItem);
                emit setDataEditForm(selectedItem,
                                     getRowData(
                                         selectedItem.left(selectedItem.indexOf('.')).toInt()));

                disconnect(this, &MainWindow::setDataEditForm, groupWindow, &GroupWindow::setData);
                disconnect(this,
                           &MainWindow::sendTeachersList,
                           groupWindow,
                           &GroupWindow::setDataCuratorComboBox);
                disconnect(this,
                           &MainWindow::sendCurrentGroup,
                           groupWindow,
                           &GroupWindow::setDataHeadManComboBox);
                groupWindow->show();
                break;
            case TableType::Subjects:
                connect(this, &MainWindow::setDataEditForm, subjectWindow, &SubjectWindow::setData);
                connect(this,
                        &MainWindow::sendTeachersList,
                        subjectWindow,
                        &SubjectWindow::setTeacherComboBox);

                emit sendTeachersList(getTeachersNames());
                emit setDataEditForm(selectedItem,
                                     getRowData(
                                         selectedItem.left(selectedItem.indexOf('.')).toInt()));

                disconnect(this,
                           &MainWindow::sendTeachersList,
                           subjectWindow,
                           &SubjectWindow::setTeacherComboBox);
                disconnect(this,
                           &MainWindow::setDataEditForm,
                           subjectWindow,
                           &SubjectWindow::setData);
                subjectWindow->show();
                break;
            case TableType::None:
                break;
            }
        }
    } else {
        QMessageBox::critical(this, "", "Не знайдено записів для редагування!");
    }
}

void MainWindow::toggleFilterWindow()
{
    ui->searchLineEdit->clearFocus();

    if (filterWindow->isVisible()) {
        filterWindow->close();
    } else {
        queryWindow->close();

        filterWindow->move(ui->filterButton->x() * 2,
                           ui->filterButton->y() + ui->mainTableFrame->y() + 42);
        filterWindow->show();
    }
}

void MainWindow::toggleQueryWindow()
{
    ui->searchLineEdit->clearFocus();

    if (queryWindow->isVisible()) {
        queryWindow->close();
    } else {
        filterWindow->close();

        queryWindow->move(ui->queryButton->x() * 1.864,
                          ui->queryButton->y() + ui->mainTableFrame->y() + 42);
        queryWindow->show();
    }
}

void MainWindow::printDocumentToPDF(const QString path, const QString html)
{
    QTextDocument *document = new QTextDocument();
    document->setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setColorMode(QPrinter::Color);
    printer.setResolution(666);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(5, 5, 5, 5), QPageLayout::Millimeter);
    printer.setOutputFileName(path);

    //document->setPageSize(QSizeF(927, 1402.5));
    document->setPageSize(QSizeF(920, 1300));
    document->print(&printer);

    QDesktopServices::openUrl(QUrl("file://" + path, QUrl::TolerantMode));
}

void MainWindow::printDocumentToHTML(const QString path, const QString html)
{
    QFile outputFile(path);
    outputFile.open(QIODevice::WriteOnly);

    if (not outputFile.isOpen()) {
        QMessageBox::critical(this, "", "Не вдалося зберегти звіт");
        return;
    }

    QTextStream outStream(&outputFile);
    outStream.setGenerateByteOrderMark(true);
    outStream << html;
    outputFile.close();

    QDesktopServices::openUrl(QUrl("file://" + path, QUrl::TolerantMode));
}

QString MainWindow::getHeaderHTML()
{
    QString htmlHeader;

    htmlHeader = "<!DOCTYPE html>\n"
                 "<html>\n"
                 "<head>\n"
                 "<style>"
                 "table {\n width: 100%;\n padding-top: 120px;\n}\n"
                 "table, th, td {\n"
                 "  border:1px solid #e8e8e8;\n"
                 "  border-collapse: collapse;\n"
                 "  padding: 3px;\n"
                 "  font-size: 12px;\n"
                 "  font-family: -apple-system, BlinkMacSystemFont, sans-serif;\n"
                 "  background-color: white;\n"
                 "  padding-top: 6px;\n"
                 "  padding-bottom: 6px;\n}\n"
                 "th {\n    color: white;\n"
                 "  background-color: #0e4870;\n"
                 "  text-align: left;\n}\n"
                 "td.la {\n background-color: #f2f2f2;\n}\n"
                 "td.info {\n   border: 0px;\n  background-color: #e1e1e1;\n}\n"
                 "h1, h2, h3 ,h4{\n font-family: -apple-system, BlinkMacSystemFont, sans-serif\n}\n"
                 "#transpert {\ncolor: white;\n}\n"
                 "</style>\n"
                 "<title>Звіт</title>\n</head>\n";

    return htmlHeader;
}

void MainWindow::goSearch()
{
    if (not ui->searchLineEdit->text().isEmpty()) {
        QString searchString;

        for (int i = 0; i < ui->tableWidget->model()->columnCount(); ++i) {
            searchString += "`" + ui->tableWidget->model()->headerData(i, Qt::Horizontal).toString()
                            + "` LIKE" + "'%" + ui->searchLineEdit->text() + "%'";

            if (i not_eq ui->tableWidget->model()->columnCount() - 1) {
                searchString += " OR ";
            }
        }

        model->setFilter(searchString);
        //ui->tableWidget->setModel(model);
    } else {
        clearFilterForTable();
    }
}

void MainWindow::setDataToModel(QStringList dataList, bool isNewRow)
{
    if (isNewRow) {
        QString newRow = "INSERT INTO ";
        QSqlQueryModel *queryModel = new QSqlQueryModel(this);
        QTableWidget *tableWidget = new QTableWidget(this);

        switch (currentSelectTable) {
        case TableType::Students:
            newRow += "`Студенти`";
            queryModel->setQuery("SELECT MAX(`Код`) "
                                 "FROM Студенти");
            break;
        case TableType::Teachers:
            newRow += "`Викладачі` ";
            queryModel->setQuery("SELECT MAX(`Код`) "
                                 "FROM Викладачі");
            break;
        case TableType::Grades:
            newRow += "`Оцінки` ";
            queryModel->setQuery("SELECT MAX(`Код`) "
                                 "FROM Оцінки");
            break;
        case TableType::Groups:
            newRow += "`Групи` ";
            queryModel->setQuery("SELECT MAX(`Код`) "
                                 "FROM Групи");
            break;
        case TableType::Subjects:
            newRow += "`Предмети` ";
            queryModel->setQuery("SELECT MAX(`Код`) "
                                 "FROM Предмети");
            break;
        case TableType::None:
            break;
        }

        //tableWidget->setModel(queryModel);

        newRow += "(";

        for (int i = 0; i < model->columnCount(); ++i) {
            newRow += "`" + model->headerData(i, Qt::Horizontal).toString();

            if (i not_eq model->columnCount() - 1) {
                newRow += "`, ";
            } else {
                newRow += "`)";
            }
        }

        newRow += "\nVALUES ('"
                  + QString::number(tableWidget->model()->index(0, 0).data().toInt() + 1) + "',";

        for (int i = 1; i < model->columnCount(); ++i) {
            newRow += "'" + dataList[i];

            if (i not_eq model->columnCount() - 1) {
                newRow += "', ";
            } else {
                newRow += "')";
            }
        }

        QSqlQueryModel *sqlModel = new QSqlQueryModel();
        sqlModel->setQuery(newRow);
        model->select();
    } else {
        QString queryEdit = "UPDATE ";

        switch (currentSelectTable) {
        case TableType::Students:
            queryEdit += "`Студенти`";
            break;
        case TableType::Teachers:
            queryEdit += "`Викладачі` ";
            break;
        case TableType::Grades:
            queryEdit += "`Оцінки`";
            break;
        case TableType::Groups:
            queryEdit += "`Групи`";
            break;
        case TableType::Subjects:
            queryEdit += "`Предмети`";
            break;
        case None:
            break;
        }
        queryEdit += " \nSET";

        for (int i = 1; i < model->columnCount(); ++i) {
            queryEdit += "`" + model->headerData(i, Qt::Horizontal).toString() + "` = '"
                         + dataList[i];

            if (i not_eq model->columnCount() - 1) {
                queryEdit += "', \n";
            } else {
                queryEdit += "'";
            }
        }

        queryEdit += "\nWHERE `Код` = '" + dataList[0] + "'";

        QSqlQueryModel *sqlModel = new QSqlQueryModel();
        sqlModel->setQuery(queryEdit);
        model->select();
    }
}

void MainWindow::setQueryForTable(QString query)
{
    if (query == "NULL") {
        //ui->tableWidget->setModel(model);
        ui->tableWidget->resizeColumnsToContents();
        ui->tableWidget->sortByColumn(0, Qt::AscendingOrder);
    } else {
        queryModel->setQuery(query);
        //ui->tableWidget->setModel(queryModel);
    }
}

void MainWindow::clearFilterForTable()
{
    model->setFilter("");
    model->select();
    //ui->tableWidget->setModel(model);
}

QGraphicsDropShadowEffect *MainWindow::paintDropShadowEffect()
{
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(25);
    effect->setColor(QColor(15, 15, 15));
    effect->setOffset(QPointF(0, 1));
    return effect;
}

QMap<QString, QString> MainWindow::getColumnsNamesAndDatatypes(const QString &tableName)
{
    QMap<QString, QString> headerListMap;

    if (not tableName.isEmpty()) {
        QSqlQueryModel *queryModel = new QSqlQueryModel(this);
        QTableWidget *tableWidget = new QTableWidget(this);

        queryModel->setQuery("SELECT COLUMN_NAME, DATA_TYPE "
                             "FROM INFORMATION_SCHEMA.COLUMNS "
                             "WHERE table_schema = 'Gradify' "
                             "AND table_name = '"
                             + tableName
                             + "'"
                               "AND NOT column_name = 'Код'");

        //tableWidget->setModel(queryModel);

        for (int row = 0; row < queryModel->rowCount(); ++row) {
            headerListMap.insert(tableWidget->model()->index(row, 0).data().toString(),
                                 tableWidget->model()->index(row, 1).data().toString());
        }
    }

    return headerListMap;
}

QStringList MainWindow::getCurrentItemTable()
{
    QStringList str;

    switch (currentSelectTable) {
    case TableType::Students:
    case TableType::Teachers:
        for (int i = 0; i < ui->tableWidget->model()->rowCount(); ++i) {
            str << QString::number(i + 1) + ". "
                       + ui->tableWidget->model()->data(model->index(i, 1)).toString() + " "
                       + ui->tableWidget->model()->data(model->index(i, 2)).toString() + " "
                       + ui->tableWidget->model()->data(model->index(i, 3)).toString();
        }
        break;
    case TableType::Grades:
        for (int i = 0; i < ui->tableWidget->model()->rowCount(); ++i) {
            str << QString::number(i + 1) + ". "
                       + ui->tableWidget->model()->data(model->index(i, 2)).toString() + " - "
                       + ui->tableWidget->model()->data(model->index(i, 1)).toString() + ", "
                       + ui->tableWidget->model()->data(model->index(i, 4)).toString() + " ("
                       + ui->tableWidget->model()->data(model->index(i, 3)).toString() + ")";
        }
        break;
    case TableType::Groups:
    case TableType::Subjects:
        for (int i = 0; i < ui->tableWidget->model()->rowCount(); ++i) {
            str << QString::number(i + 1) + ". "
                       + ui->tableWidget->model()->data(model->index(i, 1)).toString();
        }
        break;
    case None:
        break;
    }

    return str;
}

QStringList MainWindow::getRowData(const int &row)
{
    QStringList listData;

    for (int j = 0; j < model->columnCount(); ++j) {
        listData << model->data(model->index(row - 1, j)).toString();
    }

    return listData;
}

QStringList MainWindow::getStudentsNames()
{
    QStringList studentList;
    QSqlQueryModel *virualQueryModel = new QSqlQueryModel(this);
    QTableView *virtualTable = new QTableView(this);

    virualQueryModel->setQuery("SELECT `Прізвище`, `Ім'я`, `По батькові`"
                               "FROM `Студенти`");

    virtualTable->setModel(virualQueryModel);

    for (int row = 0; row < virualQueryModel->rowCount(); ++row) {
        studentList.append(virtualTable->model()->index(row, 0).data().toString() + " "
                           + virtualTable->model()->index(row, 1).data().toString() + " "
                           + virtualTable->model()->index(row, 2).data().toString());
    }

    return studentList;
}

QStringList MainWindow::getTeachersNames()
{
    QStringList teacherList;
    QSqlQueryModel *virualQueryModel = new QSqlQueryModel(this);
    QTableView *virtualTable = new QTableView(this);

    virualQueryModel->setQuery("SELECT `Прізвище`, `Ім'я`, `По батькові`"
                               "FROM `Викладачі`");

    virtualTable->setModel(virualQueryModel);

    for (int row = 0; row < virualQueryModel->rowCount(); ++row) {
        teacherList.append(virtualTable->model()->index(row, 0).data().toString() + " "
                           + virtualTable->model()->index(row, 1).data().toString() + " "
                           + virtualTable->model()->index(row, 2).data().toString());
    }

    return teacherList;
}

QStringList MainWindow::getSubjectsNames()
{
    QStringList subjectList;
    QSqlQueryModel *virualQueryModel = new QSqlQueryModel(this);
    QTableView *virtualTable = new QTableView(this);

    virualQueryModel->setQuery("SELECT `Назва`"
                               "FROM `Предмети`");

    virtualTable->setModel(virualQueryModel);

    for (int row = 0; row < virualQueryModel->rowCount(); ++row) {
        subjectList.append(virtualTable->model()->index(row, 0).data().toString());
    }

    return subjectList;
}

QStringList MainWindow::getSubjectsTypes()
{
    QStringList categoryList;
    QSqlQueryModel *virualQueryModel = new QSqlQueryModel(this);
    QTableView *virtualTable = new QTableView(this);

    virualQueryModel->setQuery("SELECT `Тип`"
                               "FROM `Предмети`"
                               "GROUP BY `Тип`");

    virtualTable->setModel(virualQueryModel);

    for (int row = 0; row < virualQueryModel->rowCount(); ++row) {
        categoryList.append(virtualTable->model()->index(row, 0).data().toString());
    }

    return categoryList;
}

QStringList MainWindow::getCategoryTeachers()
{
    QStringList categoryList;
    QSqlQueryModel *virualQueryModel = new QSqlQueryModel(this);
    QTableView *virtualTable = new QTableView(this);

    virualQueryModel->setQuery("SELECT `Категорія`"
                               "FROM `Викладачі`"
                               "GROUP BY `Категорія`");

    virtualTable->setModel(virualQueryModel);

    for (int row = 0; row < virualQueryModel->rowCount(); ++row) {
        categoryList.append(virtualTable->model()->index(row, 0).data().toString());
    }

    return categoryList;
}

QStringList MainWindow::getGroupsNames()
{
    QStringList groupList;
    QSqlQueryModel *virualQueryModel = new QSqlQueryModel(this);
    QTableView *virtualTable = new QTableView(this);

    virualQueryModel->setQuery("SELECT `Назва`"
                               "FROM `Групи`");

    virtualTable->setModel(virualQueryModel);

    for (int row = 0; row < virualQueryModel->rowCount(); ++row) {
        groupList.append(virtualTable->model()->index(row, 0).data().toString());
    }

    return groupList;
}

QStringList MainWindow::getGroupsSpecial()
{
    QStringList groupSpecialList;
    QSqlQueryModel *virualQueryModel = new QSqlQueryModel(this);
    QTableView *virtualTable = new QTableView(this);

    virualQueryModel->setQuery("SELECT `Спеціальність`"
                               "FROM `Групи`"
                               "GROUP BY `Спеціальність`");

    virtualTable->setModel(virualQueryModel);

    for (int row = 0; row < virualQueryModel->rowCount(); ++row) {
        groupSpecialList.append(virtualTable->model()->index(row, 0).data().toString());
    }

    return groupSpecialList;
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

//=========================================================
//
//                 КОД ДЛЯ ЗВИТОВ ПО ТАБЛИЦАМ!!!
//
//=========================================================

void MainWindow::fillHTMLTable(QString &textHTML, QTableView *tableView)
{
    for (int i = 0; i < tableView->model()->columnCount(); ++i) {
        textHTML += "   <th>" + tableView->model()->headerData(i, Qt::Horizontal).toString()
                    + "</th>\n";
    }

    textHTML += "</tr>\n";

    for (int i = 0; i < tableView->model()->rowCount(); ++i) {
        textHTML += "<tr>\n";

        for (int j = 0; j < tableView->model()->columnCount(); ++j) {
            if (i % 2 not_eq 0) {
                textHTML += "   <td class='la'>" + tableView->model()->index(i, j).data().toString()
                            + "</td>\n";
            } else {
                textHTML += "   <td>" + tableView->model()->index(i, j).data().toString()
                            + "</td>\n";
            }
        }
        textHTML += "</tr>\n";
    }
    textHTML += "</tbody></table>";
}

void MainWindow::generateCurrentTableReport()
{
    qDebug() << QString("generateCurrentTableReport()");
    return;

    if (model->rowCount() > 0) {
        QString typeFile;
        QString pathToSave
            = QFileDialog::getSaveFileName(nullptr,
                                           tr("Збереження звіту"),
                                           "/Users/" + qgetenv("USER") + "/Desktop",
                                           "PDF формат (*.pdf);;HTML формат (*.html)",
                                           &typeFile);
        if (not pathToSave.isEmpty()) {
            QString textHTML = getHeaderHTML();
            textHTML += "<h2 align='center'>Звіт Gradify</h2>\n<table ALIGN = 'center'>\n<p2 "
                        "id='transpert'>f</p2><tr>";

            fillHTMLTable(textHTML, ui->tableWidget);

            if (typeFile == "HTML формат (*.html)") {
                printDocumentToHTML(pathToSave, textHTML);
            } else if (typeFile == "PDF формат (*.pdf)") {
                printDocumentToPDF(pathToSave, textHTML);
            }
        }
    } else {
        QMessageBox::information(this, "", "У таблиці не знайдено записів!");
    }
}

void MainWindow::generateStudentsGroupReport()
{
    qDebug() << QString("generateStudentsGroupReport()");
    return;

    bool ok;

    QString selectedGroup = QInputDialog::getItem(this,
                                                  tr("Звіт за студентами групи"),
                                                  tr("Оберіть групу:"),
                                                  getGroupsNames(),
                                                  0,
                                                  false,
                                                  &ok);
    if (ok) {
        QString typeFile;
        QString pathToSave
            = QFileDialog::getSaveFileName(nullptr,
                                           tr("Збереження звіту"),
                                           "/Users/" + qgetenv("USER") + "/Desktop",
                                           "PDF формат (*.pdf);;HTML формат (*.html)",
                                           &typeFile);
        if (not pathToSave.isEmpty()) {
            QSqlQueryModel *queryModel = new QSqlQueryModel(this);
            QTableView *tableView = new QTableView(this);

            queryModel->setQuery("SELECT * "
                                 "FROM `Студенти`"
                                 "WHERE `Студенти`.`Група` = '"
                                 + selectedGroup + "'");
            tableView->setModel(queryModel);

            QString textHTML = getHeaderHTML();
            textHTML += "<h2 align='center'>Звіт за студентами групи «" + selectedGroup
                        + "»</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";

            fillHTMLTable(textHTML, tableView);

            queryModel->setQuery("SELECT `Куратор`,`Староста`"
                                 "FROM `Групи`"
                                 "WHERE `Групи`.`Назва` = '"
                                 + selectedGroup + "'");
            tableView->setModel(queryModel);

            textHTML += "<tr>\n <td class='info'>Куратор</td>";

            QString bufStr = tableView->model()->index(0, 0).data().toString();
            textHTML += "\n <td>" + bufStr.left(bufStr.indexOf(' ')) + "</td>";
            bufStr.remove(0, bufStr.indexOf(' ') + 1);
            textHTML += "\n <td>" + bufStr.left(bufStr.lastIndexOf(' ')) + "</td>";
            bufStr.remove(0, bufStr.lastIndexOf(' ') + 1);
            textHTML += "\n <td>" + bufStr + "</td>\n</tr>\n";

            bufStr = tableView->model()->index(0, 1).data().toString();
            textHTML += "\n<tr>\n   <td class='info'>Староста</td>";
            textHTML += "\n <td>" + bufStr.left(bufStr.indexOf(' ')) + "</td>";
            bufStr.remove(0, bufStr.indexOf(' ') + 1);
            textHTML += "\n <td>" + bufStr.left(bufStr.lastIndexOf(' ')) + "</td>";
            bufStr.remove(0, bufStr.lastIndexOf(' ') + 1);
            textHTML += "\n <td>" + bufStr + "</td>\n</tr>\n</table>\n";

            if (typeFile == "HTML формат (*.html)") {
                printDocumentToHTML(pathToSave, textHTML);
            } else if (typeFile == "PDF формат (*.pdf)") {
                printDocumentToPDF(pathToSave, textHTML);
            }
        }
    }
}

void MainWindow::generateTeachersReport()
{
    qDebug() << QString("generateTeachersReport()");
    return;

    // bool flag for get events status
    bool ok;

    // select teachers category
    QString selectedCategory = QInputDialog::getItem(this,
                                                     tr("Звіт по викладачам"),
                                                     tr("Оберіть категорію викладача:"),
                                                     getCategoryTeachers(),
                                                     0,
                                                     false,
                                                     &ok);

    if (ok) {
        // create teachers list
        QStringList teachersList;
        QSqlQueryModel *virtualQueryModel = new QSqlQueryModel(this);
        QTableView *virtualTable = new QTableView(this);

        virtualQueryModel->setQuery("SELECT `Прізвище`"
                                    "FROM `Викладачі` "
                                    "WHERE `Викладачі`.`Категорія` = '"
                                    + selectedCategory + "';");

        virtualTable->setModel(virtualQueryModel);

        if (virtualQueryModel->rowCount() > 0) {
            teachersList.append("Всі викладачі");
            for (int row = 0; row < virtualQueryModel->rowCount(); ++row) {
                teachersList.append(virtualTable->model()->index(row, 0).data().toString());
            }
        } else {
            QMessageBox::information(this, "Помилка", "Викладачів даної категорії немає!");
            return;
        }

        // string choice teacher
        QString optionChoice = QInputDialog::getItem(this,
                                                     tr("Звіт по викладачам"),
                                                     tr("Оберіть викладача:"),
                                                     teachersList,
                                                     0,
                                                     false,
                                                     &ok);

        if (ok) {
            // get path to report save
            QString typeFile;
            QString pathToSave
                = QFileDialog::getSaveFileName(nullptr,
                                               tr("Збереження звіту"),
                                               "/Users/" + qgetenv("USER") + "/Desktop",
                                               "PDF формат (*.pdf);;HTML формат (*.html)",
                                               &typeFile);
            if (not pathToSave.isEmpty()) {
                QSqlQueryModel *virtualQueryModel = new QSqlQueryModel(this);
                QTableView *virtualTableView = new QTableView(this);

                QString textHTML = getHeaderHTML();

                if (optionChoice == "Всі викладачі") {
                    virtualQueryModel->setQuery("SELECT * "
                                                "FROM `Викладачі`"
                                                "WHERE `Викладачі`.`Категорія` = '"
                                                + selectedCategory + "';");
                    textHTML += "<h2 align='center'>Викладачі з категорією «" + selectedCategory
                                + "»</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";

                } else {
                    virtualQueryModel->setQuery("SELECT * "
                                                "FROM `Викладачі` "
                                                "WHERE `Викладачі`.`Категорія` = '"
                                                + selectedCategory
                                                + "' "
                                                  "AND `Викладачі`.`Прізвище` = '"
                                                + optionChoice + "';");
                    textHTML += "<h2 align='center'>Викладач з категорією «" + selectedCategory
                                + "» " + optionChoice
                                + "</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";
                }

                virtualTableView->setModel(virtualQueryModel);

                fillHTMLTable(textHTML, virtualTableView);

                // statistics chart

                if (optionChoice != "Всі викладачі") {
                    virtualQueryModel->setQuery(
                        "SELECT `Предмети`.`Назва`, COUNT(`Оцінки`.`Оцінка`)"
                        "FROM `Оцінки`, `Предмети`, `Викладачі`"
                        "WHERE SUBSTRING_INDEX(`Предмети`.`Викладач`, ' ', 1) = '"
                        + optionChoice
                        + "'"
                          "AND `Предмети`.`Назва` = `Оцінки`.`Предмет`"
                          "GROUP BY(`Предмети`.`Назва`);");

                    if (virtualQueryModel->rowCount() > 0) {
                        // fill pie series
                        virtualTable->setModel(virtualQueryModel);

                        QPieSeries *pieSeries = new QPieSeries();

                        for (int row = 0; row < virtualQueryModel->rowCount(); ++row) {
                            pieSeries->append(virtualTable->model()->index(row, 0).data().toString(),
                                              virtualTable->model()->index(row, 1).data().toInt()
                                                  / 21);
                        }

                        pieSeries->setLabelsVisible(true);

                        // create chart
                        QChart *chart = new QChart();
                        chart->addSeries(pieSeries);
                        chart->setTitle("Статистика оцінок по предметам");
                        chart->legend()->setVisible(true);

                        QChartView *chartView = new QChartView(chart);
                        chartView->setRenderHint(QPainter::Antialiasing);
                        chartView->setBackgroundBrush(Qt::white);

                        chartView->grab().save(pathToSave.left(pathToSave.lastIndexOf('.')) + ".png",
                                               "PNG");

                        textHTML += "<br><br><br><center><img src="
                                    + pathToSave.left(pathToSave.lastIndexOf('.')) + ".png"
                                    + " width=\"640\" height=\"480\"></center>";
                    }
                }

                if (typeFile == "HTML формат (*.html)") {
                    printDocumentToHTML(pathToSave, textHTML);
                } else if (typeFile == "PDF формат (*.pdf)") {
                    printDocumentToPDF(pathToSave, textHTML);
                }
            }
        }
    }
}

void MainWindow::generateGradesReport()
{
    qDebug() << QString("generateGradesReport()");
    return;

    bool ok;

    QString selectedStudent = QInputDialog::getItem(this,
                                                    tr("Звіт по оцінкам"),
                                                    tr("Оберіть отримувача оцінок:"),
                                                    getStudentsNames(),
                                                    0,
                                                    false,
                                                    &ok);
    if (ok) {
        QString typeFile;
        QString pathToSave
            = QFileDialog::getSaveFileName(nullptr,
                                           tr("Збереження звіту"),
                                           "/Users/" + qgetenv("USER") + "/Desktop",
                                           "PDF формат (*.pdf);;HTML формат (*.html)",
                                           &typeFile);
        if (not pathToSave.isEmpty()) {
            QSqlQueryModel *queryModel = new QSqlQueryModel(this);
            QTableView *tableView = new QTableView(this);

            queryModel->setQuery("SELECT * "
                                 "FROM `Оцінки`"
                                 "WHERE `Оцінки`.`Отримувач` = '"
                                 + selectedStudent + "'");
            tableView->setModel(queryModel);

            QString textHTML = getHeaderHTML();
            textHTML += "<h2 align='center'>Звіт за оцінками студента «" + selectedStudent
                        + "»</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";

            fillHTMLTable(textHTML, tableView);

            if (typeFile == "HTML формат (*.html)") {
                printDocumentToHTML(pathToSave, textHTML);
            } else if (typeFile == "PDF формат (*.pdf)") {
                printDocumentToPDF(pathToSave, textHTML);
            }
        }
    }
}

void MainWindow::generateGroupsReport()
{
    qDebug() << QString("generateGroupsReport()");
    return;

    bool ok;

    QString selectedTypeSubject = QInputDialog::getItem(this,
                                                        tr("Звіт за спеціальностями груп"),
                                                        tr("Оберіть спеціальність групи:"),
                                                        getGroupsSpecial(),
                                                        0,
                                                        false,
                                                        &ok);
    if (ok) {
        QString typeFile;
        QString pathToSave
            = QFileDialog::getSaveFileName(nullptr,
                                           tr("Збереження звіту"),
                                           "/Users/" + qgetenv("USER") + "/Desktop",
                                           "PDF формат (*.pdf);;HTML формат (*.html)",
                                           &typeFile);
        if (not pathToSave.isEmpty()) {
            QSqlQueryModel *queryModel = new QSqlQueryModel(this);
            QTableView *tableView = new QTableView(this);

            queryModel->setQuery("SELECT * "
                                 "FROM `Групи`"
                                 "WHERE `Групи`.`Спеціальність` = '"
                                 + selectedTypeSubject + "'");
            tableView->setModel(queryModel);

            QString textHTML = getHeaderHTML();
            textHTML += "<h2 align='center'>Звіт за спеціальністю «" + selectedTypeSubject
                        + "»</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";

            fillHTMLTable(textHTML, tableView);

            if (typeFile == "HTML формат (*.html)") {
                printDocumentToHTML(pathToSave, textHTML);
            } else if (typeFile == "PDF формат (*.pdf)") {
                printDocumentToPDF(pathToSave, textHTML);
            }
        }
    }
}

void MainWindow::generateSubjectsReport()
{
    qDebug() << QString("generateSubjectsReport()");
    return;

    bool ok;

    QString selectedTypeSubject = QInputDialog::getItem(this,
                                                        tr("Звіт за предметами"),
                                                        tr("Оберіть тип предмету:"),
                                                        getSubjectsTypes(),
                                                        0,
                                                        false,
                                                        &ok);
    if (ok) {
        QString typeFile;
        QString pathToSave
            = QFileDialog::getSaveFileName(nullptr,
                                           tr("Збереження звіту"),
                                           "/Users/" + qgetenv("USER") + "/Desktop",
                                           "PDF формат (*.pdf);;HTML формат (*.html)",
                                           &typeFile);
        if (not pathToSave.isEmpty()) {
            QSqlQueryModel *queryModel = new QSqlQueryModel(this);
            QTableView *tableView = new QTableView(this);

            queryModel->setQuery("SELECT * "
                                 "FROM `Предмети`"
                                 "WHERE `Предмети`.`Тип` = '"
                                 + selectedTypeSubject + "'");
            tableView->setModel(queryModel);

            QString textHTML = getHeaderHTML();
            textHTML += "<h2 align='center'>Звіт за типом предмета «" + selectedTypeSubject
                        + "»</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";

            fillHTMLTable(textHTML, tableView);

            if (typeFile == "HTML формат (*.html)") {
                printDocumentToHTML(pathToSave, textHTML);
            } else if (typeFile == "PDF формат (*.pdf)") {
                printDocumentToPDF(pathToSave, textHTML);
            }
        }
    }
}

void MainWindow::setBlackUI()
{
    QFile file(":/styles/black/MainWindow/MainWindow.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    styleF.setFileName(":/styles/black/MainWindow/SelectButtonTableStyle.qss");
    styleF.open(QFile::ReadOnly);
    selectButtonTableStyle = styleF.readAll();
    styleF.close();

    file.setFileName(":/styles/black/MainWindow/OutLoginButton.qss");
    file.open(QFile::ReadOnly);
    selectButtonAuthStyle = QLatin1String(file.readAll());
    file.close();

    if (isLogin) {
        ui->authorizationButton->setStyleSheet(selectButtonAuthStyle);
    }

    ui->searchLineEdit->setIconSearchButton(QIcon(":/img/blackMenuIcon/search.png"), QSize(12, 12));
    ui->searchLineEdit->setIconClearButton(QIcon(":/img/whiteMenuIcon/clearLoginIco.png"),
                                           QSize(12, 12));

    setCurrentIconAction();

    switch (currentSelectTable) {
    case TableType::Students:
        ui->studentsTableButton->setStyleSheet(selectButtonTableStyle);
        ui->studentsTableButton->setIcon(QIcon(":/img/blackMenuIcon/studentsIco.png"));
        break;
    case TableType::Teachers:
        ui->teachersTableButton->setStyleSheet(selectButtonTableStyle);
        ui->teachersTableButton->setIcon(QIcon(":/img/blackMenuIcon/teachersIco.png"));
        break;
    case TableType::Grades:
        ui->gradesTableButton->setStyleSheet(selectButtonTableStyle);
        ui->gradesTableButton->setIcon(QIcon(":/img/blackMenuIcon/gradesIco.png"));
        break;
    case TableType::Groups:
        ui->groupsTableButton->setStyleSheet(selectButtonTableStyle);
        ui->groupsTableButton->setIcon(QIcon(":/img/blackMenuIcon/groupsIco.png"));
        break;
    case TableType::Subjects:
        ui->subjectsTableButton->setStyleSheet(selectButtonTableStyle);
        ui->subjectsTableButton->setIcon(QIcon(":/img/blackMenuIcon/subjectsIco.png"));
        break;
    case None:
        break;
    }
}

//====================
//
// set white style
//
//====================

void MainWindow::setWhiteUI()
{
    QFile file(":/styles/white/MainWindow/MainWindow.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    file.setFileName(":/styles/white/MainWindow/SelectButtonTableStyle.qss");
    file.open(QFile::ReadOnly);
    selectButtonTableStyle = QLatin1String(file.readAll());
    file.close();

    file.setFileName(":/styles/white/MainWindow/OutLoginButton.qss");
    file.open(QFile::ReadOnly);
    selectButtonAuthStyle = QLatin1String(file.readAll());
    file.close();

    if (isLogin) {
        ui->authorizationButton->setStyleSheet(selectButtonAuthStyle);
    }

    ui->searchLineEdit->setIconSearchButton(QIcon(":/img/blackMenuIcon/search.png"), QSize(12, 12));
    ui->searchLineEdit->setIconClearButton(QIcon(":/img/blackMenuIcon/clearLoginIco.png"),
                                           QSize(12, 12));

    setCurrentIconAction();

    switch (currentSelectTable) {
    case TableType::Students:
        ui->studentsTableButton->setStyleSheet(selectButtonTableStyle);
        ui->studentsTableButton->setIcon(QIcon(":/img/whiteMenuIcon/studentsIco.png"));
        break;
    case TableType::Teachers:
        ui->teachersTableButton->setStyleSheet(selectButtonTableStyle);
        ui->teachersTableButton->setIcon(QIcon(":/img/whiteMenuIcon/teachersIco.png"));
        break;
    case TableType::Grades:
        ui->gradesTableButton->setStyleSheet(selectButtonTableStyle);
        ui->gradesTableButton->setIcon(QIcon(":/img/whiteMenuIcon/gradesIco.png"));
        break;
    case TableType::Groups:
        ui->groupsTableButton->setStyleSheet(selectButtonTableStyle);
        ui->groupsTableButton->setIcon(QIcon(":/img/whiteMenuIcon/groupsIco.png"));
        break;
    case TableType::Subjects:
        ui->subjectsTableButton->setStyleSheet(selectButtonTableStyle);
        ui->subjectsTableButton->setIcon(QIcon(":/img/whiteMenuIcon/subjectsIco.png"));
        break;
    case TableType::None:
        break;
    }
}

void MainWindow::setSystemUI()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(),
                                      1 - baseColor.greenF(),
                                      1 - baseColor.blueF());

    if (newBase.name() == "#000000") {
        theme = "white";
        setWhiteUI();
    } else {
        theme = "black";
        setBlackUI();
    }
}

void MainWindow::setCurrentIconAction()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(),
                                      1 - baseColor.greenF(),
                                      1 - baseColor.blueF());

    QString iconColor = newBase.name() == "#000000" ? "black" : "white";

    ui->openStudTabAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/studentsIco.png"));
    ui->openTeachTabAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/teachersIco.png"));
    ui->openGradesTabAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/gradesIco.png"));
    ui->openGroupTabAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/groupsIco.png"));
    ui->openSubjTabAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/subjectsIco.png"));

    ui->addRowAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/newRecord.png"));
    ui->deleteRowAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/deleteRecord.png"));
    ui->editRowAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/editRecord.png"));

    ui->currentTableReportAction->setIcon(
        QIcon(":/img/" + iconColor + "ActionsIcon/reportCurrentTable.png"));
    ui->studentsReportAction->setIcon(
        QIcon(":/img/" + iconColor + "ActionsIcon/reportStudents.png"));
    ui->teachersReportAction->setIcon(
        QIcon(":/img/" + iconColor + "ActionsIcon/reportTeachers.png"));
    ui->gradesReportAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/reportGrades.png"));
    ui->groupsReportAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/reportGroups.png"));
    ui->subjectsReportAction->setIcon(
        QIcon(":/img/" + iconColor + "ActionsIcon/reportSubjects.png"));
}

//=========================================================
//
//                  Realisation menuBar code
//
//=========================================================

void MainWindow::openManual()
{
    QDesktopServices::openUrl(
        QUrl("https://gradify.online/Посібник_користувача.pdf", QUrl::TolerantMode));
}

void MainWindow::openAboutWindow()
{
    aboutAppWindow->show();
}

void MainWindow::openStatisticsWindow()
{
    closeAllStatisticsForm();

    switch (currentSelectTable) {
    case TableType::Students:
        studentStatisticsWindow->show();
        break;
    case TableType::Teachers:
        teacherStatisticsWindow->fillChart();
        teacherStatisticsWindow->show();
        break;
    case TableType::Grades:
        gradeStatisticsWindow->show();
        break;
    case TableType::Groups:
        groupStatisticsWindow->show();
        emit updateStatisticsComboBoxSignal();
        break;
    case TableType::Subjects:
        subjectStatisticsWindow->fillChart();
        subjectStatisticsWindow->show();
        break;
    case None:
        break;
    }

    emit updateStatisticsSignal();
}

QString MainWindow::modelDataToString(QAbstractItemModel *model)
{
    QString textData;

    for (int col = 0; col < model->columnCount(); ++col) {
        textData += model->headerData(col, Qt::Horizontal).toString() + ", ";
    }
    textData += "\n";

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            textData += model->data(model->index(row, col)).toString();
            textData += ", ";
        }
        textData += "\n";
    }

    return textData;
}

void MainWindow::exportDataToCSV()
{
    qDebug() << QString("exportDataToCSV");
    return;

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Помилка", "Оберіть таблицю для експорту");
        return;
    }

    QString pathToSave = QFileDialog::getSaveFileName(nullptr,
                                                      tr("Експорт файлу:"),
                                                      "/Users/" + qgetenv("USER") + "/Desktop",
                                                      "CSV files (*.csv);;All files (*.*)",
                                                      new QString("CSV file (*.csv)"));

    QFile csvFile(pathToSave + ".csv");
    if (csvFile.open(QIODevice::WriteOnly)) {
        QTextStream out(&csvFile);
        out << modelDataToString(model);
        csvFile.close();
    }
}

void MainWindow::exportDataToTXT()
{
    qDebug() << QString("exportDataToTXT");
    return;

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Помилка", "Оберіть таблицю для експорту");
        return;
    }

    QString pathToSave = QFileDialog::getSaveFileName(nullptr,
                                                      tr("Експорт файлу:"),
                                                      "/Users/" + qgetenv("USER") + "/Desktop",
                                                      "Text file (*.txt);;All files (*.*)",
                                                      new QString("Text file (*.txt)"));

    QFile txtFile(pathToSave);
    if (txtFile.open(QIODevice::WriteOnly)) {
        QTextStream out(&txtFile);
        out << modelDataToString(model);
        txtFile.close();
    }
}

void MainWindow::on_actionEnglish_Translate_triggered()
{
    /*
    qDebug() << "Switching to English (United States)...";
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    qDebug() << "Current locale:" << QLocale::system().name();

    translator.load(":/translations/Gradify_en_US.qm");
    if (qApp->installTranslator(&translator)) {
        qDebug() << "Translation installed successfully.";
    } else {
        qDebug() << "Failed to install translation.";
    }
    */
}

void MainWindow::on_actionUkrainian_Translate_triggered()
{
    /*
    qDebug() << "Switching to Ukrainian (Ukraine)...";
    QLocale::setDefault(QLocale(QLocale::Ukrainian, QLocale::Ukraine));
    qDebug() << "Current locale:" << QLocale::system().name();

    translator.load(":/translations/Gradify_ua_UA.qm");
    if (qApp->installTranslator(&translator)) {
        qDebug() << "Translation installed successfully.";
    } else {
        qDebug() << "Failed to install translation.";
    }
    */
}
