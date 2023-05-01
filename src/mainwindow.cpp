#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QInputDialog>
#include <QGraphicsDropShadowEffect>
#include <QKeyEvent>


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

    // filters and requests
    connect(filterWindow, &filterForm::sendFilter, this, &MainWindow::setFilterForTable);
    connect(filterWindow, &filterForm::clearFilter, this, &MainWindow::clearFilterForTable);
    connect(this, &MainWindow::setTableForFilter, filterWindow, &filterForm::setListTable);
    connect(queryWindow, &queryForm::sendQuery, this, &MainWindow::setQueryForTable);

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
            and button->objectName() not_eq "mySQLPushButton" and button->objectName() not_eq "Менять!")
        {
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
    QSettings settingsConfig(QDir::currentPath() + "/gradify.conf", QSettings::IniFormat);
    settingsConfig.setValue("theme", "system");

    settingsConfig.setValue("hostname", "141.136.44.252");
    settingsConfig.setValue("username", "teacher");
    settingsConfig.setValue("password", "P433w0rD!");
    settingsConfig.setValue("databasename", "Gradify");
}

void MainWindow::configInit()
{
    QSettings settingsConfig(QDir::currentPath() + "/gradify.conf", QSettings::IniFormat);

    if (settingsConfig.allKeys().empty())
    {
        configDefault();
    }

    if (settingsConfig.contains("theme"))
    {
        theme = settingsConfig.value("theme").toString();

        if (theme == "white")
        {
            setWhiteUI();
        }
        else if (theme == "black")
        {
            setBlackUI();
        }
        else if (theme == "system")
        {
            setSystemUI();
        }

        emit setThemeSettingsUI(theme);
    }
    if (settingsConfig.contains("userlogin"))
    {
        authorization(settingsConfig.value("userlogin").toString());
    }
}


void MainWindow::configWrite(const QString &key, const QVariant &value)
{
    QSettings settingsConfig(QDir::currentPath() + "/gradify.conf", QSettings::IniFormat);
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
    if (event->button() == Qt::LeftButton and filterWindow->isVisible() and !filterWindow->underMouse())
    {
        filterWindow->close();
    }
    else if (event->button() == Qt::LeftButton and queryWindow->isVisible() and !queryWindow->underMouse())
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

    ui->studentsTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/studentsIco.png"));

    emit setTableForFilter(getColumnsNamesAndDatatypes("Студенти"));
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

    ui->teachersTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/teachersIco.png"));

    emit setTableForFilter(getColumnsNamesAndDatatypes("Викладачі"));
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

    ui->gradesTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/raitingIco.png"));

    emit setTableForFilter(getColumnsNamesAndDatatypes("Оцінки"));
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

    ui->groupsTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/groupIco.png"));

    emit setTableForFilter(getColumnsNamesAndDatatypes("Групи"));
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

    ui->subjectsTableButton->setIcon(QIcon(":/img/" + theme + "MenuIcon/subjectIco.png"));

    emit setTableForFilter(getColumnsNamesAndDatatypes("Предмети"));
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
    QSettings settingsConfig(QDir::currentPath() + "/gradify.conf", QSettings::IniFormat);

    db = QSqlDatabase::addDatabase("QMYSQL");
    // https://gradify.online/
    db.setHostName(settingsConfig.value("hostname").toString());
    db.setUserName(settingsConfig.value("username").toString());
    db.setPassword(settingsConfig.value("password").toString());
    db.setDatabaseName(settingsConfig.value("databasename").toString());

    if (!db.open())
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

    QSettings settingsConfig(QDir::currentPath() + "/gradify.conf", QSettings::IniFormat);
    settingsConfig.remove("userlogin");
}

void MainWindow::on_authorizationButton_clicked()
{
    if (!isLogin)
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
    /* model->insertRow(model->rowCount());
    ui->tableView->scrollToBottom();
    ui->tableView->selectRow(model->rowCount() - 1);
    ui->searchLineEdit->clearFocus(); */

    createNewRow();

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
        connect(this, &MainWindow::sendTeachersList, gradeForm, &gradeWindow::setDataTeacherComboBox);
        connect(this, &MainWindow::sendSubjectsList, gradeForm, &gradeWindow::setDataSubjectComboBox);

        emit sendSubjectsList(getSubjectsNames());
        emit sendStudentsList(getStudentsNames());
        emit sendTeachersList(getTeachersNames());
        emit createNewRow();

        disconnect(this, &MainWindow::sendSubjectsList, gradeForm, &gradeWindow::setDataSubjectComboBox);
        disconnect(this, &MainWindow::sendStudentsList, gradeForm, &gradeWindow::setDataStudentComboBox);
        disconnect(this, &MainWindow::sendTeachersList, gradeForm, &gradeWindow::setDataTeacherComboBox);
        disconnect(this, &MainWindow::createNewRow, gradeForm, &gradeWindow::newRow);
        gradeForm->show();
        break;
    case 3:
        connect(this, &MainWindow::createNewRow, groupForm, &groupWindow::newRow);
        connect(this, &MainWindow::sendTeachersList, groupForm, &groupWindow::setDataCuratorComboBox);
        connect(this, &MainWindow::sendStudentsList, groupForm, &groupWindow::setDataHeadManComboBox);

        emit createNewRow();
        emit sendTeachersList(getTeachersNames());
        emit sendStudentsList(getStudentsNames());

        disconnect(this, &MainWindow::sendTeachersList, groupForm, &groupWindow::setDataCuratorComboBox);
        disconnect(this, &MainWindow::sendStudentsList, groupForm, &groupWindow::setDataHeadManComboBox);
        disconnect(this, &MainWindow::createNewRow, groupForm, &groupWindow::newRow);
        groupForm->show();
        break;
    case 4:
        connect(this, &MainWindow::createNewRow, subjectForm, &subjectWindow::newRow);

        emit createNewRow();

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
                connect(this, &MainWindow::sendTeachersList, gradeForm, &gradeWindow::setDataTeacherComboBox);
                connect(this, &MainWindow::sendSubjectsList, gradeForm, &gradeWindow::setDataSubjectComboBox);

                emit sendSubjectsList(getSubjectsNames());
                emit sendStudentsList(getStudentsNames());
                emit sendTeachersList(getTeachersNames());
                emit setDataEditForm(selectedItem, getRowData(selectedItem.left(selectedItem.indexOf('.')).toInt()));

                disconnect(this, &MainWindow::sendSubjectsList, gradeForm, &gradeWindow::setDataSubjectComboBox);
                disconnect(this, &MainWindow::sendStudentsList, gradeForm, &gradeWindow::setDataStudentComboBox);
                disconnect(this, &MainWindow::sendTeachersList, gradeForm, &gradeWindow::setDataTeacherComboBox);
                disconnect(this, &MainWindow::setDataEditForm, gradeForm, &gradeWindow::setData);
                gradeForm->show();
                break;
            case 3:
                connect(this, &MainWindow::setDataEditForm, groupForm, &groupWindow::setData);
                connect(this, &MainWindow::sendTeachersList, groupForm, &groupWindow::setDataCuratorComboBox);
                connect(this, &MainWindow::sendStudentsList, groupForm, &groupWindow::setDataHeadManComboBox);

                emit sendTeachersList(getTeachersNames());
                emit sendStudentsList(getStudentsNames());
                emit setDataEditForm(selectedItem, getRowData(selectedItem.left(selectedItem.indexOf('.')).toInt()));

                disconnect(this, &MainWindow::setDataEditForm, groupForm, &groupWindow::setData);
                disconnect(this, &MainWindow::sendTeachersList, groupForm, &groupWindow::setDataCuratorComboBox);
                disconnect(this, &MainWindow::sendStudentsList, groupForm, &groupWindow::setDataHeadManComboBox);
                groupForm->show();
                break;
            case 4:
                connect(this, &MainWindow::setDataEditForm, subjectForm, &subjectWindow::setData);
                emit setDataEditForm(selectedItem, getRowData(selectedItem.left(selectedItem.indexOf('.')).toInt()));
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


void MainWindow::goSearch()
{
    if (!ui->searchLineEdit->text().isEmpty())
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
            if (i not_eq model->columnCount() - 1)
            {
                newRow += "`" + model->headerData(i, Qt::Horizontal).toString() + "`, ";
            }
            else
            {
                newRow += "`" + model->headerData(i, Qt::Horizontal).toString() + "`)";
            }
        }

        newRow += "\nVALUES ('" + QString::number(tableView->model()->index(0, 0).data().toInt() + 1) + "',";

        for (int i = 1; i < model->columnCount(); ++i)
        {
            if (i not_eq model->columnCount() - 1)
            {
                newRow += "'" + dataList[i] + "', ";
            }
            else
            {
                newRow += "'" + dataList[i] + "')";
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
            if (i not_eq model->columnCount() - 1)
            {
                queryEdit += "`" + model->headerData(i, Qt::Horizontal).toString() + "` = '" + dataList[i] + "', \n";
            }
            else
            {
                queryEdit += "`" + model->headerData(i, Qt::Horizontal).toString() + "` = '" + dataList[i] + "'";
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
    queryModel->setQuery(query);
    ui->tableView->setModel(queryModel);


    //QMessageBox::information(this,"",query);
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

    if (!tableName.isEmpty())
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
                       + ui->tableView->model()->data(model->index(i, 6)).toString() + ")";
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


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}


//=========================================================
//
//                 КОД ДЛЯ ЗВИТОВ ПО ТАБЛИЦАМ!!!
//
//=========================================================


void MainWindow::on_currentTableReportButton_clicked()
{
}


void MainWindow::on_studentsReportButton_clicked()
{
}


void MainWindow::on_teachersReportButton_clicked()
{
}


void MainWindow::on_gradesReportButton_clicked()
{
}


void MainWindow::on_groupsReportButton_clicked()
{
}


void MainWindow::on_subjectsReportButton_clicked()
{
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
        ui->studentsTableButton->setIcon(QIcon(":/img/blackMenuIcon/studenstIco.png"));
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

    if (newBase.name() == "#000000")
    {
        ui->openStudTabAction->setIcon(QIcon(":/img/blackActionsIcon/studentsIco.png"));
        ui->openTeachTabAction->setIcon(QIcon(":/img/blackActionsIcon/teachersIco.png"));
        ui->openGradesTabAction->setIcon(QIcon(":/img/blackActionsIcon/raitingIco.png"));
        ui->openGroupTabAction->setIcon(QIcon(":/img/blackActionsIcon/groupIco.png"));
        ui->openSubjTabAction->setIcon(QIcon(":/img/blackActionsIcon/subjectIco.png"));

        ui->addRowAction->setIcon(QIcon(":/img/blackActionsIcon/newRecord.png"));
        ui->deleteRowAction->setIcon(QIcon(":/img/blackActionsIcon/deleteRecord.png"));
        ui->editRowAction->setIcon(QIcon(":/img/blackActionsIcon/editRecord.png"));

        ui->currentTableReportAction->setIcon(QIcon(":/img/blackActionsIcon/reportCurrentTable.png"));
        ui->studentsReportAction->setIcon(QIcon(":/img/blackActionsIcon/reportStudent.png"));
        ui->teachersReportAction->setIcon(QIcon(":/img/blackActionsIcon/reportTeachers.png"));
        ui->gradesReportAction->setIcon(QIcon(":/img/blackActionsIcon/reportRaiting.png"));
        ui->groupsReportAction->setIcon(QIcon(":/img/blackActionsIcon/reportGroup.png"));
        ui->subjectsReportAction->setIcon(QIcon(":/img/blackActionsIcon/reportItem.png"));
    }
    else
    {
        ui->openStudTabAction->setIcon(QIcon(":/img/whiteActionsIcon/studentsIco.png"));
        ui->openTeachTabAction->setIcon(QIcon(":/img/whiteActionsIcon/teachersIco.png"));
        ui->openGradesTabAction->setIcon(QIcon(":/img/whiteActionsIcon/raitingIco.png"));
        ui->openGroupTabAction->setIcon(QIcon(":/img/whiteActionsIcon/groupIco.png"));
        ui->openSubjTabAction->setIcon(QIcon(":/img/whiteActionsIcon/subjectIco.png"));

        ui->addRowAction->setIcon(QIcon(":/img/whiteActionsIcon/newRecord.png"));
        ui->deleteRowAction->setIcon(QIcon(":/img/whiteActionsIcon/deleteRecord.png"));
        ui->editRowAction->setIcon(QIcon(":/img/whiteActionsIcon/editRecord.png"));

        ui->currentTableReportAction->setIcon(QIcon(":/img/whiteActionsIcon/reportCurrentTable.png"));
        ui->studentsReportAction->setIcon(QIcon(":/img/whiteActionsIcon/reportStudent.png"));
        ui->teachersReportAction->setIcon(QIcon(":/img/whiteActionsIcon/reportTeachers.png"));
        ui->gradesReportAction->setIcon(QIcon(":/img/whiteActionsIcon/reportRaiting.png"));
        ui->groupsReportAction->setIcon(QIcon(":/img/whiteActionsIcon/reportGroup.png"));
        ui->subjectsReportAction->setIcon(QIcon(":/img/whiteActionsIcon/reportItem.png"));
    }
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
    QMessageBox::information(this, "", "ОКРЫТИЕ ДОВИДКИ");
    // КОД РЕАЛИЗАЦИИ ОТКРЫТИЯ ДОВИДКИ
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
