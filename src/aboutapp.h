#ifndef ABOUTAPP_H
#define ABOUTAPP_H

#include <QWidget>

namespace Ui {
class aboutApp;
}

class aboutApp : public QWidget
{
    Q_OBJECT

public:
    explicit aboutApp(QWidget *parent = nullptr);
    ~aboutApp();
    void changeEvent(QEvent *event) override;

private slots:
    void setBlackUI();

    void setWhiteUI();

    void setSystemUI();

private:
    Ui::aboutApp *ui;

public slots:
    void setThemeSettingUI(const QString style);

};

#endif // ABOUTAPP_H
