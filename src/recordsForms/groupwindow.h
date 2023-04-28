#ifndef GROUPWINDOW_H
#define GROUPWINDOW_H

#include <QWidget>

namespace Ui {
class groupWindow;
}

class groupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit groupWindow(QWidget *parent = nullptr);
    ~groupWindow();

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();
    void on_cancelButton_clicked();
    void on_saveButton_clicked();
    void on_startStudySpinBox_valueChanged(int arg1);

    QStringList getCurrentData();

private:
    Ui::groupWindow *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName, QStringList listData);
    void setDataCuratorComboBox(QStringList list);
    void setDataHeadManComboBox(QStringList list);
    void setTheme(const QString style);

signals:
    void sendData(QStringList);
};

#endif // GROUPWINDOW_H
