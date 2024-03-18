#ifndef GRADESTATISTICS_H
#define GRADESTATISTICS_H

#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QWidget>

namespace Ui {
class GradeStatisticsWindow;
}

class GradeStatisticsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GradeStatisticsWindow(QWidget *parent = nullptr);
    ~GradeStatisticsWindow();

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

    void updateTeacherComboBox();
    void clearTeacherComboBox();
    void clearSubjectComboBox();

    void clearPieChart();

    void on_categoryComboBox_currentIndexChanged(int index);
    void on_teacherComboBox_currentIndexChanged(int index);
    void on_subjectComboBox_currentIndexChanged(int index);

private:
    Ui::GradeStatisticsWindow *ui;

    QChartView *chartView;
    QChart *chart;

    QPieSeries *series;

public slots:
    void setTheme(const QString &style);
};

#endif // GRADESTATISTICS_H
