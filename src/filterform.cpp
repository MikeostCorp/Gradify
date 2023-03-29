#include "filterform.h"
#include "ui_filterform.h"
#include <QMessageBox>

filterForm::filterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::filterForm)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint, true);
    setFixedSize(width(),height());
    close();
}

filterForm::~filterForm()
{
    delete ui;
}

void filterForm::changeEvent(QEvent *event)
{
    //QWidget::changeEvent(event);
    if(event->type() == QEvent::Enter)
    {
        QMessageBox::information(this, "Enter", "Enter");
        show();
    }
    else if (event->type() == QEvent::Leave)
    {
        QMessageBox::information(this, "leave", "leave");
        close();
    }
}

void filterForm::leaveEvent(QEvent *event)
{
    close();
}
