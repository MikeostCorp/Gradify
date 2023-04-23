#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
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

    // new windows
    settingWindow = new appSetting();
    authorizationWindow = new authorization();
    filterWindow = new filterForm(this);
    queryWindow = new queryForm(this);
    aboutAppAction = new aboutApp();

    gradeEditForm = new editGrade();
    groupEditForm = new editGroup();
    studentEditForm = new editStudent();
    subjectEditForm = new editSubject();
    teacherEditForm = new editTeacher();

    filterWindow->setGraphicsEffect(paintDropShadowEffect());
    queryWindow->setGraphicsEffect(paintDropShadowEffect());

    currentSelectTable = -1;
    setEnabledButtons(false);
    setEnabledActions(false);
    setEnabledEditButton(false);

    // tableview settings
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);

    ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);
    ui->authorizationButton->setFocus();

    connect(this, &MainWindow::setThemeSettingsUI, settingWindow, &appSetting::setThemeSettingUI);
    connect(this, &MainWindow::setThemeSettingsUI, authorizationWindow, &authorization::setThemeAuthorUI);
    connect(this, &MainWindow::setThemeSettingsUI, aboutAppAction, &aboutApp::setThemeSettingUI);
    connect(this, &MainWindow::setTableForFilter, filterWindow, &filterForm::setListTable);

    configInit();

    connect(settingWindow, &appSetting::logoutSignal, this, &MainWindow::userLogout);

    connect(settingWindow, &appSetting::changeThemeApp, this, &MainWindow::setThemeUI);
    connect(settingWindow, &appSetting::changeThemeApp, authorizationWindow, &authorization::setThemeAuthorUI);
    connect(authorizationWindow, &authorization::signalLogin, this, &MainWindow::succesfullyAuthorization);
    connect(settingWindow, &appSetting::changeThemeApp, aboutAppAction, &aboutApp::setThemeSettingUI);

    connect(filterWindow, &filterForm::sendFilter, this, &MainWindow::setFilterForTable);
    connect(filterWindow, &filterForm::clearFilter, this, &MainWindow::clearFilterForTable);

    // close popup windows on click tableView (need fix empty space)
    connect(ui->tableView->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::closeAllPopUpWindow);
    connect(ui->tableView->verticalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::closeAllPopUpWindow);
    connect(ui->tableView, &QAbstractItemView::clicked, this, &MainWindow::closeAllPopUpWindow);
    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::closeAllPopUpWindow);

    // close popup windows on click any buttons
    for (QPushButton* button : findChildren<QPushButton*>())
    {
        // Добавлять в условие название кнопок форм привязаных к главном у окну
        if (button->objectName() != "filterButton" and button->objectName() != "queryButton"
            and button->objectName() != "filterPushButton" and button->objectName() != "succesStudentPushButton"
            and button->objectName() != "avgScorePushButton" and button->objectName() != "clearFilterPushButton"
            and button->objectName() != "mySQLPushButton" and button->objectName() != "nameFreeButtonМенять!")
        {
            connect(button, &QPushButton::clicked, this, &MainWindow::closeAllPopUpWindow);
        }
    }

    // close popup windows on click menubar
    connect(ui->menuBar, &QMenuBar::triggered, this, &MainWindow::closeAllPopUpWindow);
    connect(ui->searchLineEdit, &QSearchBar::haveFocus, this, &MainWindow::closeAllPopUpWindow);
    connect(ui->searchLineEdit, &QSearchBar::buttonSearchClick, this, &MainWindow::goSearch);
    connect(ui->searchLineEdit, &QLineEdit::returnPressed, this, &MainWindow::goSearch);

    //succesfullyAuthorization("ララ･サタ"); // <- абьюз для ровных девелоперов

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
        succesfullyAuthorization(settingsConfig.value("userlogin").toString());
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

    ui->studentsTableButton->setStyleSheet(selectButtonTableStyle);

    setEnabledEditButton(true);

    if (theme == "white")
    {
        ui->studentsTableButton->setIcon(QIcon(":/img/whiteMenuIcon/studentsIco.png"));

    }
    else if (theme == "black")
    {
        ui->studentsTableButton->setIcon(QIcon(":/img/blackMenuIcon/studenstIco.png"));
    }

    emit setTableForFilter("Студенти", getColumnsAndDatatypes("Студенти"));
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

    ui->teachersTableButton->setStyleSheet(selectButtonTableStyle);


    setEnabledEditButton(true);

    if (theme == "white")
    {
        ui->teachersTableButton->setIcon(QIcon(":/img/whiteMenuIcon/teachersIco.png"));
    }
    else if (theme == "black")
    {
        ui->teachersTableButton->setIcon(QIcon(":/img/blackMenuIcon/teachersIco.png"));
    }

    emit setTableForFilter("Викладачі", getColumnsAndDatatypes("Викладачі"));
}


void MainWindow::on_gradesTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы оценок
     *
     *    ui->tableView->resizeColumnsToContents(); не юзаем ибо баг
     *                                              с длиной колонк (последняя колонка не до
     *                                              конца растянута)
    */
    setWindowTitle("Gradify - (Оцінки)");
    model->setTable("Оцінки");
    model->select();
    currentSelectTable = 2;

    ui->tableView->setModel(model);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);

    clearStyleButtonTable();

    ui->gradesTableButton->setStyleSheet(selectButtonTableStyle);

    setEnabledEditButton(true);

    if (theme == "white")
    {
        ui->gradesTableButton->setIcon(QIcon(":/img/whiteMenuIcon/raitingIco.png"));
    }
    else if (theme == "black")
    {
        ui->gradesTableButton->setIcon(QIcon(":/img/blackMenuIcon/raitingIco.png"));
    }

    emit setTableForFilter("Оцінки", getColumnsAndDatatypes("Оцінки"));
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

    ui->groupsTableButton->setStyleSheet(selectButtonTableStyle);

    setEnabledEditButton(true);

    if (theme == "white")
    {
        ui->groupsTableButton->setIcon(QIcon(":/img/whiteMenuIcon/groupIco.png"));
    }
    else if (theme == "black")
    {
        ui->groupsTableButton->setIcon(QIcon(":/img/blackMenuIcon/groupIco.png"));
    }

    emit setTableForFilter("Групи", getColumnsAndDatatypes("Групи"));
}


void MainWindow::on_subjectsTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы предметы
     *
    */
    setWindowTitle("Gradify - (Предмети)");
    model->setTable("Предмет");
    model->select();
    currentSelectTable = 4;

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);

    clearStyleButtonTable();

    ui->subjectsTableButton->setStyleSheet(selectButtonTableStyle);

    setEnabledEditButton(true);

    if (theme == "white")
    {
        ui->subjectsTableButton->setIcon(QIcon(":/img/whiteMenuIcon/subjectIco.png"));
    }
    else if (theme == "black")
    {
        ui->subjectsTableButton->setIcon(QIcon(":/img/blackMenuIcon/subjectIco.png"));
    }

    emit setTableForFilter("Предмет", getColumnsAndDatatypes("Предмет"));
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


void MainWindow::setEnabledButtons(bool status)
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


void MainWindow::setEnabledActions(bool status)
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


void MainWindow::setEnabledEditButton(bool status)
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


void MainWindow::setThemeUI(const QString style)
{
    QString theme;
    if (style == "black")
    {
        setBlackUI();
        theme = "black";
    }
    else if (style == "white")
    {
        setWhiteUI();
        theme = "white";
    }
    else
    {
        setSystemUI();
        theme = "system";
    }

    configWrite("theme", theme);
}


void MainWindow::succesfullyAuthorization(const QString login)
{

    QSettings settingsConfig(QDir::currentPath() + "/gradify.conf", QSettings::IniFormat);

    // Может быть стоит перенести в отдельный метод
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

    isLogin = true;
    setEnabledButtons(true);
    setEnabledActions(true);

    clearSelectTable();

    ui->authorizationButton->setText(" Привіт, " + login + "!");
    ui->authorizationButton->setStyleSheet(selectButtonAuthStyle);
}


void MainWindow::setFilterForTable(const QString filterQuery, const QString currentColumnFilter)
{
    queryModel->setQuery(filterQuery);
    ui->tableView->setModel(queryModel);

    for(int i = 0; i < ui->tableView->model()->columnCount(); i++)
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
}

void MainWindow::userLogout()
{
    isLogin = false;
    setEnabledButtons(false);
    setEnabledEditButton(false);

    clearSelectTable();
    clearStyleButtonTable();
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
    model->insertRow(model->rowCount());
    ui->tableView->scrollToBottom();
    ui->tableView->selectRow(model->rowCount() - 1);
    ui->searchLineEdit->clearFocus();
}


void MainWindow::on_deleteRowButton_clicked()
{
    ui->searchLineEdit->clearFocus();

    bool ok;
    int inputNum = QInputDialog::getInt(this, tr("Видалення запису"),
                                              tr("Введіть номер ключового поля:"), row + 1, 1, model->rowCount(), 1, &ok); // model->rowCount() - максимальное выбранное число (в нашем
                                              // случае максимальный выбор заканчивается на общем количестве записей)
                                              // первая 1 означает текущий выбор за умолчанием
                                              // вторая 1 означает минимальное значение выбор
                                              // третья 1 означает шаг с которым выбирается индекс
    if (ok)
    {
        model->removeRow(inputNum - 1);
        model->select();                      // Для мгновенного обновления таблицы
    }
}


void MainWindow::on_editRowButton_clicked()
{
    ui->searchLineEdit->clearFocus();
    // добавить выбор кого редактировать ещё обязательно!! (по айди можно)

    switch (currentSelectTable)
    {
    case 0:
        studentEditForm->show();
        break;
    case 1:
        teacherEditForm->show();
        break;
    case 2:
        gradeEditForm->show();
        break;
    case 3:
        groupEditForm->show();
        break;
    case 4:
        subjectEditForm->show();
        break;
    }


    // РЕАЛИЗАЦИЯ РЕДАКТИРОВАНИЯ ЗАПИСИ В ОТДЕЛЬНОМ ОКНЕ/ФОРМЕ
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
        QString searchString = "SELECT `" + model->tableName() + "`.*" +
                "FROM `" + model->tableName() + "`" +
                "WHERE ";

        for (int i = 0; i < ui->tableView->model()->columnCount(); i++)
        {
            searchString += "`" + ui->tableView->model()->headerData(i, Qt::Horizontal).toString() + "` LIKE" +
                    "'%" + ui->searchLineEdit->text() + "%'";

            if (i != ui->tableView->model()->columnCount() - 1)
            {
                searchString += " OR ";
            }
        }

        queryModel->setQuery(searchString);
        ui->tableView->setModel(queryModel);
    }
    else
    {
        model->select();
        ui->tableView->setModel(model);
    }

    //QMessageBox::information(this,"", "надо искать!" + ui->searchLineEdit->text() +
    //                         "\n" + model->tableName());
}


void MainWindow::clearFilterForTable()
{
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


QMap<QString, QString> MainWindow::getColumnsAndDatatypes(const QString &tableName)
{
    QMap<QString,QString> headerListMap;

    if (!tableName.isEmpty())
    {
        QSqlQueryModel *queryModel = new QSqlQueryModel(this);
        QTableView *tableView = new QTableView(this);
        queryModel->setQuery("SELECT COLUMN_NAME, DATA_TYPE "
                             "FROM INFORMATION_SCHEMA.COLUMNS "
                             "WHERE table_schema = 'Gradify' "
                             "AND table_name = '" + tableName + "'");
        tableView->setModel(queryModel);

        for (int row = 1; row < tableView->model()->rowCount(); ++row)
        {
            headerListMap.insert(tableView->model()->index(row, 0).data().toString(),
                                 tableView->model()->index(row, 1).data().toString());
        }
    }

    return headerListMap;
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
        setWhiteUI();
        theme = "white";
    }
    else
    {
        setBlackUI();
        theme = "black";
    }
}


void MainWindow::setCurrentIconAction()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(), 1 - baseColor.greenF(), 1 - baseColor.blueF());

    if (newBase.name() == "#000000")
    {
        ui->openStudTabAction->setIcon(QIcon(":/img/blackActionsIcon/studenstIco.png"));
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
    QMessageBox::information(this,"","ОКРЫТИЕ ДОВИДКИ");
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
    aboutAppAction->show();
}
