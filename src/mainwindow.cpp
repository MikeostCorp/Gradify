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

    this->setWindowTitle("Gradify");
    ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);

    QPixmap pix(":/img/mainLogo/mainIcox512.png"); // need fix quality pic
    int w = ui->mainLogoImg->width();
    int h = ui->mainLogoImg->height();
    ui->mainLogoImg->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    connect(this, &MainWindow::setThemeSettingsUI, openSetting, &appSetting::setThemeSettingUI);

    configRead();
    configInit();

    connect(openSetting, &appSetting::changeThemeApp, this, &MainWindow::setThemeUI);

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
        emit setThemeSettingsUI(1);
    }
    else if (config["theme"] == "black")
    {
        setBlackUI();
        emit setThemeSettingsUI(0);
    }
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
            this->setWindowOpacity(1);
        }
        else
        {
            this->setWindowOpacity(0.97);
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

    this->setWindowTitle("Gradify - (Студенти)");
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

    this->setWindowTitle("Gradify - (Викладачі)");
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
    this->setWindowTitle("Gradify - (Оцінки)");
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
    this->setWindowTitle("Gradify - (Групи)");
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

    this->setWindowTitle("Gradify");
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
    ui->leftMenuFrame->setStyleSheet("background-color: rgb(41,45,48);");
    ui->upMenuFrame->setStyleSheet("border: 0px");
    ui->mainTableFrame->setStyleSheet("background-color: rgb(41,45,48); border: 0px; border-radius: 16px;");
    this->setStyleSheet("MainWindow{background-color: rgb(29, 31, 32);}border: 0px;");
}

void MainWindow::setWhiteUI()
{
    // код для задания белого интерфейса

    this->setWindowTitle("Gradify");
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
    ui->leftMenuFrame->setStyleSheet("background-color: rgb(231,224,223);");
    ui->upMenuFrame->setStyleSheet("border: 0px");
    ui->mainTableFrame->setStyleSheet("background-color: rgb(231,224,223); border: 0px; border-radius: 16px;");
    this->setStyleSheet("MainWindow{background-color: rgb(255, 255, 255);}border: 0px;");
}

void MainWindow::setThemeUI(int style)
{
    if(style == 0)
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
}
