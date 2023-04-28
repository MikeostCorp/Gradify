#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QWidget>

namespace Ui {
class teacherWindow;
}

class teacherWindow : public QWidget
{
    Q_OBJECT

public:
    explicit teacherWindow(QWidget *parent = nullptr);
    ~teacherWindow();

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
    Ui::teacherWindow *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName, QStringList listData);
    void setTheme(const QString style);

signals:
    void sendData(QStringList);
};

#endif // TEACHERWINDOW_H
