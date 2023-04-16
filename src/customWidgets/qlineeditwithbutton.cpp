#include "qlineeditwithbutton.h"

#include <QStyle>
#include <QToolButton>
#include <QPropertyAnimation>

QLineEditWithButton::QLineEditWithButton(QWidget *parent)
    : QLineEdit{parent}
{
    searchButton = new QToolButton(this);
    clearButton = new QToolButton(this);

    font = new QFontMetrics(placeholderText());


    animationSearchButton = new QPropertyAnimation(searchButton, "geometry");
    animationSearchButton->setDuration(100);

    searchButton->setCursor(Qt::IBeamCursor);
    searchButton->setMinimumSize(25, this->height() - 5);

    clearButton->setVisible(false);
    clearButton->setMinimumSize(25, this->height() - 5);
    clearButton->setCursor(Qt::PointingHandCursor);

    setTextMargins(searchButton->minimumWidth(), 2, clearButton->minimumWidth(), 2);

    connect(searchButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateClearButton(const QString)));
}


void QLineEditWithButton::resizeEvent(QResizeEvent *event)
{
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    clearButton->move(rect().right() - frameWidth - searchButton->sizeHint().width() - 10, 2);

    if (!hasFocus())
    {
        searchButton->move(width()/2 - font->horizontalAdvance(placeholderText()) - 6, 2);
    }
}


void QLineEditWithButton::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    setAlignment(Qt::AlignLeft);
    searchButton->setCursor(Qt::PointingHandCursor);
    playAnimationSearchButton();
    emit haveFocus(true);
}


void QLineEditWithButton::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    playAnimationSearchButton();

    if (text().isEmpty())
    {
        searchButton->setCursor(Qt::IBeamCursor);
        setAlignment(Qt::AlignCenter);
    }

    emit(haveFocus(false));
}


void QLineEditWithButton::updateClearButton(const QString &text)
{
    clearButton->setVisible(!text.isEmpty());
}


void QLineEditWithButton::buttonClick()
{
    emit buttonSearchClick();
}


void QLineEditWithButton::playAnimationSearchButton()
{
    if (hasFocus() or !text().isEmpty())
    {
        animationSearchButton->setStartValue(searchButton->geometry());
        animationSearchButton->setEndValue(QRect(2, 2, searchButton->width(), searchButton->height()));
        animationSearchButton->start();
    }
    else
    {
        animationSearchButton->setStartValue(searchButton->geometry());
        animationSearchButton->setEndValue(QRect(width()/2 - font->horizontalAdvance(placeholderText()) - 6, 2,
                                                 searchButton->width(), searchButton->height()));
        animationSearchButton->start();

    }
}


void QLineEditWithButton::setIconSearchButton(QIcon icon, QSize size)
{
    searchButton->setIcon(icon);
    searchButton->setIconSize(size);
}


void QLineEditWithButton::setIconClearButton(QIcon icon, QSize size)
{
    clearButton->setIcon(icon);
    clearButton->setIconSize(size);
}

