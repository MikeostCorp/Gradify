#ifndef STUDENTSTATISTICS_H
#define STUDENTSTATISTICS_H

#include <QWidget>

namespace Ui {
class studentStatistics;
}

class studentStatistics : public QWidget
{
    Q_OBJECT

public:
    explicit studentStatistics(QWidget *parent = nullptr);
    ~studentStatistics();

private:
    Ui::studentStatistics *ui;
};

#endif // STUDENTSTATISTICS_H
