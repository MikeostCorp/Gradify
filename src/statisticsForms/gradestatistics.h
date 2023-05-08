#ifndef GRADESTATISTICS_H
#define GRADESTATISTICS_H

#include <QWidget>

namespace Ui {
class gradeStatistics;
}

class gradeStatistics : public QWidget
{
    Q_OBJECT

public:
    explicit gradeStatistics(QWidget *parent = nullptr);
    ~gradeStatistics();

private:
    Ui::gradeStatistics *ui;
};

#endif // GRADESTATISTICS_H
