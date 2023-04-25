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

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::editGrade *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName);
    void setTheme(const QString style);
};

#endif // EDITGRADE_H
