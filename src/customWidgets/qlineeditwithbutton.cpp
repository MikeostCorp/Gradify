#include "qlineeditwithbutton.h"

#include <QToolButton>
#include <QStyle>
#include <QMessageBox>

QLineEditWithButton::QLineEditWithButton(QWidget *parent)
    : QLineEdit{parent}
{
    searchButton = new QToolButton(this);

    searchButton->setCursor(Qt::PointingHandCursor);
    searchButton->setIcon(QIcon(":/img/blackMenuIcon/search.png"));
    searchButton->setIconSize(QSize(12,12));
    searchButton->setMinimumSize(25, this->height() - 5);
    searchButton->hide();

    connect(searchButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
    connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateCloseButton(const QString)));
}


void QLineEditWithButton::resizeEvent(QResizeEvent *)
{
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    searchButton->move(rect().right() - frameWidth - searchButton->sizeHint().width() - 10, 2);
}


void QLineEditWithButton::updateCloseButton(const QString &text)
{
    // было бы прикольно сюда впихнуть анимацию появления лупы как у тг крестика, но как((
    searchButton->setVisible(!text.isEmpty());
}


void QLineEditWithButton::buttonClick()
{
    emit buttonClicked();
}
