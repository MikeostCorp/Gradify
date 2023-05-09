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

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::subjectStatistics *ui;

public slots:
    void setTheme(const QString &style);
};

#endif // SUBJECTSTATISTICS_H
