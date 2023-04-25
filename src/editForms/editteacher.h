#ifndef EDITTEACHER_H
#define EDITTEACHER_H

#include <QWidget>

namespace Ui {
class editTeacher;
}

class editTeacher : public QWidget
{
    Q_OBJECT

public:
    explicit editTeacher(QWidget *parent = nullptr);
    ~editTeacher();

private:
    Ui::editTeacher *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName);
};

#endif // EDITTEACHER_H
