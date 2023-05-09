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

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::studentStatistics *ui;

public slots:
    void setTheme(const QString &style);
};

#endif // STUDENTSTATISTICS_H
