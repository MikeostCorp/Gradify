#include "qlineeditwithbutton.h"

#include <QStyle>
#include <QToolButton>

#include <QMessageBox>

QLineEditWithButton::QLineEditWithButton(QWidget *parent)
    : QLineEdit{parent}
{
    button = new QToolButton(this);
    button->setCursor(Qt::PointingHandCursor);

    setMinimumSize(25, this->height() - 5);
    setTextMargins(2, 2, button->minimumWidth(), 2);

    connect(button, SIGNAL(clicked()), this, SLOT(buttonClick()));
}


void QLineEditWithButton::resizeEvent(QResizeEvent *event)
{
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    button->move(rect().right() - frameWidth - button->sizeHint().width(), 2);
}


void QLineEditWithButton::buttonClick()
{
    emit buttonClicked();
}


void QLineEditWithButton::setIconButton(QIcon icon)
{
    button->setIcon(icon);
}


void QLineEditWithButton::setIconSize(QSize size)
{
    button->setIconSize(size);
}
