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
    openSetting = new appSetting();
    openAuthorization = new authorization();
    db = QSqlDatabase::addDatabase("QSQLITE");


    // после покупки хостинга фикстить
    db.setDatabaseName("/Users/andrii/Desktop/Gradify/src/dataBase.db ");
    QMessageBox::information(this,"",QDir::currentPath() + "dataBase.db");

    if(!db.open())
    {
        QMessageBox::information(this,"","База даних не відкрилась");
    }


    query = new QSqlQuery(db);

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



    //query->exec("DROP TABLE Викладачі");




    model = new QSqlTableModel(this,db);
    model->setTable("Предмет");
    model->select();

    //QMessageBox::information(this,"",db.tables().at(0));

    ui->tableView->setModel(model);
    //ui->tableView->setShowGrid(false);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();

    setWindowTitle("Gradify");
    ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);

    connect(this, &MainWindow::setThemeSettingsUI, openSetting, &appSetting::setThemeSettingUI);
    connect(this, &MainWindow::setThemeSettingsUI, openAuthorization, &authorization::setThemeAuthorUI);

    configRead();
    configInit();

    connect(openSetting, &appSetting::changeThemeApp, this, &MainWindow::setThemeUI);
    connect(openSetting, &appSetting::changeThemeApp, openAuthorization, &authorization::setThemeAuthorUI);

    ui->authorizationButton->setFocus();
    }

void MainWindow::configDefault()
{
    config["theme"] = "black";
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
    */
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

void MainWindow::on_itemTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы предметы
     *
    */
    clearStyleButtonTable();
    ui->itemTableButton->setStyleSheet(selectButtonTableStyle);
    if (config["theme"] == "white")
    {
        ui->itemTableButton->setIcon(QIcon(":/img/whiteMenuIcon/itemIco.png"));
    }
    else if (config["theme"] == "black")
    {
        ui->itemTableButton->setIcon(QIcon(":/img/blackMenuIcon/itemIco.png"));
    }

    setWindowTitle("Gradify - (Предмети)");
}

void MainWindow::clearStyleButtonTable()
{
    ui->studentsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->teachersTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->gradesTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->groupsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->itemTableButton->setStyleSheet(defaultButtonTableStyle);

    ui->studentsTableButton->setIcon(QIcon(":/img/pinkMenuIcon/studentsIco.png"));
    ui->teachersTableButton->setIcon(QIcon(":/img/pinkMenuIcon/teachersIco.png"));
    ui->gradesTableButton->setIcon(QIcon(":/img/pinkMenuIcon/raitingIco.png"));
    ui->groupsTableButton->setIcon(QIcon(":/img/pinkMenuIcon/groupIco.png"));
    ui->itemTableButton->setIcon(QIcon(":/img/pinkMenuIcon/itemIco.png"));
}

void MainWindow::setBlackUI()
{
    // код для задания черного интерфейса

    setWindowTitle("Gradify");
    clearStyleButtonTable();
    defaultButtonTableStyle = "QPushButton { border-radius:  6px; background-color:  "
                              "rgb(41,45,48); color: rgb(255, 255, 255); } "
                              "QPushButton:hover { background-color:  rgb(98, 98, 98); }";

    selectButtonTableStyle = "QPushButton{border-radius:  6px;background-color:  rgb(172, 72, 70);"
                             "color:  rgb(255, 255, 255);} "
                             "QPushButton:hover{background-color: rgb(172, 72, 70);color:  "
                             "rgb(255, 255, 255);}";

    defaultSettingButtonStyle = "QPushButton { border-radius:  6px; "
                                "background-color:  rgb(41, 45, 48); color:  rgb(255, 255, 255); }";

    ui->studentsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->teachersTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->gradesTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->groupsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->itemTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportStudentsButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportTeachersButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportGradesButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportGroupsButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportItemsButton->setStyleSheet(defaultButtonTableStyle);
    ui->settingsButton->setStyleSheet(defaultSettingButtonStyle);
    ui->authorizationButton->setStyleSheet(defaultButtonTableStyle);
    ui->deleteRowButton->setStyleSheet(defaultButtonTableStyle);
    ui->addRowButton->setStyleSheet(defaultButtonTableStyle);
    ui->editRowButton->setStyleSheet(defaultButtonTableStyle);
    ui->controlTableFrame->setStyleSheet("border-radius:  6px;color: white;background-color: rgb(61,65,68);");
    ui->leftMenuFrame->setStyleSheet("background-color: rgb(41,45,48);");
    ui->upMenuFrame->setStyleSheet("border: 0px");
    ui->mainTableFrame->setStyleSheet("color: white;background-color: rgb(41,45,48); border: 0px; border-radius: 16px;");
    setStyleSheet("MainWindow{background-color: rgb(29, 31, 32);}border: 0px;");
    ui->tableView->setStyleSheet("QHeaderView::section{"
                                 "size: 12px;"
                                 "color: white;"
                                 "background-color: rgb(61,65,68);"
                                 "padding-bottom:5px;"
                                 "padding-top:5px;}"
                                 "QTableView{"
                                 "background-color: rgb(61,65,68);"
                                 "color: white;}"
                                 "QTableView::item {"
                                 "border-radius: 8px;}"
                                 "QTableView::item{"
                                 "color: white;"
                                 "text-align: center;"
                                 "border-style: 1px solid rgb(41,45,48);}"
                                 "QTableView::item:selected{color: white;background-color: rgb(232, 118, 123);}"
                                 "QScrollBar:vertical {\n"
                                 "border: none;\n"
                                 "background: rgb(61,65,68);\n"
                                 "width: 14px;\n"
                                 "margin: 15px 0 15px 0;\n"
                                 "border-radius: 0px;\n}\n"
                                 "QScrollBar::handle:vertical {\n"
                                 "background-color: rgb(132,132,132);\n"
                                 "min-height: 20px;\n"
                                 "border-radius: 7px;\n}\n"
                                 "QScrollBar::handle:vertical:hover { \n"
                                 "background-color: rgb(152,152,152);\n}\n"
                                 "QScrollBar::handle:vertical:pressed {\n"
                                 "background-color: rgb(152,152,152);\n}\n"
                                 "QScrollBar::sub-line:vertical {\n"
                                 "border: none;\n"
                                 "background-color: rgb(91,95,98);\n"
                                 "height: 15px;\n"
                                 "border-top-left-radius: 7px;\n"
                                 "border-top-right-radius: 7px;\n"
                                 "subcontrol-position: top;\n"
                                 "subcontrol-origin: margin;\n}\n"
                                 "QScrollBar::sub-line:vertical:hover {\n"
                                 "background-color: rgb(111,115,118);\n}\n"
                                 "QScrollBar::sub-line:vertical:pressed { \n"
                                 "background-color: rgb(111,115,118);\n}\n"
                                 "QScrollBar::add-line:vertical {\n"
                                 "border: none;\n"
                                 "background-color: rgb(91,95,98);\n"
                                 "height: 15px;\n"
                                 "border-bottom-left-radius: 7px;\n"
                                 "border-bottom-right-radius: 7px;\n"
                                 "subcontrol-position: bottom;\n"
                                 "subcontrol-origin: margin;\n}\n"
                                 "QScrollBar::add-line:vertical:hover {\n"
                                 "background-color: rgb(111,115,118);\n}\n"
                                 "QScrollBar::add-line:vertical:pressed { \n"
                                 "background-color: rgb(111,115,118);\n}\n\n"
                                 "QScrollBar:horizontal {"
                                 "border: none;"
                                 "border-radius: 0px;"
                                 "background: rgb(61,65,68);"
                                 "height: 14px;"
                                 "margin: 0px 15px 0 15px;}"
                                 "QScrollBar::handle:horizontal{"
                                 "background: rgb(132,132,132);"
                                 "min-width: 20px;"
                                 "border-radius: 7px;}"
                                 "QScrollBar::handle:horizontal:hover {"
                                 "background-color: rgb(152,152,152);}"
                                 "QScrollBar::handle:horizontal:pressed {"
                                 "background-color: rgb(152,152,152);}"
                                 "QScrollBar::add-line:horizontal {"
                                 "border: none;"
                                 "background: rgb(91,95,98);"
                                 "width: 15px;"
                                 "border-top-right-radius: 7px;"
                                 "border-bottom-right-radius: 7px;"
                                 "subcontrol-position: right;"
                                 "subcontrol-origin: margin;}"
                                 "QScrollBar::add-line:horizontal:hover {"
                                 "background-color: rgb(111,115,118);}"
                                 "QScrollBar::sub-line:horizontal {"
                                 "border: none;"
                                 "background: rgb(91,95,98);"
                                 "width: 15px;"
                                 "border-top-left-radius: 7px;"
                                 "border-bottom-left-radius: 7px;"
                                 "subcontrol-position: left;"
                                 "subcontrol-origin: margin;}"
                                 "QScrollBar::sub-line:horizontal:hover {"
                                 "background-color: rgb(111,115,118);}"
                                 "QScrollBar::sub-line:horizontal:pressed {"
                                 "background-color: rgb(111,115,118);}");

}

void MainWindow::setWhiteUI()
{
    // код для задания белого интерфейса

    setWindowTitle("Gradify");
    clearStyleButtonTable();
    defaultButtonTableStyle = "QPushButton { border-radius:  6px; background-color:  "
                              "rgb(231,224,223); color: rgb(61, 60, 59); } "
                              "QPushButton:hover { background-color:  rgb(207, 201, 199); }";

    selectButtonTableStyle = "QPushButton{border-radius:  6px;background-color:  rgb(212, 112, 110);"
                             "color:  rgb(61, 60, 59);} "
                             "QPushButton:hover{background-color: rgb(232, 132, 130);color:  "
                             "rgb(61, 60, 59);}";

    defaultSettingButtonStyle = "QPushButton { border-radius:  6px; "
                                "background-color:  rgb(231, 224, 223); color:  rgb(61, 60, 59); }";

    ui->studentsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->teachersTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->gradesTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->groupsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->itemTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportStudentsButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportTeachersButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportGradesButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportGroupsButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportItemsButton->setStyleSheet(defaultButtonTableStyle);
    ui->settingsButton->setStyleSheet(defaultSettingButtonStyle);
    ui->authorizationButton->setStyleSheet(defaultButtonTableStyle);
    ui->deleteRowButton->setStyleSheet(defaultButtonTableStyle);
    ui->addRowButton->setStyleSheet(defaultButtonTableStyle);
    ui->editRowButton->setStyleSheet(defaultButtonTableStyle);
    ui->controlTableFrame->setStyleSheet("border-radius:  6px;color: white;background-color: white;");
    ui->leftMenuFrame->setStyleSheet("background-color: rgb(231,224,223);");
    ui->upMenuFrame->setStyleSheet("border: 0px");
    ui->mainTableFrame->setStyleSheet("color: black;background-color: rgb(231,224,223); border: 0px; border-radius: 16px;");
    setStyleSheet("MainWindow{background-color: rgb(255, 255, 255);}border: 0px;");
    ui->tableView->setStyleSheet("QHeaderView::section{"
                                 "size: 12px;"
                                 "color: black;"
                                 "background-color: white;"
                                 "padding-bottom:5px;"
                                 "padding-top:5px;}"
                                 "QTableView{"
                                 "background-color: white;"
                                 "color: black;}"
                                 "QTableView::item{"
                                 "color: black;"
                                 "text-align: center;"
                                 "border-style: 1px solid rgb(211,204,203);}"
                                 "QTableView::item {"
                                 "border-radius: 8px;}"
                                 "QTableView::item:selected{color: black; background-color: rgb(232, 118, 123);}"
                                 "QScrollBar:vertical {\n"
                                 "border: none;\n"
                                 "background: rgb(245,245,245);\n"
                                 "width: 14px;\n"
                                 "margin: 15px 0 15px 0;\n"
                                 "border-radius: 0px;\n}\n"
                                 "QScrollBar::handle:vertical {\n"
                                 "background-color: rgb(212,212,212);\n"
                                 "min-height: 20px;\n"
                                 "border-radius: 7px;\n}\n"
                                 "QScrollBar::handle:vertical:hover { \n"
                                 "background-color: rgb(202,202,202);\n}\n"
                                 "QScrollBar::handle:vertical:pressed {\n"
                                 "background-color: rgb(202,202,202);\n}\n"
                                 "QScrollBar::sub-line:vertical {\n"
                                 "border: none;\n"
                                 "background-color: rgb(181,185,188);\n"
                                 "height: 15px;\n"
                                 "border-top-left-radius: 7px;\n"
                                 "border-top-right-radius: 7px;\n"
                                 "subcontrol-position: top;\n"
                                 "subcontrol-origin: margin;\n}\n"
                                 "QScrollBar::sub-line:vertical:hover {\n"
                                 "background-color: rgb(161,165,168);\n}\n"
                                 "QScrollBar::sub-line:pressed { \n"
                                 "background-color: rgb(161,165,168);\n}\n"
                                 "QScrollBar::add-line:vertical {\n"
                                 "border: none;\n"
                                 "background-color: rgb(181,185,188);\n"
                                 "height: 15px;\n"
                                 "border-bottom-left-radius: 7px;\n"
                                 "border-bottom-right-radius: 7px;\n"
                                 "subcontrol-position: bottom;\n"
                                 "subcontrol-origin: margin;\n}\n"
                                 "QScrollBar::add-line:vertical:hover {\n"
                                 "background-color: rgb(161,165,168);\n}\n"
                                 "QScrollBar::add-line:vertical:pressed { \n"
                                 "background-color: rgb(161,165,168);\n}\n\n"
                                 "QScrollBar:horizontal {"
                                 "border: none;"
                                 "border-radius: 0px;"
                                 "background: rgb(245,245,245);"
                                 "height: 14px;"
                                 "margin: 0px 15px 0 15px;}"
                                 "QScrollBar::handle:horizontal{"
                                 "background: rgb(212,212,212);"
                                 "min-width: 20px;"
                                 "border-radius: 7px;}"
                                 "QScrollBar::handle:horizontal:hover {"
                                 "background-color: rgb(202,202,202);}"
                                 "QScrollBar::handle:horizontal:pressed {"
                                 "background-color: rgb(202,202,202);}"
                                 "QScrollBar::add-line:horizontal {"
                                 "border: none;"
                                 "background: rgb(181,185,188);"
                                 "width: 15px;"
                                 "border-top-right-radius: 7px;"
                                 "border-bottom-right-radius: 7px;"
                                 "subcontrol-position: right;"
                                 "subcontrol-origin: margin;}"
                                 "QScrollBar::add-line:horizontal:hover {"
                                 "background-color: rgb(161,165,168);}"
                                 "QScrollBar::sub-line:horizontal {"
                                 "border: none;"
                                 "background: rgb(181,185,188);"
                                 "width: 15px;"
                                 "border-top-left-radius: 7px;"
                                 "border-bottom-left-radius: 7px;"
                                 "subcontrol-position: left;"
                                 "subcontrol-origin: margin;}"
                                 "QScrollBar::sub-line:horizontal:hover {"
                                 "background-color: rgb(161,165,168);}"
                                 "QScrollBar::sub-line:horizontal:pressed {"
                                 "background-color: rgb(161,165,168);}");
}

void MainWindow::setThemeUI(const QString style)
{
    if(style == "black")
    {
        setBlackUI();
        config["theme"] = "black";
        configWrite();
    }
    else
    {
        setWhiteUI();
        config["theme"] = "white";
        configWrite();
    }
}

void MainWindow::on_settingsButton_clicked()
{
    openSetting->show();
    openAuthorization->close();
}

void MainWindow::on_authorizationButton_clicked()
{
    openAuthorization->show();
    openSetting->close();
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
                                              tr("Введіть номер ключового поля:"), row+1, 1, model->rowCount(), 1, &ok); // model->rowCount() - максимальное выбранное число (в нашем
                                              // случае максимальный выбор заканчивается на общем количестве записей)
                                              // первая 1 означает текущий выбор за умолчанием
                                              // вторая 1 означает минимальное значение выбор
                                              // третья 1 означает шаг с которым выбирается индекс
    if(ok)
    {
        model->removeRow(inputNum - 1);
        model->select();
    }
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}
