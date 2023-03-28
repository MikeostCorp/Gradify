#include "filterform.h"
#include "ui_filterform.h"

filterForm::filterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::filterForm)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint, true);
    setFixedSize(width(),height());
}

filterForm::~filterForm()
{
    delete ui;
}

void filterForm::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::ActivationChange)
    {
        if (!isActiveWindow())
        {
            close();
        }
    }
}
