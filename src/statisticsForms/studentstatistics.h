#ifndef STUDENTSTATISTICS_H
#define STUDENTSTATISTICS_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QBarSet>
#include <QBarSeries>

namespace Ui {
class studentStatistics;
}

class studentStatistics : public QWidget
{
    Q_OBJECT

public:
    explicit studentStatistics(QWidget *parent = nullptr);
    ~studentStatistics();

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

    void on_yearSpinBox_valueChanged(int arg1);
    void on_groupComboBox_currentIndexChanged(int index);
    void on_studentComboBox_currentIndexChanged(int index);
    void clearChartSets();

    void setCurrentChart();

private:
    Ui::studentStatistics *ui;

    QChartView *chartView;

    QChart *chart;

    QBarSeries *series;

    QBarSet *set0;
    QBarSet *set1;
    QBarSet *set2;
    QBarSet *set3;

public slots:
    void setTheme(const QString &style);
    void updateGroupComboBox();
};

#endif // STUDENTSTATISTICS_H
