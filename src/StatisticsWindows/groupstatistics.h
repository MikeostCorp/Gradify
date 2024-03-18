#ifndef GROUPSTATISTICS_H
#define GROUPSTATISTICS_H

#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QWidget>

namespace Ui {
class GroupStatisticsWindow;
}

class GroupStatisticsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GroupStatisticsWindow(QWidget *parent = nullptr);
    ~GroupStatisticsWindow();

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

    void on_groupComboBox_currentIndexChanged(int index);
    void clearPieChart();

private:
    Ui::GroupStatisticsWindow *ui;

    QChartView *chartView;
    QChart *chart;

    QPieSeries *series;

public slots:
    void setTheme(const QString &style);
    void setGroupComboBox();
};

#endif // GROUPSTATISTICS_H
