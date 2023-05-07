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
    void on_groupComboBox_currentIndexChanged(int index);
    void setGroupComboBox();

    QString reverseDate(QString str);
    QStringList getCurrentData();

private:
    Ui::gradeWindow *ui;

    bool isNewRow;

    int idRowEdit;

public slots:
    void setData(QString titleName, QStringList listData);
    void setDataStudentComboBox(const QStringList list);
    void setDataTeacherComboBox(const QStringList list);
    void setDataSubjectComboBox(const QStringList list);
    void setTheme(const QString style);
    void newRow();

signals:
    void sendData(QStringList, bool);
};

#endif // GRADEWINDOW_H
