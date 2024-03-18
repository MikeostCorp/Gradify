#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QValidator>
#include <QWidget>

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);
    ~StudentWindow();

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
    Ui::StudentWindow *ui;

    bool isNewRow;

    int idRowEdit;

public slots:
    void setData(QString titleName, QStringList listData);
    void setComboBox(const QStringList groupList);
    void setTheme(const QString style);
    void newRow();

signals:
    void sendData(QStringList, bool);
};

#endif // STUDENTWINDOW_H
