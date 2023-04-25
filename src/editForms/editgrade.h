#ifndef EDITGRADE_H
#define EDITGRADE_H

#include <QWidget>

namespace Ui {
class editGrade;
}

class editGrade : public QWidget
{
    Q_OBJECT

public:
    explicit editGrade(QWidget *parent = nullptr);
    ~editGrade();

private:
    Ui::editGrade *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName);
};

#endif // EDITGRADE_H
