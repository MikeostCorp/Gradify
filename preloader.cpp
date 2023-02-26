#include "preloader.h"
#include "ui_preloader.h"

#include <QPainterPath>

preloader::preloader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::preloader)
{
    ui->setupUi(this);

    //this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint, true);
    this->setWindowFlag(Qt::FramelessWindowHint, true);
    this->setFixedSize(400,400);
    this->setWindowTitle("Preloader");

    QPainterPath painPath;
    painPath.addRoundedRect(rect(), 18, 18, Qt::AbsoluteSize);
    this->setMask(painPath.toFillPolygon().toPolygon());

    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    MainMenu = new MainWindow;

    player->setSource(QUrl("qrc:/img/preloader.mp4"));
    videoWidget->setObjectName("videoWidget");
    videoWidget->setFixedSize(400,400);
    videoWidget->setWindowFlags(Qt::FramelessWindowHint);
    player->setVideoOutput(videoWidget);

    videoWidget->setFocus();
    videoWidget->show();
    player->play();

    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(closeVideoWidget(QMediaPlayer::MediaStatus)));
}

preloader::~preloader()
{
    delete ui;
}

void preloader::closeVideoWidget(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        MainMenu->show();
        this->close();
    }
}
