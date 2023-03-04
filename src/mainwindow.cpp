#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QApplication>
#include <QDir>

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

void MainWindow::clearStyleButtonTable()
{
    ui->studentsTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->teachersTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->gradesTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->groupsTableButton->setStyleSheet(defaultButtonTableStyle);

    ui->studentsTableButton->setIcon(QIcon(":/img/pinkMenuicon/studentsIco.png"));
    ui->teachersTableButton->setIcon(QIcon(":/img/pinkMenuicon/teachersIco.png"));
    ui->gradesTableButton->setIcon(QIcon(":/img/pinkMenuicon/raitingIco.png"));
    ui->groupsTableButton->setIcon(QIcon(":/img/pinkMenuicon/groupIco.png"));
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
    ui->reportStudentsButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportTeachersButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportGradesButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportGroupsButton->setStyleSheet(defaultButtonTableStyle);
    ui->settingsButton->setStyleSheet(defaultSettingButtonStyle);
    ui->authorizationButton->setStyleSheet(defaultButtonTableStyle);
    ui->leftMenuFrame->setStyleSheet("background-color: rgb(41,45,48);");
    ui->upMenuFrame->setStyleSheet("border: 0px");
    ui->mainTableFrame->setStyleSheet("background-color: rgb(41,45,48); border: 0px; border-radius: 16px;");
    setStyleSheet("MainWindow{background-color: rgb(29, 31, 32);}border: 0px;");
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
    ui->reportStudentsButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportTeachersButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportGradesButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportGroupsButton->setStyleSheet(defaultButtonTableStyle);
    ui->settingsButton->setStyleSheet(defaultSettingButtonStyle);
    ui->authorizationButton->setStyleSheet(defaultButtonTableStyle);
    ui->leftMenuFrame->setStyleSheet("background-color: rgb(231,224,223);");
    ui->upMenuFrame->setStyleSheet("border: 0px");
    ui->mainTableFrame->setStyleSheet("background-color: rgb(231,224,223); border: 0px; border-radius: 16px;");
    setStyleSheet("MainWindow{background-color: rgb(255, 255, 255);}border: 0px;");
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

