#ifndef SUBJECTSTATISTICS_H
#define SUBJECTSTATISTICS_H

#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QTableView>
#include <QWidget>

namespace Ui {
class subjectStatistics;
}

class SubjectStatisticsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SubjectStatisticsWindow(QWidget *parent = nullptr);
    ~SubjectStatisticsWindow();

    void fillChart();
    void closeEvent(QCloseEvent *event) override;

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::subjectStatistics *ui;

    QChartView *chartView;
    QChart *chart;
    QPieSeries *series;

public slots:
    void setTheme(const QString &style);
};

#endif // SUBJECTSTATISTICS_H
