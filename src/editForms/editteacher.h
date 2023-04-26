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

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

    void on_cancelButton_clicked();

private:
    Ui::editTeacher *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName);
    void setTheme(const QString style);
};

#endif // EDITTEACHER_H
