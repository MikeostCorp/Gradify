#include "filterform.h"
#include "ui_filterform.h"

#include <QFile>
#include <QGraphicsDropShadowEffect>

filterForm::filterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::filterForm)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint, true);
    setFixedSize(width(), height());
    close();

    //QGraphicsDropShadowEffect *shadow;
    //shadow->setBlurRadius(9.0);
    //shadow->setColor(QColor(99, 255, 255));
    //shadow->setOffset(8.0, 8.0);
            //, 9.0, QColor(99, 255, 255), QPointF(8.0, 8.0));

    //setGraphicsEffect(shadow);
}

filterForm::~filterForm()
{
    delete ui;
}
