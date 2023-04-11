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

private slots:
    void on_filterPushButton_clicked();

    void on_tableComboBox_currentTextChanged(const QString &arg1);

    void on_conditionComboBox_currentTextChanged(const QString &arg1);

    void on_conditionLineEdit_editingFinished();

    void setIntTypeComboBox();

    void setStringTypeComboBox();

    void setDateTypeComboBox();

    void setDisabledComboBox();

    QString reverseDate(QString str);

private:
    Ui::filterForm *ui;

    QString currentTabelSelect;
    QString currentPlaceHolderText;

    QMap<QString, QString> typeColumnsMap;

public slots:
    void setListTable(QString tableName, const QMap<QString, QString> columnNameType);

signals:
    void sendFilter(const QString, const QString);


};

#endif // FILTERFORM_H
