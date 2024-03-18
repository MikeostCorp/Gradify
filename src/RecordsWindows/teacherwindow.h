#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QWidget>

namespace Ui {
class TeacherWindow;
}

class TeacherWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherWindow(QWidget *parent = nullptr);
    ~TeacherWindow();

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
    Ui::TeacherWindow *ui;

    bool isNewRow;

    int idRowEdit;

public slots:
    void setData(QString titleName, QStringList listData);
    void setTheme(const QString style);
    void newRow();

signals:
    void sendData(QStringList, bool);
};

#endif // TEACHERWINDOW_H
