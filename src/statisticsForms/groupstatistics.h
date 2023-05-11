#ifndef GROUPSTATISTICS_H
#define GROUPSTATISTICS_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QPieSeries>

namespace Ui {
class groupStatistics;
}

class groupStatistics : public QWidget
{
    Q_OBJECT

public:
    explicit groupStatistics(QWidget *parent = nullptr);
    ~groupStatistics();

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

    void on_groupComboBox_currentIndexChanged(int index);
    void clearPieChart();

private:
    Ui::groupStatistics *ui;

    QChartView *chartView;
    QChart *chart;

    QPieSeries *series;

public slots:
    void setTheme(const QString &style);
    void setGroupComboBox();

};

#endif // GROUPSTATISTICS_H
