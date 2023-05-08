#ifndef TEACHERSTATISTICS_H
#define TEACHERSTATISTICS_H

#include <QWidget>

namespace Ui {
class teacherStatistics;
}

class teacherStatistics : public QWidget
{
    Q_OBJECT

public:
    explicit teacherStatistics(QWidget *parent = nullptr);
    ~teacherStatistics();

private:
    Ui::teacherStatistics *ui;
};

#endif // TEACHERSTATISTICS_H
