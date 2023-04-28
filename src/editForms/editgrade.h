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
    void on_saveButton_clicked();

    QString reverseDate(QString str);
    QStringList getCurrentData();

private:
    Ui::editGrade *ui;
    int idRowEdit;

public slots:
    void setData(QString titleName, QStringList listData);
    void setDataStudentComboBox(QStringList list);
    void setDataTeacherComboBox(QStringList list);
    void setDataSubjectComboBox(QStringList list);
    void setTheme(const QString style);

signals:
    void sendData(QStringList);
};

#endif // EDITGRADE_H
