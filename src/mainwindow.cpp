#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QApplication>
#include <QDir>
#include <QInputDialog>

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

    openSetting = new appSetting();
    openAuthorization = new authorization();


    //=================================================
    //               Креатим таблицу акаунти
    //=================================================
    //
    //passLogQuery->exec("CREATE TABLE Акаунти ("
    //                               "Логін TEXT,"
    //                               "Пароль TEXT,"
    //                               "Роль TEXT"
    //                               ");");

    //=================================================
    //               Креатим таблицу группы
    //=================================================
    //
    //query->exec("CREATE TABLE Групи ("
    //            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    //            "Назва TEXT,"
    //            "Спеціальність TEXT," // можно условие закинуть на проверку групп
    //            "\"Рік початку навчання\" INTEGER,"
    //            "\"Рік закінчення навчання\" INTEGER,"
    //            "Куратор TEXT,"
    //            "Староста TEXT,"
    //            "CONSTRAINT check_yearStart CHECK(\"Рік початку навчання\" >= 2000 AND \"Рік закінчення навчання\" > \"Рік початку навчання\" AND id >= 0)"
    //            ");");


    //=================================================
    //               Креатим таблицу студенти
    //=================================================
    //
    //query->exec("CREATE TABLE Студенти ("
    //           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    //            "Прізвище TEXT,"
    //            "\"Ім'я\" TEXT,"
    //            "\"По батькові\" TEXT,"
    //            "Стать TEXT,"
    //            "\"Номер телефона\" INTEGER,"
    //            "\"Дата народження\" DATE,"
    //            "\"Адреса проживання\" TEXT,"
    //            "\"Номер паспорту\" INTEGER,"
    //            "Група TEXT,"
    //            "IHH INTEGER"
    //            ");");


    //=================================================
    //               Креатим таблицу Викладачі
    //=================================================
    //
    //query->exec("CREATE TABLE Викладачі ("
    //           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    //            "Прізвище TEXT,"
    //            "\"Ім'я\" TEXT,"
    //            "\"По батькові\" TEXT,"
    //            "\"Номер телефона\" INTEGER,"
    //            "\"Дата народження\" DATE,"
    //            "\"Адреса проживання\" TEXT,"
    //            "\"Категорія\" INTEGER,"
    //            "Спецілізація TEXT"
    //            ");");


    //=================================================
    //               Креатим таблицу Оцінки
    //=================================================
    //
    //query->exec("CREATE TABLE Оцінки ("
    //           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    //            "Предмет TEXT,"
    //            "Отримувач TEXT,"
    //            "Викладач TEXT,"
    //            "Оцінка INTEGER,"
    //            "Дата оцінки DATE"
    //            ");");


    //=================================================
    //               Креатим таблицу Предмет
    //=================================================
    //
    //query->exec("CREATE TABLE Предмет ("
    //           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    //            "Назва TEXT,"
    //            "Тип TEXT,"
    //            "\"Всього годин\" INTEGER,"
    //            "\"Кількість лабораторних годин\" INTEGER,"
    //            "\"Кількість лекційніх годин\" INTEGER,"
    //            "\"Кількість семінарних годин годин\" INTEGER,"
    //            "\"Кількість годин на самостійну роботу\" INTEGER,"
    //            "\"Семестр в якому вивчається\" INTEGER,"
    //            "\"Семестровий контроль\" TEXT," // (іспит, залік)
    //            "CONSTRAINT check_hours CHECK(\"Кількість лабораторних годин\"  > 0 AND \"Кількість лекційніх годин\" > 0 AND \"Кількість семінарних годин годин\" > 0 AND \"Кількість годин на самостійну роботу\" > 0 AND \"Семестр в якому вивчається\" > 0)"
    //            ");");



    //query->exec("DROP TABLE loginPassTable");

    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);
    ui->authorizationButton->setFocus();

    connect(this, &MainWindow::setThemeSettingsUI, openSetting, &appSetting::setThemeSettingUI);
    connect(this, &MainWindow::setThemeSettingsUI, openAuthorization, &authorization::setThemeAuthorUI);

    configRead();
    configInit();

    connect(openSetting, &appSetting::changeThemeApp, this, &MainWindow::setThemeUI);
    connect(openSetting, &appSetting::changeThemeApp, openAuthorization, &authorization::setThemeAuthorUI);
    connect(openAuthorization, &authorization::signalLogin, this, &MainWindow::succesfullyAuthorization);

    // ИЛИ ТУТ УСЛОВИЕ ПРОВЕРКИ АВТОРИЗАЦИИ РАНЕЕ

    setEnabledButtons(false);  // <- для абьюзинга системы ставь true
    setEnabledActions(false);  // <- и это тоже))
}


void MainWindow::configDefault()
{
    config["theme"] = "system";
    configWrite();
}


void MainWindow::configRead()
{
    cfgFile.setFileName(QDir::currentPath() + "/cfg");
    if (!cfgFile.open(QIODevice::ReadOnly))
    {
        configDefault();
        return;
    }

    while (!cfgFile.atEnd())
    {
        QString cfgData = cfgFile.readLine();
        if (cfgData.isEmpty()) continue;
        QStringList list = cfgData.split("=");
        list[1].remove("\n");
        config[list[0]] = list[1];
    }

    cfgFile.close();
}


void MainWindow::configInit()
{
    if (config["theme"] == "white")
    {
        setWhiteUI();
    }
    else if (config["theme"] == "black")
    {
        setBlackUI();
    }
    else if (config["theme"] == "system")
    {
        setSystemUI();
    }

    emit setThemeSettingsUI(config["theme"]);
}


void MainWindow::configWrite()
{
    cfgFile.setFileName(QDir::currentPath() + "/cfg");
    if (!cfgFile.open(QIODevice::WriteOnly))
        return;

    QTextStream stream(&cfgFile);

    for (auto const& cfg : config.keys())
    {
        stream << cfg + "=" + config.value(cfg) + "\n";
    }

    cfgFile.close();
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


void MainWindow::on_studentsTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы студентов
     *
    */
    model->setTable("Студенти");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    clearStyleButtonTable();
    ui->studentsTableButton->setStyleSheet(selectButtonTableStyle);

    if (config["theme"] == "white")
    {
        ui->studentsTableButton->setIcon(QIcon(":/img/whiteMenuIcon/studentsIco.png"));
    }
    else if (config["theme"] == "black")
    {
        ui->studentsTableButton->setIcon(QIcon(":/img/blackMenuIcon/studenstIco.png"));
    }

    setWindowTitle("Gradify - (Студенти)");
}


void MainWindow::on_teachersTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы преподавателей
     *
    */

    model->setTable("Викладачі");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    clearStyleButtonTable();
    ui->teachersTableButton->setStyleSheet(selectButtonTableStyle);

    if (config["theme"] == "white")
    {
        ui->teachersTableButton->setIcon(QIcon(":/img/whiteMenuIcon/teachersIco.png"));
    }
    else if (config["theme"] == "black")
    {
        ui->teachersTableButton->setIcon(QIcon(":/img/blackMenuIcon/teachersIco.png"));
    }

    setWindowTitle("Gradify - (Викладачі)");
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
    model->setTable("Оцінки");
    model->select();
    ui->tableView->setModel(model);


    clearStyleButtonTable();
    ui->gradesTableButton->setStyleSheet(selectButtonTableStyle);

    if (config["theme"] == "white")
    {
        ui->gradesTableButton->setIcon(QIcon(":/img/whiteMenuIcon/raitingIco.png"));
    }
    else if (config["theme"] == "black")
    {
        ui->gradesTableButton->setIcon(QIcon(":/img/blackMenuIcon/raitingIco.png"));
    }

    setWindowTitle("Gradify - (Оцінки)");
}


void MainWindow::on_groupsTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы групп
     *
    */
    model->setTable("Групи");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    clearStyleButtonTable();
    ui->groupsTableButton->setStyleSheet(selectButtonTableStyle);
    if (config["theme"] == "white")
    {
        ui->groupsTableButton->setIcon(QIcon(":/img/whiteMenuIcon/groupIco.png"));
    }
    else if (config["theme"] == "black")
    {
        ui->groupsTableButton->setIcon(QIcon(":/img/blackMenuIcon/groupIco.png"));
    }

    setWindowTitle("Gradify - (Групи)");
}


void MainWindow::on_subjectsTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы предметы
     *
    */
    model->setTable("Предмет");
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    clearStyleButtonTable();
    ui->subjectsTableButton->setStyleSheet(selectButtonTableStyle);
    if (config["theme"] == "white")
    {
        ui->subjectsTableButton->setIcon(QIcon(":/img/whiteMenuIcon/subjectIco.png"));
    }
    else if (config["theme"] == "black")
    {
        ui->subjectsTableButton->setIcon(QIcon(":/img/blackMenuIcon/subjectIco.png"));
    }

    setWindowTitle("Gradify - (Предмети)");
}


void MainWindow::clearSelectTable()
{
    model->setTable("NULL");
    model->select();
    ui->tableView->setModel(model);
}


void MainWindow::setEnabledButtons(bool status)
{
    ui->subjectsReportButton->setEnabled(status);
    ui->gradesReportButton->setEnabled(status);
    ui->groupsReportButton->setEnabled(status);
    ui->teachersReportButton->setEnabled(status);
    ui->studentsReportButton->setEnabled(status);

    ui->gradesTableButton->setEnabled(status);
    ui->studentsTableButton->setEnabled(status);
    ui->subjectsTableButton->setEnabled(status);
    ui->teachersTableButton->setEnabled(status);
    ui->groupsTableButton->setEnabled(status);

    ui->addRowButton->setEnabled(status);
    ui->deleteRowButton->setEnabled(status);
    ui->editRowButton->setEnabled(status);
}

void MainWindow::setEnabledActions(bool status)
{
    ui->addRowAction->setEnabled(status);
    ui->deleteRowAction->setEnabled(status);
    ui->editRowAction->setEnabled(status);

    ui->openGradesTabAction->setEnabled(status);
    ui->openGroupTabAction->setEnabled(status);
    ui->openStudTabAction->setEnabled(status);
    ui->openSubjTabAction->setEnabled(status);
    ui->openTeachTabAction->setEnabled(status);

    ui->gradesReportAction->setEnabled(status);
    ui->groupsReportAction->setEnabled(status);
    ui->studentsReportAction->setEnabled(status);
    ui->teachersReportAction->setEnabled(status);
    ui->subjectsReportAction->setEnabled(status);
}


void MainWindow::clearStyleButtonTable()
{
    ui->studentsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->teachersTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->gradesTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->groupsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->subjectsTableButton->setStyleSheet(defaultButtonTableStyle);

    ui->studentsTableButton->setIcon(QIcon(":/img/pinkMenuIcon/studentsIco.png"));
    ui->teachersTableButton->setIcon(QIcon(":/img/pinkMenuIcon/teachersIco.png"));
    ui->gradesTableButton->setIcon(QIcon(":/img/pinkMenuIcon/raitingIco.png"));
    ui->groupsTableButton->setIcon(QIcon(":/img/pinkMenuIcon/groupIco.png"));
    ui->subjectsTableButton->setIcon(QIcon(":/img/pinkMenuIcon/subjectIco.png"));
}

void MainWindow::setThemeUI(const QString style)
{
    if (style == "black")
    {
        setBlackUI();
        config["theme"] = "black";
        configWrite();
    }
    else if(style == "white")
    {
        setWhiteUI();
        config["theme"] = "white";
        configWrite();
    }
    else
    {
        setSystemUI();
        config["theme"] = "system";
        configWrite();
    }
}


void MainWindow::succesfullyAuthorization(const QString login)
{
    ui->authorizationButton->setText("Привіт, " + login + "!");

    // Может быть стоит перенести в отдельный метод
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::currentPath() + "/../../../../src/dataBase.db");
    //db.setDatabaseName("/Users/andrii/Desktop/Gradify/src/dataBase.db");
    query = new QSqlQuery(db);
    model = new QSqlTableModel(this, db);
    db.open();

    isLogin = true;
    setEnabledButtons(true);
    setEnabledActions(true);

    clearSelectTable();
}


void MainWindow::on_settingsButton_clicked()
{
    openSetting->show();
    openAuthorization->close();
}


void MainWindow::on_authorizationButton_clicked()
{
    if (!isLogin)
    {
        openAuthorization->show();
        openSetting->close();
    }
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "", "Ви дійсно хочете вийти з аккаунта?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            isLogin = false;
            setEnabledButtons(false);
            clearSelectTable();
            clearStyleButtonTable();
            ui->authorizationButton->setText("Авторизація");
        }
    }
}


void MainWindow::on_addRowButton_clicked()
{
    model->insertRow(model->rowCount());
    ui->tableView->scrollToBottom();
    ui->tableView->selectRow(model->rowCount() - 1);
}


void MainWindow::on_deleteRowButton_clicked()
{
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
    // РЕАЛИЗАЦИЯ РЕДАКТИРОВАНИЯ ЗАПИСИ В ОТДЕЛЬНОМ ОКНЕ/ФОРМЕ
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
    setWindowTitle("Gradify");
    clearStyleButtonTable();
    //clearSelectTable();

    styleF.setFileName(":/styles/black/defaultButtonTableStyle.qss");
    styleF.open(QFile::ReadOnly);
    defaultButtonTableStyle = styleF.readAll();
    styleF.close();

    styleF.setFileName(":/styles/black/selectButtonTableStyle.qss");
    styleF.open(QFile::ReadOnly);
    selectButtonTableStyle = styleF.readAll();
    styleF.close();

    styleF.setFileName(":/styles/black/defaultSettingButtonStyle.qss");
    styleF.open(QFile::ReadOnly);
    defaultSettingButtonStyle = styleF.readAll();
    styleF.close();

    styleF.setFileName(":/styles/black/tableView.qss");
    styleF.open(QFile::ReadOnly);
    ui->tableView->setStyleSheet(styleF.readAll());
    styleF.close();

    ui->studentsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->teachersTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->gradesTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->groupsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->subjectsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->teachersReportButton->setStyleSheet(defaultButtonTableStyle);
    ui->gradesReportButton->setStyleSheet(defaultButtonTableStyle);
    ui->groupsReportButton->setStyleSheet(defaultButtonTableStyle);
    ui->subjectsReportButton->setStyleSheet(defaultButtonTableStyle);
    ui->settingsButton->setStyleSheet(defaultSettingButtonStyle);
    ui->authorizationButton->setStyleSheet(defaultButtonTableStyle);
    ui->deleteRowButton->setStyleSheet(defaultButtonTableStyle);
    ui->addRowButton->setStyleSheet(defaultButtonTableStyle);
    ui->editRowButton->setStyleSheet(defaultButtonTableStyle);
    ui->studentsReportButton->setStyleSheet(defaultButtonTableStyle);

    ui->openStudTabAction->setIcon(QIcon(":/img/whiteMenuIcon/studentsIco.png"));
    ui->openTeachTabAction->setIcon(QIcon(":/img/whiteMenuIcon/teachersIco.png"));
    ui->openGradesTabAction->setIcon(QIcon(":/img/whiteMenuIcon/raitingIco.png"));
    ui->openGroupTabAction->setIcon(QIcon(":/img/whiteMenuIcon/groupIco.png"));
    ui->openSubjTabAction->setIcon(QIcon(":/img/whiteMenuIcon/subjectIco.png"));

    ui->controlTableFrame->setStyleSheet("border-radius:  6px;color: white;background-color: rgb(61,65,68);");
    ui->leftMenuFrame->setStyleSheet("background-color: rgb(41,45,48);");
    ui->upMenuFrame->setStyleSheet("border: 0px");
    ui->mainTableFrame->setStyleSheet("color: white;background-color: rgb(41,45,48); border: 0px; border-radius: 16px;");
    setStyleSheet("MainWindow{background-color: rgb(29, 31, 32);}border: 0px;");
}


//====================
//
// set white style
//
//====================

void MainWindow::setWhiteUI()
{
    setWindowTitle("Gradify");
    clearStyleButtonTable();
    //clearSelectTable();

    styleF.setFileName(":/styles/white/defaultButtonTableStyle.qss");
    styleF.open(QFile::ReadOnly);
    defaultButtonTableStyle = styleF.readAll();
    styleF.close();

    styleF.setFileName(":/styles/white/selectButtonTableStyle.qss");
    styleF.open(QFile::ReadOnly);
    selectButtonTableStyle = styleF.readAll();
    styleF.close();

    styleF.setFileName(":/styles/white/defaultSettingButtonStyle.qss");
    styleF.open(QFile::ReadOnly);
    defaultSettingButtonStyle = styleF.readAll();
    styleF.close();

    styleF.setFileName(":/styles/white/tableView.qss");
    styleF.open(QFile::ReadOnly);
    ui->tableView->setStyleSheet(styleF.readAll());
    styleF.close();

    styleF.setFileName(":/styles/white/tableView.qss");
    styleF.open(QFile::ReadOnly);
    ui->tableView->setStyleSheet(styleF.readAll());
    styleF.close();

    ui->studentsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->teachersTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->gradesTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->groupsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->subjectsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->studentsReportButton->setStyleSheet(defaultButtonTableStyle);
    ui->teachersReportButton->setStyleSheet(defaultButtonTableStyle);
    ui->gradesReportButton->setStyleSheet(defaultButtonTableStyle);
    ui->groupsReportButton->setStyleSheet(defaultButtonTableStyle);
    ui->subjectsReportButton->setStyleSheet(defaultButtonTableStyle);
    ui->settingsButton->setStyleSheet(defaultSettingButtonStyle);
    ui->authorizationButton->setStyleSheet(defaultButtonTableStyle);
    ui->deleteRowButton->setStyleSheet(defaultButtonTableStyle);
    ui->addRowButton->setStyleSheet(defaultButtonTableStyle);
    ui->editRowButton->setStyleSheet(defaultButtonTableStyle);

    ui->openStudTabAction->setIcon(QIcon(":/img/blackMenuIcon/studenstIco.png"));
    ui->openTeachTabAction->setIcon(QIcon(":/img/blackMenuIcon/teachersIco.png"));
    ui->openGradesTabAction->setIcon(QIcon(":/img/blackMenuIcon/raitingIco.png"));
    ui->openGroupTabAction->setIcon(QIcon(":/img/blackMenuIcon/groupIco.png"));
    ui->openSubjTabAction->setIcon(QIcon(":/img/blackMenuIcon/subjectIco.png"));


    ui->controlTableFrame->setStyleSheet("border-radius:  6px;color: white;background-color: white;");
    ui->leftMenuFrame->setStyleSheet("background-color: rgb(231,224,223);");
    ui->upMenuFrame->setStyleSheet("border: 0px");
    ui->mainTableFrame->setStyleSheet("color: black;background-color: rgb(231,224,223); border: 0px; border-radius: 16px;");
    setStyleSheet("MainWindow{background-color: rgb(255, 255, 255);}border: 0px;");
}

void MainWindow::setSystemUI()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(), 1 - baseColor.greenF(), 1 - baseColor.blueF());

    if (newBase.name() == "#000000")
    {
        setWhiteUI();
    }
    else
    {
        setBlackUI();
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
