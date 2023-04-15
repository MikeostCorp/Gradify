#include "qlineeditwithbutton.h"

#include <QToolButton>
#include <QStyle>
#include <QPropertyAnimation>


QLineEditWithButton::QLineEditWithButton(QWidget *parent)
    : QLineEdit{parent}
{
    searchButton = new QToolButton(this);

    searchButton->setIcon(QIcon(":/img/blackMenuIcon/search.png"));
    searchButton->setIconSize(QSize(12,12));
    searchButton->setCursor(Qt::PointingHandCursor);
    searchButton->setMinimumSize(25, this->height() - 5);
    searchButton->move(width()/5 - 10, 2);
    searchButton->setVisible(false);

    connect(searchButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
    connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateCloseButton(const QString)));

    setClearButtonEnabled(true);
}


void QLineEditWithButton::resizeEvent(QResizeEvent *event)
{
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    searchButton->move(rect().right() - frameWidth - searchButton->sizeHint().width() - 10, 2);

    //int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    //searchButton->move(width()/5 - 10 , 2);
    // for x coord: rect().right() - frameWidth - searchButton->sizeHint().width() - 10, 2);

    //if (!hasFocus())
    //{
    //    searchButton->move(width()/2 - 54, 2);
    //}

    //    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    //  searchButton->move(rect().right() - frameWidth - searchButton->sizeHint().width() - 10, 2);

}


void QLineEditWithButton::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    setCurrentTextAligment();
    //searchButton->setCursor(Qt::PointingHandCursor);
    emit haveFocus(true);
}


void QLineEditWithButton::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    setCurrentTextAligment();
    //searchButton->setCursor(Qt::IBeamCursor);
    emit(haveFocus(true));
}


void QLineEditWithButton::updateCloseButton(const QString &text)
{
    // bruh animation
    //QPropertyAnimation *anim = new QPropertyAnimation(searchButton, "pos", this);
    //anim->setDuration(10000);
    //anim->setStartValue(QPoint(0, 0));
    //anim->setEndValue(QPoint(100, 250));
    //anim->start();
    //searchButton->paintEvent();

    // было бы прикольно сюда впихнуть анимацию появления лупы как у тг крестика, но как((

    //setCurrentTextAligment();

    searchButton->setVisible(!text.isEmpty());

}


void QLineEditWithButton::buttonClick()
{
    //if (hasFocus() or !text().isEmpty())
    //{
    //    emit buttonClicked();
    //}

    emit buttonClicked();

}


void QLineEditWithButton::setCurrentTextAligment()
{
    /*if (hasFocus() or !text().isEmpty())
    {
        setAlignment(Qt::AlignLeft);

        setTextMargins(25, defaultTextMargins()->top(),
                       defaultTextMargins().right(), defaultTextMargins().bottom());


        QPropertyAnimation animation(searchButton, "geometry");
        animation.setDuration(5);
        animation.setStartValue(QRect(searchButton->x(),searchButton->y(),searchButton->width(), searchButton->height()));
        animation.setEndValue(QRect(2,2,searchButton->width(), searchButton->height()));
        animation.start();

    }
    else
    {
        setAlignment(Qt::AlignCenter);

        setTextMargins(textMargins().left(), textMargins().top(),
                       textMargins().right(), textMargins().bottom());

        searchButton->move(width()/2 - 54, 2);
    }
     *
     * QPushButton button("Animated Button");
button.show();

QPropertyAnimation animation(&button, "geometry");
animation.setDuration(10000);
animation.setStartValue(QRect(0, 0, 100, 30));
animation.setEndValue(QRect(250, 250, 100, 30));

animation.start();
*/
}


