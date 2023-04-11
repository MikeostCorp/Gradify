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
    void resizeEvent(QResizeEvent *);

private:
    QToolButton *searchButton;

private slots:
    void updateCloseButton(const QString &text);

    void buttonClick();

signals:
    void buttonClicked();

};


#endif // LIENEDIT_H
