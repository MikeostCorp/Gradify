#ifndef TEACHERSTATISTICS_H
#define TEACHERSTATISTICS_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QTableView>
#include <QSqlQueryModel>

namespace Ui {
class teacherStatistics;
}

class teacherStatistics : public QWidget
{
    Q_OBJECT

public:
    explicit teacherStatistics(QWidget *parent = nullptr);
    ~teacherStatistics();

    void fillChart();

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::teacherStatistics *ui;

    QChartView* chartView;
    QChart* chart;
    QPieSeries* series;

public slots:
    void setTheme(const QString &style);
};

#endif // TEACHERSTATISTICS_H
