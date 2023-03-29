#ifndef FILTERFORM_H
#define FILTERFORM_H

#include <QWidget>

namespace Ui {
class filterForm;
}

class filterForm : public QWidget
{
    Q_OBJECT

public:
    explicit filterForm(QWidget *parent = nullptr);
    ~filterForm();

    void changeEvent(QEvent *event);
    void leaveEvent(QEvent *event);

private:
    Ui::filterForm *ui;
};

#endif // FILTERFORM_H
