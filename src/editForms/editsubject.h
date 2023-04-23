#ifndef EDITSUBJECT_H
#define EDITSUBJECT_H

#include <QWidget>

namespace Ui {
class editSubject;
}

class editSubject : public QWidget
{
    Q_OBJECT

public:
    explicit editSubject(QWidget *parent = nullptr);
    ~editSubject();

private:
    Ui::editSubject *ui;
};

#endif // EDITSUBJECT_H
