#ifndef EDITSTUDENT_H
#define EDITSTUDENT_H

#include <QWidget>

namespace Ui {
class editStudent;
}

class editStudent : public QWidget
{
    Q_OBJECT

public:
    explicit editStudent(QWidget *parent = nullptr);
    ~editStudent();

private:
    Ui::editStudent *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName);
};

#endif // EDITSTUDENT_H
