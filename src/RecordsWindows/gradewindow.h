#ifndef GRADEWINDOW_H
#define GRADEWINDOW_H

#include <QWidget>
#include "DatabaseHandler/databasehandler.h"

namespace Ui {
class GradeWindow;
}

class GradeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GradeWindow(QWidget *parent = nullptr, DatabaseHandler *dbHandler = nullptr);
    ~GradeWindow();

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
    Ui::GradeWindow *ui;
    DatabaseHandler *dbHandler;

    bool isNewRow;

    int idRowEdit;

public slots:
    void setData(QString titleName, const QStringList &listData);
    void setDataStudentComboBox(const QStringList &list);
    void setDataSubjectComboBox(const QStringList &list);
    void setTheme(const QString style);
    void newRow();

signals:
    void sendData(QStringList, bool);
    void requestDataFromDatabase(const QString &tableName);
};

#endif // GRADEWINDOW_H
