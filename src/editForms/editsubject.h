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

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

    void on_cancelButton_clicked();

private:
    Ui::editSubject *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName);
    void setTheme(const QString style);
};

#endif // EDITSUBJECT_H
