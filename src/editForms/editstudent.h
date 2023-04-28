#ifndef EDITSTUDENT_H
#define EDITSTUDENT_H

#include <QWidget>
#include <QValidator>

namespace Ui {
class editStudent;
}

class editStudent : public QWidget
{
    Q_OBJECT

public:
    explicit editStudent(QWidget *parent = nullptr);
    ~editStudent();

private slots:
    void setBlackUI();
    void setWhiteUI();
    void setSystemUI();

    void on_cancelButton_clicked();
    QString reverseDate(QString str);
    QValidator *getValidatorPass();

    void on_numberLineEdit_textChanged(const QString &arg1);
    void on_saveButton_clicked();

private:
    Ui::editStudent *ui;

    int idRowEdit;

public slots:
    void setData(QString titleName, QStringList listData);
    void setComboBox(QStringList groupList);
    void setTheme(const QString style);
};

#endif // EDITSTUDENT_H
