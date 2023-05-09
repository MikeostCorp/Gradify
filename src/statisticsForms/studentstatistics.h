#ifndef STUDENTSTATISTICS_H
#define STUDENTSTATISTICS_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QPieSeries>

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

    void on_groupComboBox_currentIndexChanged(int index);
    void on_studentComboBox_currentIndexChanged(int index);


private:
    Ui::studentStatistics *ui;

    QChartView *chartView;

public slots:
    void setTheme(const QString &style);
    void updateGroupComboBox();
};

#endif // STUDENTSTATISTICS_H
