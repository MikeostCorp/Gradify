#ifndef GROUPWINDOW_H
#define GROUPWINDOW_H

#include <QWidget>
#include "DatabaseHandler/databasehandler.h"

namespace Ui {
class GroupWindow;
}

class GroupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GroupWindow(QWidget *parent = nullptr, DatabaseHandler *dbHandler = nullptr);
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
    DatabaseHandler *dbHandler;

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
    void requestDataFromDatabase(const QString &tableName);
};

#endif // GROUPWINDOW_H
