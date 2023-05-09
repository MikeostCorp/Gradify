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

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::gradeStatistics *ui;

public slots:
    void setTheme(const QString &style);

};

#endif // GRADESTATISTICS_H
