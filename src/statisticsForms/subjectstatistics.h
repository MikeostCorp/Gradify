#ifndef SUBJECTSTATISTICS_H
#define SUBJECTSTATISTICS_H

#include <QWidget>

namespace Ui {
class subjectStatistics;
}

class subjectStatistics : public QWidget
{
    Q_OBJECT

public:
    explicit subjectStatistics(QWidget *parent = nullptr);
    ~subjectStatistics();

private:
    Ui::subjectStatistics *ui;
};

#endif // SUBJECTSTATISTICS_H
