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

    QString currentTabelSelect;

public slots:
    void setListTable(const QStringList tableList, const QString tableName);

    void setNormalLineEdit();

signals:
    void sendFilter(const QString, const int);

private slots:
    void on_filterPushButton_clicked();

    void on_tableComboBox_currentTextChanged(const QString &arg1);

    void on_conditionComboBox_currentTextChanged(const QString &arg1);

    void on_conditionLineEdit_editingFinished();
};

#endif // FILTERFORM_H
