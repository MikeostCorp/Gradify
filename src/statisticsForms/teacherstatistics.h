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

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::teacherStatistics *ui;

public slots:
    void setTheme(const QString &style);
};

#endif // TEACHERSTATISTICS_H
