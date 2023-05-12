#ifndef SUBJECTSTATISTICS_H
#define SUBJECTSTATISTICS_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QTableView>
#include <QSqlQueryModel>

namespace Ui {
class subjectStatistics;
}

class subjectStatistics : public QWidget
{
    Q_OBJECT

public:
    explicit subjectStatistics(QWidget *parent = nullptr);
    ~subjectStatistics();

    void fillChart();
    void closeEvent(QCloseEvent *event) override;

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::subjectStatistics *ui;

    QChartView* chartView;
    QChart* chart;
    QPieSeries* series;

public slots:
    void setTheme(const QString &style);
};

#endif // SUBJECTSTATISTICS_H
