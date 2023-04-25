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

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::editGroup *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName);
    void setTheme(const QString style);

private slots:
    void on_cancelButton_clicked();
};

#endif // EDITGROUP_H
