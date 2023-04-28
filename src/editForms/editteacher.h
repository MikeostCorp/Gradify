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
    void on_numberLineEdit_textChanged(const QString &arg1);
    void on_saveButton_clicked();

    QString reverseDate(QString str);
    QStringList getCurrentData();


private:
    Ui::editTeacher *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName, QStringList listData);
    void setTheme(const QString style);

signals:
    void sendData(QStringList);
};

#endif // EDITTEACHER_H
