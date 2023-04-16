#ifndef QSEARCHBAR_H
#define QSEARCHBAR_H

#include <QLineEdit>
#include <QPropertyAnimation>

class QSearchBar : public QLineEdit
{
    Q_OBJECT
public:
    explicit QSearchBar(QWidget *parent = nullptr);

protected:
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QToolButton *searchButton;
    QToolButton *clearButton;

    QPropertyAnimation *animationSearchButton;
    //QPropertyAnimation *animationLineEdit; ДОДЕЛАТЬ ДЛЯ ПЛАВНОГО СМЕЩЕНИЯ КУРСОРА

    QFontMetrics *font;

private slots:
    void updateClearButton(const QString &text);
    void playAnimationSearchButton();
    void buttonClick();

public slots:
    void setIconSearchButton(QIcon icon, QSize size);
    void setIconClearButton(QIcon icon, QSize size);

signals:
    void buttonSearchClick();
    void haveFocus(bool);
};

#endif // QSEARCHBAR_H
