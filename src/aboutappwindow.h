#ifndef ABOUTAPPWINDOW_H
#define ABOUTAPPWINDOW_H

#include <QWidget>

namespace Ui {
class aboutApp;
}

class AboutAppWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AboutAppWindow(QWidget *parent = nullptr);
    ~AboutAppWindow();
    void changeEvent(QEvent *event) override;

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

private:
    Ui::aboutApp *ui;

public slots:
    void setTheme(const QString &style);
};

#endif // ABOUTAPPWINDOW_H
