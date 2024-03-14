#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <QGraphicsDropShadowEffect>
#include <QWidget>

namespace Ui {
class FilterWindow;
}

class FilterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FilterWindow(QWidget *parent = nullptr);
    ~FilterWindow();
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

    void on_clearFilterPushButton_clicked();

    QGraphicsDropShadowEffect *paintDropRedShadowEffect();

private:
    Ui::FilterWindow *ui;

    QString currentTabelSelect;
    QString currentPlaceHolderText;
    QString oldColumnSelect;
    QString strSqlFilter;

    QMap<QString, QString> typeColumnsMap;

public slots:
    void setListTable(const QMap<QString, QString> columnNameType);

signals:
    void sendFilter(const QString, const QString);
    void clearFilter();
};

#endif // FILTERWINDOW_H
