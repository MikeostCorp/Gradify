#ifndef SUBJECTWINDOW_H
#define SUBJECTWINDOW_H

#include <QWidget>

namespace Ui {
class subjectWindow;
}

class subjectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit subjectWindow(QWidget *parent = nullptr);
    ~subjectWindow();

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();
    void on_cancelButton_clicked();
    void on_saveButton_clicked();
    void setCurrentAllTime();

    QStringList getCurrentData();

private:
    Ui::subjectWindow *ui;

    bool isNewRow;

    int idRowEdit;

public slots:
    void setData(QString titleName, QStringList listData);
    void setTeacherComboBox(const QStringList teacherList);
    void setTheme(const QString style);
    void newRow();

signals:
    void sendData(QStringList, bool);
};

#endif // SUBJECTWINDOW_H
