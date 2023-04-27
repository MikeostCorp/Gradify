#ifndef EDITGROUP_H
#define EDITGROUP_H

#include <QWidget>

namespace Ui {
class editGroup;
}

class editGroup : public QWidget
{
    Q_OBJECT

public:
    explicit editGroup(QWidget *parent = nullptr);
    ~editGroup();

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::editGroup *ui;

    int idRowEdit;

private slots:
    void on_cancelButton_clicked();
    void on_saveButton_clicked();
    void on_startStudySpinBox_valueChanged(int arg1);

public slots:
    void setData(QString titleName, QStringList listData);
    void setDataCuratorComboBox(QStringList list);
    void setDataHeadManComboBox(QStringList list);
    void setTheme(const QString style);
};

#endif // EDITGROUP_H
