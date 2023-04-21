#ifndef FILTERFORM_H
#define FILTERFORM_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class filterForm;
}

class filterForm : public QWidget
{
    Q_OBJECT

public:
    explicit filterForm(QWidget *parent = nullptr);
    ~filterForm();
    bool eventFilter(QObject *obj, QEvent *event);

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

    QGraphicsDropShadowEffect *paintDropRedShadowEffect();

    void on_clearFilterPushButton_clicked();

private:
    Ui::filterForm *ui;

    QString currentTabelSelect;
    QString currentPlaceHolderText;
    QString oldColumnSelect;
    QString strSqlFilter;

    QMap<QString, QString> typeColumnsMap;

public slots:
    void setListTable(QString tableName, const QMap<QString, QString> columnNameType);

signals:
    void sendFilter(const QString, const QString);
    void clearFilter();


};

#endif // FILTERFORM_H
