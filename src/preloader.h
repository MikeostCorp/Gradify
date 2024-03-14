#ifndef PRELOADER_H
#define PRELOADER_H

#include <QGraphicsDropShadowEffect>
#include <QWidget>

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

    MainWindow *mainMenu;

    QGraphicsDropShadowEffect *shadowEffect;
    QTimer *timer;

private slots:
    void updateProgressBar();
};

#endif // PRELOADER_H
