#include "preloader.h"
#include "ui_preloader.h"

#include <QTime>
#include <QTimer>
#include <QGraphicsDropShadowEffect>

preloader::preloader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::preloader)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint, true);
    //setWindowFlag(Qt::WindowStaysOnTopHint, true); может как нибудь и включу
    setAttribute(Qt::WA_TranslucentBackground);

    setWindowTitle("Preloader");
    setFocus();
    setFixedSize(this->width(), this->height());
    ui->loadStatusLabel->setText("<strong>LOADING</strong> user interface");

    QPoint pointToCenter = QGuiApplication::primaryScreen()->geometry().center();
    pointToCenter.setX(pointToCenter.x() - (this->width()/2));
    pointToCenter.setY(190);
    move(pointToCenter);

    shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(25);
    shadowEffect->setColor(QColor(0, 0, 0, 60));
    shadowEffect->setOffset(QPointF(0, 0));
    ui->mainFrame->setGraphicsEffect(shadowEffect);

    timer = new QTimer(this);
    timer->start(25); // время загрузки

    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));

    QTimer::singleShot(1000, [this] {
        ui->loadStatusLabel->setText("<strong>LOADING</strong> database connection");
    });

    QTimer::singleShot(1850, [this]
    {
        ui->loadStatusLabel->setText("<strong>LOADING</strong> application styles");
    });

    QFile file(":/styles/other/preloader/preloader.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


preloader::~preloader()
{
    delete ui;
}


void preloader::updateProgressBar()
{

    if (ui->progressBar->value() < 100)
    {
        ui->progressBar->setValue(ui->progressBar->value() + 1);
    }
    else
    {
        mainMenu = new MainWindow;
        mainMenu->show();
        delete(timer);
        this->close();
    }
}
