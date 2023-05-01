#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QWidget>
#include <QValidator>

namespace Ui {
class studentWindow;
}

class studentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit studentWindow(QWidget *parent = nullptr);
    ~studentWindow();

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();
    void on_cancelButton_clicked();
    void on_numberLineEdit_textChanged(const QString &arg1);
    void on_saveButton_clicked();

    QString reverseDate(QString str);
    QValidator *getValidatorPass();
    QStringList getCurrentData();


private:
    Ui::studentWindow *ui;

    bool isNewRow;

    int idRowEdit;

public slots:
    void setData(QString titleName, QStringList listData);
    void setComboBox(QStringList groupList);
    void setTheme(const QString style);
    void newRow();

signals:
    void sendData(QStringList, bool);
};

#endif // STUDENTWINDOW_H
