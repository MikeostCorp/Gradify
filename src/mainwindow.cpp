#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    openSetting = new appSetting();

    //QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps); on mac always enabled
    this->setWindowTitle("Gradify");
    ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);

    QPixmap pix(":/img/mainLogo/mainIcox512.png"); // need fix quality pic
    int w = ui->mainLogoImg->width();
    int h = ui->mainLogoImg->height();
    ui->mainLogoImg->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));



    /// Код в случае если нужен будет конфиг файл, но моя идея сдлеать его получила
    /// не удачу ибо он не может записывать в файл, ищет его не в той директории :(
    /*cfgFile.setFileName(":/config/cfg");
    if (!cfgFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Помилка","Файл налаштувань не відкрився!");
    }
    else
    {
        cfgData = cfgFile.readLine();
        if (cfgData[cfgData.size()-2] == '0')
        {
            appThemeStyle = 0;
        }
        else
        {
            appThemeStyle = 1;
        }
    }*/


    connect(openSetting, &appSetting::changeThemeApp, this, &MainWindow::setThemeUI);

    setBlackUI();
}


MainWindow::~MainWindow()
{
    delete ui;
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


void MainWindow::on_firstTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы студентов
     *
    */

    clearStyleButtonTable();
    ui->firstTableButton->setStyleSheet(selectButtonTableStyle);

    if (appThemeStyle == 0)
    {
        ui->firstTableButton->setIcon(QIcon(":/img/whiteMenuIcon/studentsIco.png"));
    }
    else
    {
        ui->firstTableButton->setIcon(QIcon(":/img/blackMenuIcon/studenstIco.png"));
    }

    this->setWindowTitle("Gradify - (Студенти)");
}


void MainWindow::on_secondTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы викладачив
     *
    */
    clearStyleButtonTable();
    ui->secondTableButton->setStyleSheet(selectButtonTableStyle);

    if (appThemeStyle == 0)
    {
        ui->secondTableButton->setIcon(QIcon(":/img/whiteMenuIcon/teachersIco.png"));
    }
    else
    {
        ui->secondTableButton->setIcon(QIcon(":/img/blackMenuIcon/teachersIco.png"));
    }

    this->setWindowTitle("Gradify - (Викладачі)");
}


void MainWindow::on_thirdTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы оценок
     *
    */
    clearStyleButtonTable();
    ui->thirdTableButton->setStyleSheet(selectButtonTableStyle);

    if (appThemeStyle == 0)
    {
        ui->thirdTableButton->setIcon(QIcon(":/img/whiteMenuIcon/raitingIco.png"));
    }
    else
    {
        ui->thirdTableButton->setIcon(QIcon(":/img/blackMenuIcon/raitingIco.png"));
    }
    this->setWindowTitle("Gradify - (Оцінки)");
}


void MainWindow::on_fourthTableButton_clicked()
{
    /*
     *
     * Код реализации открытия таблицы груп
     *
    */
    clearStyleButtonTable();
    ui->fourthTableButton->setStyleSheet(selectButtonTableStyle);
    if (appThemeStyle == 0)
    {
        ui->fourthTableButton->setIcon(QIcon(":/img/whiteMenuIcon/groupIco.png"));
    }
    else
    {
        ui->fourthTableButton->setIcon(QIcon(":/img/blackMenuIcon/groupIco.png"));
    }
    this->setWindowTitle("Gradify - (Групи)");
}


void MainWindow::clearStyleButtonTable()
{
    ui->firstTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->secondTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->thirdTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->fourthTableButton->setStyleSheet(defaultButtonTableStyle);

    ui->firstTableButton->setIcon(QIcon(":/img/pinkMenuicon/studentsIco.png"));
    ui->secondTableButton->setIcon(QIcon(":/img/pinkMenuicon/teachersIco.png"));
    ui->thirdTableButton->setIcon(QIcon(":/img/pinkMenuicon/raitingIco.png"));
    ui->fourthTableButton->setIcon(QIcon(":/img/pinkMenuicon/groupIco.png"));
}

void MainWindow::setBlackUI()
{
    // код для задания черного интерфейса
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

    ui->firstTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->secondTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->thirdTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->fourthTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportFirstButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportSecondButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportThirdButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportFourthButton->setStyleSheet(defaultButtonTableStyle);
    ui->settingButton->setStyleSheet(defaultSettingButtonStyle);
    ui->leftMenuFrame->setStyleSheet("background-color: rgb(41,45,48);");
    ui->upMenuFrame->setStyleSheet("border: 0px");
    ui->mainTableFrame->setStyleSheet("background-color: rgb(41,45,48); border: 0px; border-radius: 16px;");
    this->setStyleSheet("MainWindow{background-color: rgb(29, 31, 32);}border: 0px;");


}


void MainWindow::setWhiteUI()
{
    // код для задания белого интерфейса
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

    ui->firstTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->secondTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->thirdTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->fourthTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportFirstButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportSecondButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportThirdButton->setStyleSheet(defaultButtonTableStyle);
    ui->reportFourthButton->setStyleSheet(defaultButtonTableStyle);
    ui->settingButton->setStyleSheet(defaultSettingButtonStyle);
    ui->leftMenuFrame->setStyleSheet("background-color: rgb(231,224,223);");
    ui->upMenuFrame->setStyleSheet("border: 0px");
    ui->mainTableFrame->setStyleSheet("background-color: rgb(231,224,223); border: 0px; border-radius: 16px;");
    this->setStyleSheet("MainWindow{background-color: rgb(255, 255, 255);}border: 0px;");
}

void MainWindow::setThemeUI(int style)
{
    appThemeStyle = style;

    if(appThemeStyle == 0)
    {
        setBlackUI();
    }
    else
    {
        setWhiteUI();
    }
}


void MainWindow::on_settingButton_clicked()
{
    openSetting->show();
}
