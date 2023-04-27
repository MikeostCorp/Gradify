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

    void on_cancelButton_clicked();
    QString reverseDate();

private:
    Ui::editGrade *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName, QStringList listData);
    void setTheme(const QString style);
};

#endif // EDITGRADE_H
