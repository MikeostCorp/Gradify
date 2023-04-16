#ifndef QLINEEDITWITHBUTTON_H
#define QLINEEDITWITHBUTTON_H

#include <QLineEdit>

class QLineEditWithButton : public QLineEdit
{
    Q_OBJECT
public:
    explicit QLineEditWithButton(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QToolButton *button;

private slots:
    void buttonClick();

public slots:
    void setIconButton(QIcon icon);
    void setIconSize(QSize size);

signals:
    void buttonClicked();

};

#endif // QLINEEDITWITHBUTTON_H
