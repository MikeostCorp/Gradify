#ifndef QLINEEDITWITHBUTTON_H
#define QLINEEDITWITHBUTTON_H

#include <QLineEdit>

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

private slots:
    void updateCloseButton(const QString &text);
    void buttonClick();
    void setCurrentTextAligment();

signals:
    void buttonClicked();
    void haveFocus(bool);
};


#endif // LIENEDIT_H
