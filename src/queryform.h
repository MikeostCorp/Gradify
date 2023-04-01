#ifndef QUERYFORM_H
#define QUERYFORM_H

#include <QWidget>

namespace Ui {
class queryForm;
}

class queryForm : public QWidget
{
    Q_OBJECT

public:
    explicit queryForm(QWidget *parent = nullptr);
    ~queryForm();

private:
    Ui::queryForm *ui;
};

#endif // QUERYFORM_H
