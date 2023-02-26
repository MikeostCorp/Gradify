#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps); on mac always enabled

    this->setWindowTitle("Gradify");
    //ui->centralwidget->
    //this->setFixedSize(width(),height());\

    //ui->frame->move(0,0);
    ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);

    QPixmap pix(":/img/mainLogo/mainIcox64.png");
    int w = ui->mainLogoImg->width();
    int h = ui->mainLogoImg->height();

    ui->mainLogoImg->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    defaultButtonTableStyle = "QPushButton { border-radius:  6px; background-color:  "
                              "rgb(41,45,48); color:  rgb(255, 255, 255); } "
                              "QPushButton:hover { background-color:  rgb(98, 98, 98); }";

    selectButtonTableStyle = "QPushButton{border-radius:  6px;background-color:  rgb(172, 72, 70);"
                             "color:  rgb(255, 255, 255);} "
                             "QPushButton:hover{background-color:  rgb(172, 72, 70);color:  "
                             "rgb(255, 255, 255);}";
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::ActivationChange) {
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

    // ещё менять иконку нужно
    clearStyleButtonTable();
    ui->firstTableButton->setStyleSheet(selectButtonTableStyle);
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
    this->setWindowTitle("Gradify - (Групи)");
}


void MainWindow::clearStyleButtonTable()
{
    ui->firstTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->secondTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->thirdTableButton->setStyleSheet(defaultButtonTableStyle);
    ui->fourthTableButton->setStyleSheet(defaultButtonTableStyle);

    // менять ещё иконку на стандартную
}
