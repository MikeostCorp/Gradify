#ifndef GROUPWINDOW_H
#define GROUPWINDOW_H

#include <QWidget>

namespace Ui {
class GroupWindow;
}

class GroupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GroupWindow(QWidget *parent = nullptr);
    ~GroupWindow();

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();
    void on_cancelButton_clicked();
    void on_saveButton_clicked();
    void on_startStudySpinBox_valueChanged(int arg1);

    QStringList getCurrentData();

private:
    Ui::GroupWindow *ui;

    bool isNewRow;

    int idRowEdit;

public slots:
    void setData(QString titleName, QStringList listData);
    void setDataCuratorComboBox(const QStringList list);
    void setDataHeadManComboBox(const QString list);
    void setTheme(const QString style);
    void newRow();

signals:
    void sendData(QStringList, bool);
};

#endif // GROUPWINDOW_H
