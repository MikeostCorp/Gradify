#include "preloader.h"
#include "ui_preloader.h"

#include <QPainterPath>
#include <QPainter>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>

preloader::preloader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::preloader)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint, true);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(414,233);
    setWindowTitle("Preloader");

    QPoint pointToCenter = QGuiApplication::primaryScreen()->geometry().center();
    pointToCenter.setX(pointToCenter.x() - (this->width()/2));
    pointToCenter.setY(190);
    move(pointToCenter);


    //QVBoxLayout *lay = new QVBoxLayout(videoWidget);
    //lay->addWidget(videoWidget);
    //lay->setContentsMargins(10, 10, 10, 10);

    //QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    //shadow->setBlurRadius(9.0);
    //shadow->setColor(QColor(99, 255, 255));
    //shadow->setOffset(QPointF(8.0, 8.0));
    //this->setGraphicsEffect(shadow);



    //painter = QtGui.QPainter(self)
    //        painter.begin(self)
    //        painter.setBrush(QColor(255, 255, 255))
    //        painter.setPen(Qt.NoPen)
    //        painter.drawRoundedRect(self.rect(), 10.0, 10.0)
    //        painter.end()

    //QPainter painter(this);
    //painter.begin(this);
    //painter.setBrush(QColor(255, 255, 255));
    //painter.setPen(Qt::NoPen);
    //painter.drawRoundedRect(this->rect(), 10.0, 10.0);
    //painter.end();
    //QPainterPath paintPath;
    //paintPath.addRoundedRect(rect(), 18, 18, Qt::AbsoluteSize);
    //setMask(paintPath.toFillPolygon().toPolygon());

    //lay = QtWidgets.QVBoxLayout(self)
    //lay.addWidget(window)
    //lay.setContentsMargins(10, 10, 10, 10)

    //QVBoxLayout *videoLay = new QVBoxLayout(this);
    //videoLay->addWidget(videoWidget);
    //videoLay->setContentsMargins(10, 10, 10, 10);

    //painter = QtGui.QPainter(self)
    //painter.setRenderHint(QtGui.QPainter.Antialiasing)
    //painter.setBrush(QtGui.QColor(195, 195, 255))
    //painter.setPen(QtCore.Qt.NoPen)
    //painter.drawRoundedRect(self.rect(), 10.0, 10.0)

    //QPainter *painter = new QPainter(this);
    //painter->setRenderHint(QPainter::Antialiasing);
    //painter->setBrush(QColor(195, 195 , 255));
    //painter->setPen(Qt::NoPen);
    //painter->drawRoundedRect(this->rect(), 10.0, 10.0);



    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    MainMenu = new MainWindow;

    player->setSource(QUrl("qrc:/img/preloader.mp4"));
    videoWidget->setObjectName("videoWidget");
    videoWidget->setFixedSize(width(),height());
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


void preloader::closeVideoWidget(const QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        MainMenu->show();
        close();
    }
}
