#ifndef GRADEWINDOW_H
#define GRADEWINDOW_H

#include <QWidget>

namespace Ui {
class gradeWindow;
}

class gradeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit gradeWindow(QWidget *parent = nullptr);
    ~gradeWindow();

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();
    void on_cancelButton_clicked();
    void on_saveButton_clicked();

    QString reverseDate(QString str);
    QStringList getCurrentData();

private:
    Ui::gradeWindow *ui;
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

#endif // GRADEWINDOW_H
