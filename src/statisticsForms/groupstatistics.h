#ifndef GROUPSTATISTICS_H
#define GROUPSTATISTICS_H

#include <QWidget>

namespace Ui {
class groupStatistics;
}

class groupStatistics : public QWidget
{
    Q_OBJECT

public:
    explicit groupStatistics(QWidget *parent = nullptr);
    ~groupStatistics();

private:
    Ui::groupStatistics *ui;
};

#endif // GROUPSTATISTICS_H
