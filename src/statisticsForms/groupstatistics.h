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

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::groupStatistics *ui;

public slots:
    void setTheme(const QString &style);

};

#endif // GROUPSTATISTICS_H
