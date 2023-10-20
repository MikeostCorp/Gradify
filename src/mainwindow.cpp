#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QInputDialog>
#include <QFileDialog>
#include <QStandardPaths>
#include <QGraphicsDropShadowEffect>
#include <QKeyEvent>
#include <QTextDocument>
#include <QPrinter>
#include <QPageSize>
#include <QDesktopServices>

#include <customWidgets/qsearchbar.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainWindowInit();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mainWindowInit()
{
    // example of translate
    // idk why you paste 2 spaces bro
    ui->settingsButton->setText(tr("  Налаштування"));

    setWindowTitle("Gradify");

    // init obj's of windows classes
    settingWindow = new appSetting();
    authorizationWindow = new authorizationForm();
    filterWindow = new filterForm(this);
    queryWindow = new queryForm(this);
    aboutAppWindow = new aboutApp();

    gradeForm = new gradeWindow();
    groupForm = new groupWindow();
    studentForm = new studentWindow();
    subjectForm = new subjectWindow();
    teacherForm = new teacherWindow();

    gradeStat = new gradeStatistics();
    groupStat = new groupStatistics();
    studentStat = new studentStatistics();
    subjectStat = new subjectStatistics();
    teacherStat = new teacherStatistics();

    // pop-up windows graphics settings
    filterWindow->setGraphicsEffect(paintDropShadowEffect());
    queryWindow->setGraphicsEffect(paintDropShadowEffect());

    // default inactive state on main window
    currentSelectTable = -1;
    setEnabledButtons(false);
    setEnabledActions(false);
    setEnabledEditButton(false);

    // tableview settings
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);

    ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);

    // theme change after config init
    connect(this, &MainWindow::setThemeSettingsUI, settingWindow, &appSetting::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, authorizationWindow, &authorizationForm::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, aboutAppWindow, &aboutApp::setTheme);

    connect(this, &MainWindow::setThemeSettingsUI, gradeForm, &gradeWindow::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, groupForm, &groupWindow::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, studentForm, &studentWindow::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, subjectForm, &subjectWindow::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, teacherForm, &teacherWindow::setTheme);

    connect(this, &MainWindow::setThemeSettingsUI, gradeStat, &gradeStatistics::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, groupStat, &groupStatistics::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, studentStat, &studentStatistics::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, subjectStat, &subjectStatistics::setTheme);
    connect(this, &MainWindow::setThemeSettingsUI, teacherStat, &teacherStatistics::setTheme);

    // update statistics
    connect(this, &MainWindow::updateStatisticsSignal, studentStat, &studentStatistics::updateGroupComboBox);
    connect(this, &MainWindow::updateStatisticsComboBoxSignal, groupStat, &groupStatistics::setGroupComboBox);
    // config initialization
    configInit();

    // login/logout
    connect(authorizationWindow, &authorizationForm::signalLogin, this, &MainWindow::authorization);
    connect(settingWindow, &appSetting::logoutSignal, this, &MainWindow::userLogout);

    // theme change in settings window
    connect(settingWindow, &appSetting::changeThemeApp, this, &MainWindow::setTheme);
    connect(settingWindow, &appSetting::changeThemeApp, authorizationWindow, &authorizationForm::setTheme);
    connect(settingWindow, &appSetting::changeThemeApp, aboutAppWindow, &aboutApp::setTheme);

    connect(settingWindow, &appSetting::changeThemeApp, gradeForm, &gradeWindow::setTheme);
    connect(settingWindow, &appSetting::changeThemeApp, groupForm, &groupWindow::setTheme);
    connect(settingWindow, &appSetting::changeThemeApp, studentForm, &studentWindow::setTheme);
    connect(settingWindow, &appSetting::changeThemeApp, subjectForm, &subjectWindow::setTheme);
    connect(settingWindow, &appSetting::changeThemeApp, teacherForm, &teacherWindow::setTheme);

    connect(settingWindow, &appSetting::changeThemeApp, gradeStat, &gradeStatistics::setTheme);
    connect(settingWindow, &appSetting::changeThemeApp, groupStat, &groupStatistics::setTheme);
    connect(settingWindow, &appSetting::changeThemeApp, studentStat, &studentStatistics::setTheme);
    connect(settingWindow, &appSetting::changeThemeApp, subjectStat, &subjectStatistics::setTheme);
    connect(settingWindow, &appSetting::changeThemeApp, teacherStat, &teacherStatistics::setTheme);

    // filters and requests
    connect(filterWindow, &filterForm::sendFilter, this, &MainWindow::setFilterForTable);
    connect(filterWindow, &filterForm::clearFilter, this, &MainWindow::clearFilterForTable);
    connect(this, &MainWindow::setTableForFilter, filterWindow, &filterForm::setListTable);
    connect(queryWindow, &queryForm::sendQuery, this, &MainWindow::setQueryForTable);
    connect(queryWindow, &queryForm::sendFilter, this, &MainWindow::setFilterForTable);
    connect(queryWindow, &queryForm::clearFilter, this, &MainWindow::clearFilterForTable);
    connect(this, &MainWindow::changedGradeTable, queryWindow, &queryForm::selectedGradeTable);

    // clear searchbar & filter
    connect(ui->searchLineEdit, &QSearchBar::clickedClearButton, this, &MainWindow::clearFilterForTable);

    // close pop-up windows on click tableView (need fix empty space)
    connect(ui->tableView->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::closeAllPopUpWindow);
    connect(ui->tableView->verticalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::closeAllPopUpWindow);
    connect(ui->tableView, &QAbstractItemView::clicked, this, &MainWindow::closeAllPopUpWindow);
    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::closeAllPopUpWindow);

    // close pop-up windows on click any buttons
    for (QPushButton* button : findChildren<QPushButton*>())
    {
        // Добавлять в условие название кнопок форм привязаных к главному окну
        if (button->objectName() not_eq "filterButton" and button->objectName() not_eq "queryButton"
            and button->objectName() not_eq "filterPushButton" and button->objectName() not_eq "succesStudentPushButton"
            and button->objectName() not_eq "avgScorePushButton" and button->objectName() not_eq "clearFilterPushButton"
            and button->objectName() not_eq "mySQLPushButton" and button->objectName() not_eq "searchGradeStudentButton")
        { // ето тебе нада
            connect(button, &QPushButton::clicked, this, &MainWindow::closeAllPopUpWindow);
        }
        if (button->objectName() not_eq "editRowButton"
            and button->objectName() not_eq "settingsButton"
            and button->objectName() not_eq "addRowButton")
        {
            connect(button, &QPushButton::clicked, this, &MainWindow::closeAllEditForm);
        }
    }

    // close popup windows on click menubar
    connect(ui->menuBar, &QMenuBar::triggered, this, &MainWindow::closeAllPopUpWindow);
    connect(ui->searchLineEdit, &QSearchBar::haveFocus, this, &MainWindow::closeAllPopUpWindow);
    connect(ui->searchLineEdit, &QSearchBar::buttonSearchClick, this, &MainWindow::goSearch);
    connect(ui->searchLineEdit, &QLineEdit::returnPressed, this, &MainWindow::goSearch);

    // send list to edit form
    connect(this, &MainWindow::sendGroupsList, studentForm, &studentWindow::setComboBox);

    // get data from edit form
    connect(gradeForm, &gradeWindow::sendData, this, &MainWindow::setDataToModel);
    connect(groupForm, &groupWindow::sendData, this, &MainWindow::setDataToModel);
    connect(studentForm, &studentWindow::sendData, this, &MainWindow::setDataToModel);
    connect(subjectForm, &subjectWindow::sendData, this, &MainWindow::setDataToModel);
    connect(teacherForm, &teacherWindow::sendData, this, &MainWindow::setDataToModel);

    // custom message box
    logoutMessageBox.setIcon(QMessageBox::Question);
    yesButton = logoutMessageBox.addButton(tr("Так"), QMessageBox::YesRole);
    logoutMessageBox.addButton(tr("Ні"), QMessageBox::NoRole);
    logoutMessageBox.setDefaultButton(yesButton);
    logoutMessageBox.setWindowTitle("Разлогін");
    logoutMessageBox.setText("Ви дійсно хочете вийти з аккаунта?");
}


void MainWindow::configDefault()
{
    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf", QSettings::IniFormat);

    settingsConfig.setValue("theme", "system");
    settingsConfig.setValue("hostname", "141.136.44.252");
    settingsConfig.setValue("username", "teacher");
    settingsConfig.setValue("password", "P433w0rD!");
    settingsConfig.setValue("databasename", "Gradify");
}


void MainWindow::configInit()
{
    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf", QSettings::IniFormat);

    if (settingsConfig.allKeys().empty())
    {
        configDefault();
    }

    if (settingsConfig.contains("theme"))
    {
        setTheme(settingsConfig.value("theme").toString());

        emit setThemeSettingsUI(theme);
    }
    if (settingsConfig.contains("userlogin"))
    {
        authorization(settingsConfig.value("userlogin").toString());
    }
}


void MainWindow::configWrite(const QString &key, const QVariant &value)
{
    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf", QSettings::IniFormat);
    settingsConfig.setValue(key, value);
}


void MainWindow::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::ActivationChange)
    {
        if (isActiveWindow())
        {
            setWindowOpacity(1);
        }
        else
        {
            setWindowOpacity(0.97);
        }
    }
    else if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (event->Close)
    {
        QApplication::closeAllWindows();
    }
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton and filterWindow->isVisible() and not filterWindow->underMouse())
    {
        filterWindow->close();
    }
    else if (event->button() == Qt::LeftButton and queryWindow->isVisible() and not queryWindow->underMouse())
    {
        queryWindow->close();
    }
}


void MainWindow::on_studentsTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы студентов
     *
    */
    setWindowTitle("Gradify - (Студенти)");
    model->setTable("Студенти");
    model->select();
    currentSelectTable = 0;

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);

    clearStyleButtonTable();

    setEnabledEditButton(true);

    ui->studentsTableButton->setStyleSheet(selectButtonTableStyle);
    ui->searchLineEdit->clear();

    ui->studentsTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/studentsIco.png"));

    emit setTableForFilter(getColumnsNamesAndDatatypes("Студенти"));
    emit changedGradeTable(0);
}


void MainWindow::on_teachersTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы преподавателей
     *
    */
    setWindowTitle("Gradify - (Викладачі)");
    model->setTable("Викладачі");
    model->select();
    currentSelectTable = 1;

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);

    clearStyleButtonTable();

    setEnabledEditButton(true);

    ui->teachersTableButton->setStyleSheet(selectButtonTableStyle);
    ui->searchLineEdit->clear();

    ui->teachersTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/teachersIco.png"));

    emit setTableForFilter(getColumnsNamesAndDatatypes("Викладачі"));
    emit changedGradeTable(1);
}


void MainWindow::on_gradesTableButton_clicked()
{
    setWindowTitle("Gradify - (Оцінки)");
    model->setTable("Оцінки");
    model->select();
    currentSelectTable = 2;

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);

    clearStyleButtonTable();

    setEnabledEditButton(true);

    ui->gradesTableButton->setStyleSheet(selectButtonTableStyle);
    ui->searchLineEdit->clear();

    ui->gradesTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/raitingIco.png"));

    emit setTableForFilter(getColumnsNamesAndDatatypes("Оцінки"));
    emit changedGradeTable(2);
}


void MainWindow::on_groupsTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы групп
     *
    */
    setWindowTitle("Gradify - (Групи)");
    model->setTable("Групи");
    model->select();
    currentSelectTable = 3;

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);

    clearStyleButtonTable();

    setEnabledEditButton(true);

    ui->groupsTableButton->setStyleSheet(selectButtonTableStyle);
    ui->searchLineEdit->clear();

    ui->groupsTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/groupIco.png"));

    emit setTableForFilter(getColumnsNamesAndDatatypes("Групи"));
    emit changedGradeTable(3);
}


void MainWindow::on_subjectsTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы предметы
     *
    */
    setWindowTitle("Gradify - (Предмети)");
    model->setTable("Предмети");
    model->select();
    currentSelectTable = 4;

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);

    clearStyleButtonTable();

    setEnabledEditButton(true);

    ui->subjectsTableButton->setStyleSheet(selectButtonTableStyle);
    ui->searchLineEdit->clear();

    ui->subjectsTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/subjectIco.png"));

    emit setTableForFilter(getColumnsNamesAndDatatypes("Предмети"));
    emit changedGradeTable(4);
}


void MainWindow::clearSelectTable()
{
    ui->tableView->setModel(NULL);
    currentSelectTable = -1;
    closeAllPopUpWindow();
}


void MainWindow::closeAllPopUpWindow()
{
    filterWindow->close();
    queryWindow->close();
}


void MainWindow::closeAllEditForm()
{
    gradeForm->close();
    groupForm->close();
    studentForm->close();
    subjectForm->close();
    teacherForm->close();
}


void MainWindow::closeAllStatisticsForm()
{
    gradeStat->close();
    groupStat->close();
    studentStat->close();
    subjectStat->close();
    teacherStat->close();
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
    ui->gradesTableButton->setIcon(QIcon(":/img/blueMenuIcon/raitingIco.png"));
    ui->groupsTableButton->setIcon(QIcon(":/img/blueMenuIcon/groupIco.png"));
    ui->subjectsTableButton->setIcon(QIcon(":/img/blueMenuIcon/subjectIco.png"));
}


void MainWindow::setTheme(const QString &style)
{
    if (style == "black")
    {
        theme = "black";
        setBlackUI();
    }
    else if (style == "white")
    {
        theme = "white";
        setWhiteUI();
    }
    else
    {
        theme = "system";
        setSystemUI();
    }

    configWrite("theme", theme);
}


void MainWindow::authorization(const QString &login)
{
    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf", QSettings::IniFormat);


    db = QSqlDatabase::addDatabase("QMYSQL");
    // https://gradify.online/
    db.setHostName(settingsConfig.value("hostname").toString());
    db.setUserName(settingsConfig.value("username").toString());
    db.setPassword(settingsConfig.value("password").toString());
    db.setDatabaseName(settingsConfig.value("databasename").toString());

    if (not db.open())
    {
        QMessageBox::critical(this, "Помилка з'єднання", "Перевірте статус серверу або параметри серверу в налаштуваннях!");
        return;
    }

    query = new QSqlQuery(db);
    model = new QSqlTableModel(this, db);
    queryModel = new QSqlQueryModel(this);

    setEnabledButtons(true);
    setEnabledActions(true);

    clearSelectTable();

    ui->authorizationButton->setText(" Привіт, " + login + "!");
    ui->authorizationButton->setStyleSheet(selectButtonAuthStyle);

    isLogin = true;
}


void MainWindow::setFilterForTable(const QString &filterQuery, const QString &currentColumnFilter)
{
    model->setFilter(filterQuery);
    ui->tableView->setModel(model);

    for(int i = 0; i < ui->tableView->model()->columnCount(); ++i)
    {
        if (ui->tableView->model()->headerData(i, Qt::Horizontal).toString() == currentColumnFilter)
        {
            ui->tableView->selectColumn(i);
            break;
        }
    }

    // debug
    //QMessageBox::information(this, "", filterQuery);
}


void MainWindow::on_settingsButton_clicked()
{
    settingWindow->show();

    if (settingWindow->isVisible())
    {
        settingWindow->raise();
    }
}

void MainWindow::userLogout()
{
    isLogin = false;
    setEnabledButtons(false);
    setEnabledEditButton(false);

    clearSelectTable();
    clearStyleButtonTable();
    closeAllEditForm();
    ui->searchLineEdit->clear();

    setWindowTitle("Gradify");
    ui->authorizationButton->setText("Авторизація");
    ui->authorizationButton->setStyleSheet("");

    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf", QSettings::IniFormat);
    settingsConfig.remove("userlogin");
}

void MainWindow::on_authorizationButton_clicked()
{
    if (not isLogin)
    {
        authorizationWindow->show();
    }
    else
    {
        logoutMessageBox.exec();
        if (logoutMessageBox.clickedButton() == yesButton)
        {
            userLogout();
        }
    }
}


void MainWindow::on_addRowButton_clicked()
{
    switch (currentSelectTable)
    {
    case 0:
        connect(this, &MainWindow::createNewRow, studentForm, &studentWindow::newRow);

        emit sendGroupsList(getGroupsNames());
        emit createNewRow();

        disconnect(this, &MainWindow::createNewRow, studentForm, &studentWindow::newRow);
        studentForm->show();
        break;
    case 1:
        connect(this, &MainWindow::createNewRow, teacherForm, &teacherWindow::newRow);

        emit createNewRow();

        disconnect(this, &MainWindow::createNewRow, teacherForm, &teacherWindow::newRow);
        teacherForm->show();
        break;
    case 2:
        connect(this, &MainWindow::createNewRow, gradeForm, &gradeWindow::newRow);
        connect(this, &MainWindow::sendStudentsList, gradeForm, &gradeWindow::setDataStudentComboBox);
        connect(this, &MainWindow::sendSubjectsList, gradeForm, &gradeWindow::setDataSubjectComboBox);

        emit sendSubjectsList(getSubjectsNames());
        emit sendStudentsList(getStudentsNames());
        emit sendTeachersList(getTeachersNames());
        emit createNewRow();

        disconnect(this, &MainWindow::sendSubjectsList, gradeForm, &gradeWindow::setDataSubjectComboBox);
        disconnect(this, &MainWindow::sendStudentsList, gradeForm, &gradeWindow::setDataStudentComboBox);
        disconnect(this, &MainWindow::createNewRow, gradeForm, &gradeWindow::newRow);
        gradeForm->show();
        break;
    case 3:
        connect(this, &MainWindow::createNewRow, groupForm, &groupWindow::newRow);
        connect(this, &MainWindow::sendTeachersList, groupForm, &groupWindow::setDataCuratorComboBox);
        connect(this, &MainWindow::sendCurrentGroup, groupForm, &groupWindow::setDataHeadManComboBox);

        emit createNewRow();
        emit sendTeachersList(getTeachersNames());
        emit sendCurrentGroup("NULL");

        disconnect(this, &MainWindow::sendTeachersList, groupForm, &groupWindow::setDataCuratorComboBox);
        disconnect(this, &MainWindow::sendCurrentGroup, groupForm, &groupWindow::setDataHeadManComboBox);
        disconnect(this, &MainWindow::createNewRow, groupForm, &groupWindow::newRow);
        groupForm->show();
        break;
    case 4:
        connect(this, &MainWindow::createNewRow, subjectForm, &subjectWindow::newRow);
        connect(this, &MainWindow::sendTeachersList, subjectForm, &subjectWindow::setTeacherComboBox);

        emit sendTeachersList(getTeachersNames());
        emit createNewRow();

        disconnect(this, &MainWindow::sendTeachersList, subjectForm, &subjectWindow::setTeacherComboBox);
        disconnect(this, &MainWindow::createNewRow, subjectForm, &subjectWindow::newRow);
        subjectForm->show();
        break;
    }
}


void MainWindow::on_deleteRowButton_clicked()
{
    ui->searchLineEdit->clearFocus();
    closeAllPopUpWindow();

    if (ui->tableView->model()->rowCount() > 0)
    {
        bool ok;
        QString selectedItem = QInputDialog::getItem(this, tr("Видалення запису"),
                                                     tr("Оберіть запис для видалення:"), getCurrentItemTable(),
                                                     ui->tableView->currentIndex().row(), false, &ok);


        if (ok)
        {
            model->removeRow(selectedItem.left(selectedItem.indexOf('.')).toInt() - 1);
            model->select();
        }
    }
    else
    {
        QMessageBox::critical(this, "", "Не знайдено записів для видалення!");
    }
}


void MainWindow::on_editRowButton_clicked()
{
    ui->searchLineEdit->clearFocus();
    closeAllPopUpWindow();

    if (ui->tableView->model()->rowCount() > 0)
    {
        bool ok;
        QString selectedItem = QInputDialog::getItem(this, tr("Редагування запису"),
                                                     tr("Оберіть запис для редагування:"), getCurrentItemTable(),
                                                     ui->tableView->currentIndex().row(), false, &ok);

        if (ok)
        {
            switch (currentSelectTable)
            {
            case 0:
                connect(this, &MainWindow::setDataEditForm, studentForm, &studentWindow::setData);

                emit sendGroupsList(getGroupsNames());
                emit setDataEditForm(selectedItem, getRowData(selectedItem.QString::left(selectedItem.indexOf('.')).toInt()));

                disconnect(this, &MainWindow::setDataEditForm, studentForm, &studentWindow::setData);
                studentForm->show();
                break;
            case 1:
                connect(this, &MainWindow::setDataEditForm, teacherForm, &teacherWindow::setData);

                emit setDataEditForm(selectedItem, getRowData(selectedItem.left(selectedItem.indexOf('.')).toInt()));

                disconnect(this, &MainWindow::setDataEditForm, teacherForm, &teacherWindow::setData);
                teacherForm->show();
                break;
            case 2:
                connect(this, &MainWindow::setDataEditForm, gradeForm, &gradeWindow::setData);
                connect(this, &MainWindow::sendStudentsList, gradeForm, &gradeWindow::setDataStudentComboBox);
                connect(this, &MainWindow::sendSubjectsList, gradeForm, &gradeWindow::setDataSubjectComboBox);

                emit sendSubjectsList(getSubjectsNames());
                emit sendStudentsList(getStudentsNames());
                emit setDataEditForm(selectedItem, getRowData(selectedItem.left(selectedItem.indexOf('.')).toInt()));

                disconnect(this, &MainWindow::sendSubjectsList, gradeForm, &gradeWindow::setDataSubjectComboBox);
                disconnect(this, &MainWindow::sendStudentsList, gradeForm, &gradeWindow::setDataStudentComboBox);
                disconnect(this, &MainWindow::setDataEditForm, gradeForm, &gradeWindow::setData);
                gradeForm->show();
                break;
            case 3:
                connect(this, &MainWindow::setDataEditForm, groupForm, &groupWindow::setData);
                connect(this, &MainWindow::sendTeachersList, groupForm, &groupWindow::setDataCuratorComboBox);
                connect(this, &MainWindow::sendCurrentGroup, groupForm, &groupWindow::setDataHeadManComboBox);

                emit sendTeachersList(getTeachersNames());
                emit sendCurrentGroup(selectedItem);
                emit setDataEditForm(selectedItem, getRowData(selectedItem.left(selectedItem.indexOf('.')).toInt()));

                disconnect(this, &MainWindow::setDataEditForm, groupForm, &groupWindow::setData);
                disconnect(this, &MainWindow::sendTeachersList, groupForm, &groupWindow::setDataCuratorComboBox);
                disconnect(this, &MainWindow::sendCurrentGroup, groupForm, &groupWindow::setDataHeadManComboBox);
                groupForm->show();
                break;
            case 4:
                connect(this, &MainWindow::setDataEditForm, subjectForm, &subjectWindow::setData);
                connect(this, &MainWindow::sendTeachersList, subjectForm, &subjectWindow::setTeacherComboBox);

                emit sendTeachersList(getTeachersNames());
                emit setDataEditForm(selectedItem, getRowData(selectedItem.left(selectedItem.indexOf('.')).toInt()));

                disconnect(this, &MainWindow::sendTeachersList, subjectForm, &subjectWindow::setTeacherComboBox);
                disconnect(this, &MainWindow::setDataEditForm, subjectForm, &subjectWindow::setData);
                subjectForm->show();
                break;
            }
        }
    }
    else
    {
        QMessageBox::critical(this, "", "Не знайдено записів для редагування!");
    }
}


void MainWindow::on_filterButton_clicked()
{
    ui->searchLineEdit->clearFocus();

    if (filterWindow->isVisible())
    {
        filterWindow->close();
    }
    else
    {
        queryWindow->close();

        filterWindow->move(ui->filterButton->x() * 2,
                           ui->filterButton->y() + ui->mainTableFrame->y() + 42);
        filterWindow->show();
    }
}


void MainWindow::on_queryButton_clicked()
{
    ui->searchLineEdit->clearFocus();

    if (queryWindow->isVisible())
    {
        queryWindow->close();
    }
    else
    {
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

    if(not outputFile.isOpen())
    {
        QMessageBox::critical(this,"","Не вдалося зберегти звіт");
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
    if (not ui->searchLineEdit->text().isEmpty())
    {
        QString searchString;

        for (int i = 0; i < ui->tableView->model()->columnCount(); ++i)
        {
            searchString += "`" + ui->tableView->model()->headerData(i, Qt::Horizontal).toString() + "` LIKE" +
                            "'%" + ui->searchLineEdit->text() + "%'";

            if (i not_eq ui->tableView->model()->columnCount() - 1)
            {
                searchString += " OR ";
            }
        }

        model->setFilter(searchString);
        ui->tableView->setModel(model);
    }
    else
    {
        clearFilterForTable();
    }
}


void MainWindow::setDataToModel(QStringList dataList, bool isNewRow)
{
    if (isNewRow)
    {
        QString newRow = "INSERT INTO ";
        QSqlQueryModel *queryModel = new QSqlQueryModel(this);
        QTableView *tableView = new QTableView(this);

        switch (currentSelectTable)
        {
        case 0:
            newRow += "`Студенти`";
            queryModel->setQuery("SELECT MAX(`Код`) "
                                 "FROM Студенти");
            break;
        case 1:
            newRow += "`Викладачі` ";
            queryModel->setQuery("SELECT MAX(`Код`) "
                                 "FROM Викладачі");
            break;
        case 2:
            newRow += "`Оцінки` ";
            queryModel->setQuery("SELECT MAX(`Код`) "
                                 "FROM Оцінки");
            break;
        case 3:
            newRow += "`Групи` ";
            queryModel->setQuery("SELECT MAX(`Код`) "
                                 "FROM Групи");
            break;
        case 4:
            newRow += "`Предмети` ";
            queryModel->setQuery("SELECT MAX(`Код`) "
                                 "FROM Предмети");
            break;
        }

        tableView->setModel(queryModel);

        newRow += "(";

        for (int i = 0; i < model->columnCount(); ++i)
        {
            newRow += "`" + model->headerData(i, Qt::Horizontal).toString();

            if (i not_eq model->columnCount() - 1)
            {
                newRow += "`, ";
            }
            else
            {
                newRow += "`)";
            }
        }

        newRow += "\nVALUES ('" + QString::number(tableView->model()->index(0, 0).data().toInt() + 1) + "',";

        for (int i = 1; i < model->columnCount(); ++i)
        {
            newRow += "'" + dataList[i];

            if (i not_eq model->columnCount() - 1)
            {
                newRow += "', ";
            }
            else
            {
                newRow += "')";
            }
        }

        QSqlQueryModel *sqlModel = new QSqlQueryModel();
        sqlModel->setQuery(newRow);
        model->select();
    }
    else
    {
        QString queryEdit = "UPDATE ";

        switch (currentSelectTable)
        {
        case 0:
            queryEdit += "`Студенти`";
            break;
        case 1:
            queryEdit += "`Викладачі` ";
            break;
        case 2:
            queryEdit += "`Оцінки`";
            break;
        case 3:
            queryEdit += "`Групи`";
            break;
        case 4:
            queryEdit += "`Предмети`";
            break;
        }
        queryEdit += " \nSET";

        for (int i = 1; i < model->columnCount(); ++i)
        {
            queryEdit += "`" + model->headerData(i, Qt::Horizontal).toString() + "` = '" + dataList[i];

            if (i not_eq model->columnCount() - 1)
            {
                queryEdit += "', \n";
            }
            else
            {
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
    if (query == "NULL")
    {
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->sortByColumn(0, Qt::AscendingOrder);
    }
    else
    {
        queryModel->setQuery(query);
        ui->tableView->setModel(queryModel);
    }
}


void MainWindow::clearFilterForTable()
{
    model->setFilter("");
    model->select();
    ui->tableView->setModel(model);
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
    QMap<QString,QString> headerListMap;

    if (not tableName.isEmpty())
    {
        QSqlQueryModel *queryModel = new QSqlQueryModel(this);
        QTableView *tableView = new QTableView(this);

        queryModel->setQuery("SELECT COLUMN_NAME, DATA_TYPE "
                             "FROM INFORMATION_SCHEMA.COLUMNS "
                             "WHERE table_schema = 'Gradify' "
                             "AND table_name = '" + tableName + "'"
                             "AND NOT column_name = 'Код'");

        tableView->setModel(queryModel);

        for (int row = 0; row < queryModel->rowCount(); ++row)
        {
            headerListMap.insert(tableView->model()->index(row, 0).data().toString(),
                                 tableView->model()->index(row, 1).data().toString());
        }
    }

    return headerListMap;
}


QStringList MainWindow::getCurrentItemTable()
{
    QStringList str;

    switch (currentSelectTable)
    {
    case 0:
    case 1:
        for (int i = 0; i < ui->tableView->model()->rowCount(); ++i)
        {
            str << QString::number(i + 1) +  ". "
                   + ui->tableView->model()->data(model->index(i, 1)).toString() + " "
                   + ui->tableView->model()->data(model->index(i, 2)).toString() + " "
                   + ui->tableView->model()->data(model->index(i, 3)).toString();
        }
        break;
    case 2:
        for (int i = 0; i < ui->tableView->model()->rowCount(); ++i)
        {
            str << QString::number(i + 1) +  ". "
                   + ui->tableView->model()->data(model->index(i, 2)).toString() + " - "
                   + ui->tableView->model()->data(model->index(i, 1)).toString() + ", "
                   + ui->tableView->model()->data(model->index(i, 4)).toString() + " ("
                   + ui->tableView->model()->data(model->index(i, 3)).toString() + ")";
        }
        break;
    case 3:
    case 4:
        for (int i = 0; i < ui->tableView->model()->rowCount(); ++i)
        {
            str << QString::number(i + 1) +  ". "
                   + ui->tableView->model()->data(model->index(i, 1)).toString();
        }
        break;
    }

    return str;
}


QStringList MainWindow::getRowData(const int &row)
{
    QStringList listData;

    for (int j = 0; j < model->columnCount(); ++j)
    {
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

    for (int row = 0; row < virualQueryModel->rowCount(); ++row)
    {
        studentList.append(virtualTable->model()->index(row, 0).data().toString() + " " +
                           virtualTable->model()->index(row, 1).data().toString() + " " +
                           virtualTable->model()->index(row, 2).data().toString() );
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

    for (int row = 0; row < virualQueryModel->rowCount(); ++row)
    {
        teacherList.append(virtualTable->model()->index(row, 0).data().toString() + " " +
                           virtualTable->model()->index(row, 1).data().toString() + " " +
                           virtualTable->model()->index(row, 2).data().toString());
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

    for (int row = 0; row < virualQueryModel->rowCount(); ++row)
    {
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

    for (int row = 0; row < virualQueryModel->rowCount(); ++row)
    {
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

    for (int row = 0; row < virualQueryModel->rowCount(); ++row)
    {
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

    for (int row = 0; row < virualQueryModel->rowCount(); ++row)
    {
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

    for (int row = 0; row < virualQueryModel->rowCount(); ++row)
    {
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

void MainWindow::fillHTMLTable(QString& textHTML, QTableView* tableView){
    for (int i = 0; i < tableView->model()->columnCount(); ++i)
    {
        textHTML += "   <th>" + tableView->model()->headerData(i, Qt::Horizontal ).toString() +"</th>\n";
    }

    textHTML += "</tr>\n";

    for (int i = 0; i < tableView->model()->rowCount(); ++i)
    {
        textHTML += "<tr>\n";

        for (int j = 0; j < tableView->model()->columnCount(); ++j)
        {
            if (i % 2 not_eq 0)
            {
                textHTML += "   <td class='la'>" + tableView->model()->index(i,j).data().toString() + "</td>\n";
            }
            else
            {
                textHTML += "   <td>" + tableView->model()->index(i,j).data().toString() + "</td>\n";
            }
        }
        textHTML += "</tr>\n";
    }
    textHTML+= "</tbody></table>";
}


void MainWindow::on_currentTableReportButton_clicked()
{
    if (model->rowCount() > 0)
    {
        QString typeFile;
        QString pathToSave = QFileDialog::getSaveFileName(nullptr,
                                                          tr("Збереження звіту"),
                                                          "/Users/" + qgetenv("USER") + "/Desktop",
                                                          "PDF формат (*.pdf);;HTML формат (*.html)",
                                                          &typeFile);
        if (not pathToSave.isEmpty())
        {
            QString textHTML = getHeaderHTML();
            textHTML += "<h2 align='center'>Звіт Gradify</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";

            fillHTMLTable(textHTML, ui->tableView);

            if (typeFile == "HTML формат (*.html)")
            {
                printDocumentToHTML(pathToSave, textHTML);
            }
            else if (typeFile == "PDF формат (*.pdf)")
            {
                printDocumentToPDF(pathToSave, textHTML);
            }
        }
    }
    else
    {
        QMessageBox::information(this,"","У таблиці не знайдено записів!");
    }
}


void MainWindow::on_studentsReportButton_clicked()
{
    bool ok;

    QString selectedGroup = QInputDialog::getItem(this, tr("Звіт за студентами групи"),
                                                  tr("Оберіть групу:"), getGroupsNames(),
                                                  0, false, &ok);
    if (ok)
    {
        QString typeFile;
        QString pathToSave = QFileDialog::getSaveFileName(nullptr,
                                                          tr("Збереження звіту"),
                                                          "/Users/" + qgetenv("USER") + "/Desktop",
                                                          "PDF формат (*.pdf);;HTML формат (*.html)",
                                                          &typeFile);
        if (not pathToSave.isEmpty())
        {
            QSqlQueryModel *queryModel = new QSqlQueryModel(this);
            QTableView *tableView = new QTableView(this);

            queryModel->setQuery("SELECT * "
                                 "FROM `Студенти`"
                                 "WHERE `Студенти`.`Група` = '" + selectedGroup + "'");
            tableView->setModel(queryModel);

            QString textHTML = getHeaderHTML();
            textHTML += "<h2 align='center'>Звіт за студентами групи «" + selectedGroup + "»</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";

            fillHTMLTable(textHTML, tableView);

            queryModel->setQuery("SELECT `Куратор`,`Староста`"
                                        "FROM `Групи`"
                                        "WHERE `Групи`.`Назва` = '" + selectedGroup + "'");
            tableView->setModel(queryModel);

            textHTML += "<tr>\n <td class='info'>Куратор</td>";


            QString bufStr = tableView->model()->index(0, 0) .data().toString();
            textHTML += "\n <td>" + bufStr.left(bufStr.indexOf(' ')) + "</td>";
            bufStr.remove(0, bufStr.indexOf(' ') + 1);
            textHTML += "\n <td>" + bufStr.left(bufStr.lastIndexOf(' ')) + "</td>";
            bufStr.remove(0, bufStr.lastIndexOf(' ') + 1);
            textHTML += "\n <td>" + bufStr + "</td>\n</tr>\n";

            bufStr = tableView->model()->index(0, 1) .data().toString();
            textHTML += "\n<tr>\n   <td class='info'>Староста</td>";
            textHTML += "\n <td>" + bufStr.left(bufStr.indexOf(' ')) + "</td>";
            bufStr.remove(0, bufStr.indexOf(' ') + 1);
            textHTML += "\n <td>" + bufStr.left(bufStr.lastIndexOf(' ')) + "</td>";
            bufStr.remove(0, bufStr.lastIndexOf(' ') + 1);
            textHTML += "\n <td>" + bufStr + "</td>\n</tr>\n</table>\n";

            if (typeFile == "HTML формат (*.html)")
            {
                printDocumentToHTML(pathToSave, textHTML);
            }
            else if (typeFile == "PDF формат (*.pdf)")
            {
                printDocumentToPDF(pathToSave, textHTML);
            }
        }
    }
}


void MainWindow::on_teachersReportButton_clicked()
{
    // bool flag for get events status
    bool ok;

    // select teachers category
    QString selectedCategory = QInputDialog::getItem(this, tr("Звіт по викладачам"),
                                                  tr("Оберіть категорію викладача:"), getCategoryTeachers(),
                                                  0, false, &ok);

    if (ok)
    {
        // create teachers list
        QStringList teachersList;
        QSqlQueryModel *virtualQueryModel = new QSqlQueryModel(this);
        QTableView *virtualTable = new QTableView(this);

        virtualQueryModel->setQuery("SELECT `Прізвище`"
                                    "FROM `Викладачі` "
                                    "WHERE `Викладачі`.`Категорія` = '" + selectedCategory + "';");

        virtualTable->setModel(virtualQueryModel);

        if (virtualQueryModel->rowCount() > 0)
        {
            teachersList.append("Всі викладачі");
            for (int row = 0; row < virtualQueryModel->rowCount(); ++row)
            {
                teachersList.append(virtualTable->model()->index(row, 0).data().toString());
            }
        }
        else
        {
            QMessageBox::information(this, "Помилка", "Викладачів даної категорії немає!");
            return;
        }

        // string choice teacher
        QString optionChoice = QInputDialog::getItem(this, tr("Звіт по викладачам"),
                                                     tr("Оберіть викладача:"), teachersList,
                                                     0, false, &ok);

        if (ok)
        {
            // get path to report save
            QString typeFile;
            QString pathToSave = QFileDialog::getSaveFileName(nullptr,
                                                              tr("Збереження звіту"),
                                                              "/Users/" + qgetenv("USER") + "/Desktop",
                                                              "PDF формат (*.pdf);;HTML формат (*.html)",
                                                              &typeFile);
            if (not pathToSave.isEmpty())
            {
                QSqlQueryModel *virtualQueryModel = new QSqlQueryModel(this);
                QTableView *virtualTableView = new QTableView(this);

                QString textHTML = getHeaderHTML();

                if (optionChoice == "Всі викладачі")
                {
                    virtualQueryModel->setQuery("SELECT * "
                                                "FROM `Викладачі`"
                                                "WHERE `Викладачі`.`Категорія` = '" + selectedCategory + "';");
                    textHTML += "<h2 align='center'>Викладачі з категорією «" + selectedCategory + "»</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";

                }
                else
                {
                    virtualQueryModel->setQuery("SELECT * "
                                                "FROM `Викладачі` "
                                                "WHERE `Викладачі`.`Категорія` = '" + selectedCategory + "' "
                                                "AND `Викладачі`.`Прізвище` = '" + optionChoice + "';");
                    textHTML += "<h2 align='center'>Викладач з категорією «" + selectedCategory + "» " + optionChoice +"</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";

                }

                virtualTableView->setModel(virtualQueryModel);

                fillHTMLTable(textHTML, virtualTableView);

                // statistics chart

                if (optionChoice != "Всі викладачі")
                {
                    virtualQueryModel->setQuery("SELECT `Предмети`.`Назва`, COUNT(`Оцінки`.`Оцінка`)"
                                                "FROM `Оцінки`, `Предмети`, `Викладачі`"
                                                "WHERE SUBSTRING_INDEX(`Предмети`.`Викладач`, ' ', 1) = '" + optionChoice + "'"
                                                "AND `Предмети`.`Назва` = `Оцінки`.`Предмет`"
                                                "GROUP BY(`Предмети`.`Назва`);");

                    if (virtualQueryModel->rowCount() > 0){
                        // fill pie series
                        virtualTable->setModel(virtualQueryModel);

                        QPieSeries *pieSeries = new QPieSeries();

                        for (int row = 0; row < virtualQueryModel->rowCount(); ++row)
                        {
                            pieSeries->append(virtualTable->model()->index(row, 0).data().toString(),
                                              virtualTable->model()->index(row, 1).data().toInt() / 21);
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


                        chartView->grab().save(pathToSave.left(pathToSave.lastIndexOf('.')) + ".png", "PNG");

                        textHTML += "<br><br><br><center><img src=" + pathToSave.left(pathToSave.lastIndexOf('.')) + ".png"
                                  + " width=\"640\" height=\"480\"></center>";
                    }
                }

                if (typeFile == "HTML формат (*.html)")
                {
                    printDocumentToHTML(pathToSave, textHTML);
                }
                else if (typeFile == "PDF формат (*.pdf)")
                {
                    printDocumentToPDF(pathToSave, textHTML);
                }
            }
        }
    }

}


void MainWindow::on_gradesReportButton_clicked()
{
    bool ok;

    QString selectedStudent = QInputDialog::getItem(this, tr("Звіт по оцінкам"),
                                                  tr("Оберіть отримувача оцінок:"), getStudentsNames(),
                                                  0, false, &ok);
    if (ok)
    {
        QString typeFile;
        QString pathToSave = QFileDialog::getSaveFileName(nullptr,
                                                          tr("Збереження звіту"),
                                                          "/Users/" + qgetenv("USER") + "/Desktop",
                                                          "PDF формат (*.pdf);;HTML формат (*.html)",
                                                          &typeFile);
        if (not pathToSave.isEmpty())
        {
            QSqlQueryModel *queryModel = new QSqlQueryModel(this);
            QTableView *tableView = new QTableView(this);

            queryModel->setQuery("SELECT * "
                                 "FROM `Оцінки`"
                                 "WHERE `Оцінки`.`Отримувач` = '" + selectedStudent + "'");
            tableView->setModel(queryModel);

            QString textHTML = getHeaderHTML();
            textHTML += "<h2 align='center'>Звіт за оцінками студента «" + selectedStudent + "»</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";

            fillHTMLTable(textHTML, tableView);

            if (typeFile == "HTML формат (*.html)")
            {
                printDocumentToHTML(pathToSave, textHTML);
            }
            else if (typeFile == "PDF формат (*.pdf)")
            {
                printDocumentToPDF(pathToSave, textHTML);
            }
        }
    }
}


void MainWindow::on_groupsReportButton_clicked()
{
    bool ok;

    QString selectedTypeSubject = QInputDialog::getItem(this, tr("Звіт за спеціальностями груп"),
                                                  tr("Оберіть спеціальність групи:"), getGroupsSpecial(),
                                                  0, false, &ok);
    if (ok)
    {
        QString typeFile;
        QString pathToSave = QFileDialog::getSaveFileName(nullptr,
                                                          tr("Збереження звіту"),
                                                          "/Users/" + qgetenv("USER") + "/Desktop",
                                                          "PDF формат (*.pdf);;HTML формат (*.html)",
                                                          &typeFile);
        if (not pathToSave.isEmpty())
        {
            QSqlQueryModel *queryModel = new QSqlQueryModel(this);
            QTableView *tableView = new QTableView(this);

            queryModel->setQuery("SELECT * "
                                 "FROM `Групи`"
                                 "WHERE `Групи`.`Спеціальність` = '" + selectedTypeSubject + "'");
            tableView->setModel(queryModel);

            QString textHTML = getHeaderHTML();
            textHTML += "<h2 align='center'>Звіт за спеціальністю «" + selectedTypeSubject + "»</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";

            fillHTMLTable(textHTML, tableView);

            if (typeFile == "HTML формат (*.html)")
            {
                printDocumentToHTML(pathToSave, textHTML);
            }
            else if (typeFile == "PDF формат (*.pdf)")
            {
                printDocumentToPDF(pathToSave, textHTML);
            }
        }
    }
}


void MainWindow::on_subjectsReportButton_clicked()
{
    bool ok;

    QString selectedTypeSubject = QInputDialog::getItem(this, tr("Звіт за предметами"),
                                                  tr("Оберіть тип предмету:"), getSubjectsTypes(),
                                                  0, false, &ok);
    if (ok)
    {
        QString typeFile;
        QString pathToSave = QFileDialog::getSaveFileName(nullptr,
                                                          tr("Збереження звіту"),
                                                          "/Users/" + qgetenv("USER") + "/Desktop",
                                                          "PDF формат (*.pdf);;HTML формат (*.html)",
                                                          &typeFile);
        if (not pathToSave.isEmpty())
        {
            QSqlQueryModel *queryModel = new QSqlQueryModel(this);
            QTableView *tableView = new QTableView(this);

            queryModel->setQuery("SELECT * "
                                 "FROM `Предмети`"
                                 "WHERE `Предмети`.`Тип` = '" + selectedTypeSubject + "'");
            tableView->setModel(queryModel);

            QString textHTML = getHeaderHTML();
            textHTML += "<h2 align='center'>Звіт за типом предмета «" + selectedTypeSubject + "»</h2>\n<table ALIGN = 'center'>\n<p2 id='transpert'>f</p2><tr>";

            fillHTMLTable(textHTML, tableView);

            if (typeFile == "HTML формат (*.html)")
            {
                printDocumentToHTML(pathToSave, textHTML);
            }
            else if (typeFile == "PDF формат (*.pdf)")
            {
                printDocumentToPDF(pathToSave, textHTML);
            }
        }
    }
}


//=========================================================
//
//
//          This code for styling theme application
//          Warning! Many line code.
//
//
//=========================================================

//====================
//
// set black style
//
//====================


void MainWindow::setBlackUI()
{
    QFile file(":/styles/black/mainWindow/mainWindow.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    styleF.setFileName(":/styles/black/mainWindow/selectButtonTableStyle.qss");
    styleF.open(QFile::ReadOnly);
    selectButtonTableStyle = styleF.readAll();
    styleF.close();

    file.setFileName(":/styles/black/mainWindow/outLoginButton.qss");
    file.open(QFile::ReadOnly);
    selectButtonAuthStyle = QLatin1String(file.readAll());
    file.close();

    if (isLogin)
    {
        ui->authorizationButton->setStyleSheet(selectButtonAuthStyle);
    }

    ui->searchLineEdit->setIconSearchButton(QIcon(":/img/blackMenuIcon/search.png"), QSize(12, 12));
    ui->searchLineEdit->setIconClearButton(QIcon(":/img/whiteMenuIcon/clearLoginIco.png"), QSize(12, 12));

    setCurrentIconAction();

    switch (currentSelectTable)
    {
    case 0:
        ui->studentsTableButton->setStyleSheet(selectButtonTableStyle);
        ui->studentsTableButton->setIcon(QIcon(":/img/blackMenuIcon/studentsIco.png"));
        break;
    case 1:
        ui->teachersTableButton->setStyleSheet(selectButtonTableStyle);
        ui->teachersTableButton->setIcon(QIcon(":/img/blackMenuIcon/teachersIco.png"));
        break;
    case 2:
        ui->gradesTableButton->setStyleSheet(selectButtonTableStyle);
        ui->gradesTableButton->setIcon(QIcon(":/img/blackMenuIcon/raitingIco.png"));
        break;
    case 3:
        ui->groupsTableButton->setStyleSheet(selectButtonTableStyle);
        ui->groupsTableButton->setIcon(QIcon(":/img/blackMenuIcon/groupIco.png"));
        break;
    case 4:
        ui->subjectsTableButton->setStyleSheet(selectButtonTableStyle);
        ui->subjectsTableButton->setIcon(QIcon(":/img/blackMenuIcon/subjectIco.png"));
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
    QFile file(":/styles/white/mainWindow/mainWindow.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    file.setFileName(":/styles/white/mainWindow/selectButtonTableStyle.qss");
    file.open(QFile::ReadOnly);
    selectButtonTableStyle = QLatin1String(file.readAll());
    file.close();

    file.setFileName(":/styles/white/mainWindow/outLoginButton.qss");
    file.open(QFile::ReadOnly);
    selectButtonAuthStyle = QLatin1String(file.readAll());
    file.close();

    if (isLogin)
    {
        ui->authorizationButton->setStyleSheet(selectButtonAuthStyle);
    }

    ui->searchLineEdit->setIconSearchButton(QIcon(":/img/blackMenuIcon/search.png"), QSize(12, 12));
    ui->searchLineEdit->setIconClearButton(QIcon(":/img/blackMenuIcon/clearLoginIco.png"), QSize(12, 12));

    setCurrentIconAction();

    switch (currentSelectTable)
    {
    case 0:
        ui->studentsTableButton->setStyleSheet(selectButtonTableStyle);
        ui->studentsTableButton->setIcon(QIcon(":/img/whiteMenuIcon/studentsIco.png"));
        break;
    case 1:
        ui->teachersTableButton->setStyleSheet(selectButtonTableStyle);
        ui->teachersTableButton->setIcon(QIcon(":/img/whiteMenuIcon/teachersIco.png"));
        break;
    case 2:
        ui->gradesTableButton->setStyleSheet(selectButtonTableStyle);
        ui->gradesTableButton->setIcon(QIcon(":/img/whiteMenuIcon/raitingIco.png"));
        break;
    case 3:
        ui->groupsTableButton->setStyleSheet(selectButtonTableStyle);
        ui->groupsTableButton->setIcon(QIcon(":/img/whiteMenuIcon/groupIco.png"));
        break;
    case 4:
        ui->subjectsTableButton->setStyleSheet(selectButtonTableStyle);
        ui->subjectsTableButton->setIcon(QIcon(":/img/whiteMenuIcon/subjectIco.png"));
        break;
    }
}


void MainWindow::setSystemUI()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(), 1 - baseColor.greenF(), 1 - baseColor.blueF());

    if (newBase.name() == "#000000")
    {
        theme = "white";
        setWhiteUI();
    }
    else
    {
        theme = "black";
        setBlackUI();
    }
}


void MainWindow::setCurrentIconAction()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(), 1 - baseColor.greenF(), 1 - baseColor.blueF());

    QString iconColor = newBase.name() == "#000000" ? "black" : "white";

    ui->openStudTabAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/studentsIco.png"));
    ui->openTeachTabAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/teachersIco.png"));
    ui->openGradesTabAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/raitingIco.png"));
    ui->openGroupTabAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/groupIco.png"));
    ui->openSubjTabAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/subjectIco.png"));

    ui->addRowAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/newRecord.png"));
    ui->deleteRowAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/deleteRecord.png"));
    ui->editRowAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/editRecord.png"));

    ui->currentTableReportAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/reportCurrentTable.png"));
    ui->studentsReportAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/reportStudent.png"));
    ui->teachersReportAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/reportTeachers.png"));
    ui->gradesReportAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/reportRaiting.png"));
    ui->groupsReportAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/reportGroup.png"));
    ui->subjectsReportAction->setIcon(QIcon(":/img/" + iconColor + "ActionsIcon/reportItem.png"));
}


//=========================================================
//
//                  Realisation menuBar code
//
//=========================================================

void MainWindow::on_addRowAction_triggered()
{
    on_addRowButton_clicked();
}


void MainWindow::on_deleteRowAction_triggered()
{
    on_deleteRowButton_clicked();
}


void MainWindow::on_editRowAction_triggered()
{
    on_editRowButton_clicked();
}


void MainWindow::on_openStudTabAction_triggered()
{
    on_studentsTableButton_clicked();
}


void MainWindow::on_openTeachTabAction_triggered()
{
    on_teachersTableButton_clicked();
}


void MainWindow::on_openGradesTabAction_triggered()
{
    on_gradesTableButton_clicked();
}


void MainWindow::on_openGroupTabAction_triggered()
{
    on_groupsTableButton_clicked();
}


void MainWindow::on_openSubjTabAction_triggered()
{
    on_subjectsTableButton_clicked();
}


void MainWindow::on_openManual_triggered()
{
    QDesktopServices::openUrl(QUrl("https://gradify.online/Посібник_користувача.pdf", QUrl::TolerantMode));
}


void MainWindow::on_studentsReportAction_triggered()
{
    on_studentsReportButton_clicked();
}


void MainWindow::on_teachersReportAction_triggered()
{
    on_teachersReportButton_clicked();
}


void MainWindow::on_groupsReportAction_triggered()
{
    on_groupsReportButton_clicked();
}


void MainWindow::on_gradesReportAction_triggered()
{
    on_gradesReportButton_clicked();
}


void MainWindow::on_subjectsReportAction_triggered()
{
    on_subjectsReportButton_clicked();
}


void MainWindow::on_currentTableReportAction_triggered()
{
    on_currentTableReportButton_clicked();
}


void MainWindow::on_about_triggered()
{
    aboutAppWindow->show();
}


void MainWindow::on_statisticsButton_clicked()
{
    closeAllStatisticsForm();

    switch (currentSelectTable)
    {
    case 0:
        studentStat->show();
        break;
    case 1:
        teacherStat->fillChart();
        teacherStat->show();
        break;
    case 2:
        gradeStat->show();
        break;
    case 3:
        groupStat->show();
        emit updateStatisticsComboBoxSignal();
        break;
    case 4:
        subjectStat->fillChart();
        subjectStat->show();
        break;
    }

    emit updateStatisticsSignal();
}

QString MainWindow::modelDataToString(QAbstractItemModel* model)
{
    QString textData;

    for (int col = 0; col < model->columnCount(); ++col)
    {
        textData += model->headerData(col, Qt::Horizontal).toString() + ", ";
    }
    textData += "\n";

    for (int row = 0; row < model->rowCount(); ++row)
    {
        for (int col = 0; col < model->columnCount(); ++col)
        {
                textData += model->data(model->index(row, col)).toString();
                textData += ", ";
        }
        textData += "\n";
    }

    return textData;
}

void MainWindow::on_actionCSV_triggered()
{
    if (model->rowCount() == 0)
    {
        QMessageBox::information(this, "Помилка", "Оберіть таблицю для експорту");
        return;
    }

    QString pathToSave = QFileDialog::getSaveFileName(nullptr,
                                                      tr("Експорт файлу:"),
                                                      "/Users/" + qgetenv("USER") + "/Desktop",
                                                      "CSV files (*.csv);;All files (*.*)", new QString("CSV file (*.csv)"));

    QFile csvFile(pathToSave + ".csv");
    if(csvFile.open(QIODevice::WriteOnly)) {

        QTextStream out(&csvFile);
        out << modelDataToString(model);
        csvFile.close();
    }
}


void MainWindow::on_actionTXT_triggered()
{
    if (model->rowCount() == 0)
    {
        QMessageBox::information(this, "Помилка", "Оберіть таблицю для експорту");
        return;
    }

    QString pathToSave = QFileDialog::getSaveFileName(nullptr,
                                                      tr("Експорт файлу:"),
                                                      "/Users/" + qgetenv("USER") + "/Desktop",
                                                      "Text file (*.txt);;All files (*.*)", new QString("Text file (*.txt)"));

    QFile txtFile(pathToSave);
    if (txtFile.open(QIODevice::WriteOnly))
    {
        QTextStream out(&txtFile);
        out << modelDataToString(model);
        txtFile.close();
    }
}


void MainWindow::on_actionEnglish_Translate_triggered()
{
    qDebug() << "Switching to English (United States)...";
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    qDebug() << "Current locale:" << QLocale::system().name();

    translator.load(":/translations/Gradify_en_US.qm");
    if (qApp->installTranslator(&translator)) {
        qDebug() << "Translation installed successfully.";
    } else {
        qDebug() << "Failed to install translation.";
    }
}



void MainWindow::on_actionUkrainian_Translate_triggered()
{
    qDebug() << "Switching to Ukrainian (Ukraine)...";
    QLocale::setDefault(QLocale(QLocale::Ukrainian, QLocale::Ukraine));
    qDebug() << "Current locale:" << QLocale::system().name();

    translator.load(":/translations/Gradify_ua_UA.qm");
    if (qApp->installTranslator(&translator)) {
        qDebug() << "Translation installed successfully.";
    } else {
        qDebug() << "Failed to install translation.";
    }
}

