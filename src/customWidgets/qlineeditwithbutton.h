#ifndef QLINEEDITWITHBUTTON_H
#define QLINEEDITWITHBUTTON_H

#include <QLineEdit>
#include <QPropertyAnimation>

class QToolButton;

class QLineEditWithButton : public QLineEdit
{
    Q_OBJECT
public:
    explicit QLineEditWithButton(QWidget *parent = nullptr);

protected:
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QToolButton *searchButton;
    QToolButton *clearButton;

    QPropertyAnimation *animationSearchButton;
    //QPropertyAnimation *animationLineEdit; ДОДЕЛАТЬ ДЛЯ ПЛАВНОГО СМЕЩЕНИЯ КУРСОРА


private slots:
    void updateClearButton(const QString &text);
    void buttonClick();
    void playAnimationSearchButton();

public slots:
    void setIconSearchButton(QIcon icon, QSize size);
    void setIconClearButton(QIcon icon, QSize size);

signals:
    void buttonSearchClick();
    void haveFocus(bool);
};


#endif // LIENEDIT_H
