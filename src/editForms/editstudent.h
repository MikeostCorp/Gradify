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

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::editStudent *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName);
    void setTheme(const QString style);
};

#endif // EDITSTUDENT_H
