#ifndef QUERYWINDOW_H
#define QUERYWINDOW_H

#include <QWidget>

namespace Ui {
class queryForm;
}

class QueryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit QueryWindow(QWidget *parent = nullptr);
    ~QueryWindow();

private slots:
    void on_mySQLPushButton_clicked();
    void on_succesStudentPushButton_clicked();
    void on_searchGradeStudentButton_clicked();

    QString getDateWithDialog();

    void on_avgScorePushButton_clicked();

private:
    Ui::queryForm *ui;

    int changedGradeTable;

public slots:
    void selectedGradeTable(int status);

signals:
    void sendQuery(const QString);
    void sendFilter(const QString, const QString);
    void clearFilter();
};

#endif // QUERYWINDOW_H
