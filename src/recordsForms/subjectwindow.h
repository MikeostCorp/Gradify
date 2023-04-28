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

    QStringList getCurrentData();

private:
    Ui::subjectWindow *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName, QStringList listData);
    void setTheme(const QString style);

signals:
    void sendData(QStringList);
};

#endif // SUBJECTWINDOW_H
