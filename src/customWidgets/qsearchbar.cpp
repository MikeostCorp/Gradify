#include "qsearchbar.h"

#include <QPropertyAnimation>
#include <QStyle>
#include <QToolButton>

QSearchBar::QSearchBar(QWidget *parent)
    : QLineEdit{parent}
{
    searchButton = new QToolButton(this);
    clearButton = new QToolButton(this);

    font = new QFontMetrics(placeholderText());

    animationSearchButton = new QPropertyAnimation(searchButton, "geometry");

    searchButton->setCursor(Qt::IBeamCursor);
    searchButton->setMinimumSize(25, this->height() - 5);

    clearButton->setVisible(false);
    clearButton->setMinimumSize(25, this->height() - 5);
    clearButton->setCursor(Qt::PointingHandCursor);

    setTextMargins(searchButton->minimumWidth(), 2, clearButton->minimumWidth(), 2);

    connect(searchButton, &QAbstractButton::clicked, this, &QSearchBar::search);
    connect(clearButton, &QAbstractButton::clicked, this, &QSearchBar::clearText);
    connect(this, &QSearchBar::textChanged, this, &QSearchBar::updateClearButton);
}

void QSearchBar::resizeEvent(QResizeEvent *event)
{
    QLineEdit::resizeEvent(event);
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    clearButton->move(rect().right() - frameWidth - searchButton->sizeHint().width() - 10, 2);

    if (not hasFocus()) {
        searchButton->move(width() / 2 - font->horizontalAdvance(placeholderText()) - 6, 2);
    }
}

void QSearchBar::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    setAlignment(Qt::AlignLeft);
    searchButton->setCursor(Qt::PointingHandCursor);
    playAnimationSearchButton();
    emit haveFocus();
}

void QSearchBar::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    playAnimationSearchButton();

    if (text().isEmpty()) {
        searchButton->setCursor(Qt::IBeamCursor);
        setAlignment(Qt::AlignCenter);
    }

    emit haveFocus();
}

void QSearchBar::updateClearButton(const QString &text)
{
    clearButton->setVisible(not text.isEmpty());
    search();
}

void QSearchBar::search()
{
    emit searchInfo();
}

void QSearchBar::clearText()
{
    clear();
    emit clearInfo();
}

void QSearchBar::playAnimationSearchButton()
{
    if (hasFocus() or not text().isEmpty()) {
        animationSearchButton->setDuration(this->width() / 1.85);
        animationSearchButton->setStartValue(searchButton->geometry());
        animationSearchButton->setEndValue(
            QRect(2, 2, searchButton->width(), searchButton->height()));
        animationSearchButton->start();
    } else {
        animationSearchButton->setDuration(this->width() / 1.85);
        animationSearchButton->setStartValue(searchButton->geometry());
        animationSearchButton->setEndValue(
            QRect(width() / 2 - font->horizontalAdvance(placeholderText()) - 6,
                  2,
                  searchButton->width(),
                  searchButton->height()));
        animationSearchButton->start();
    }
}

void QSearchBar::setIconSearchButton(QIcon icon, QSize size)
{
    searchButton->setIcon(icon);
    searchButton->setIconSize(size);
}

void QSearchBar::setIconClearButton(QIcon icon, QSize size)
{
    clearButton->setIcon(icon);
    clearButton->setIconSize(size);
}
