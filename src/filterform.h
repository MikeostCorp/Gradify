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

private:
    Ui::filterForm *ui;

};

#endif // FILTERFORM_H
