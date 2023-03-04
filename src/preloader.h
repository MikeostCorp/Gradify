#ifndef PRELOADER_H
#define PRELOADER_H

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>

#include <mainwindow.h>

namespace Ui {
class preloader;
}

class preloader : public QWidget
{
    Q_OBJECT

public:
    explicit preloader(QWidget *parent = nullptr);
    ~preloader();

private:
    Ui::preloader *ui;
    MainWindow *MainMenu;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;

private slots:
    void closeVideoWidget(const QMediaPlayer::MediaStatus status);
};

#endif // PRELOADER_H
