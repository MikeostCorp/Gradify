#ifndef TEACHERSTATISTICS_H
#define TEACHERSTATISTICS_H

#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QTableView>
#include <QWidget>

namespace Ui {
class teacherStatistics;
}

class TeacherStatisticsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherStatisticsWindow(QWidget *parent = nullptr);
    ~TeacherStatisticsWindow();

    void fillChart();
    void closeEvent(QCloseEvent *event) override;

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::teacherStatistics *ui;

    QChartView *chartView;
    QChart *chart;
    QPieSeries *series;

public slots:
    void setTheme(const QString &style);
};

#endif // TEACHERSTATISTICS_H
