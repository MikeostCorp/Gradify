#ifndef FILTERFORM_H
#define FILTERFORM_H

#include <QWidget>

namespace Ui {
class filterForm;
}

class filterForm : public QWidget
{
    Q_OBJECT

public:
    explicit filterForm(QWidget *parent = nullptr);
    ~filterForm();

private:
    Ui::filterForm *ui;

public slots:
    void setListTable(const QStringList tableList);

signals:
    void sendFilter(const QString);

private slots:
    void on_filterPushButton_clicked();
    void on_conditionComboBox_currentTextChanged(const QString &arg1);
};

#endif // FILTERFORM_H
