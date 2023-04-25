#ifndef EDITGROUP_H
#define EDITGROUP_H

#include <QWidget>

namespace Ui {
class editGroup;
}

class editGroup : public QWidget
{
    Q_OBJECT

public:
    explicit editGroup(QWidget *parent = nullptr);
    ~editGroup();

private:
    Ui::editGroup *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName);
};

#endif // EDITGROUP_H
