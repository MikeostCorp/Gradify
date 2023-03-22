#include "preloader.h"
#include "ui_preloader.h"

#include <QStyle>
#include <QPainterPath>
#include <QPainter>

preloader::preloader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::preloader)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint, true);
    setFixedSize(414,233);
    setWindowTitle("Preloader");

    QPoint pointToCenter = QGuiApplication::primaryScreen()->geometry().center();
    pointToCenter.setX(pointToCenter.x() - (this->width()/2));
    pointToCenter.setY(190);
    move(pointToCenter);

    QPainterPath paintPath;
    paintPath.addRoundedRect(rect(), 18, 18, Qt::AbsoluteSize);
    setMask(paintPath.toFillPolygon().toPolygon());

    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    MainMenu = new MainWindow;

    player->setSource(QUrl("qrc:/img/preloader.mp4"));
    videoWidget->setObjectName("videoWidget");
    videoWidget->setFixedSize(width(),height());
    videoWidget->setWindowFlags(Qt::FramelessWindowHint);
    player->setVideoOutput(videoWidget);

    videoWidget->setStyleSheet("border-radius: 16px;");

    videoWidget->setFocus();
    videoWidget->show();
    player->play();

    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(closeVideoWidget(QMediaPlayer::MediaStatus)));
}


preloader::~preloader()
{
    delete ui;
}


void preloader::closeVideoWidget(const QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        MainMenu->show();
        close();
    }
}
