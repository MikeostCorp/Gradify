#include "filterform.h"
#include "ui_filterform.h"

#include <QMessageBox>
#include <QRegularExpression>

filterForm::filterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::filterForm)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint, true);
    setFixedSize(width(), height());
    ui->conditionComboBox->insertSeparator(1);
    currentTabelSelect = "NULL";
    close();
}


filterForm::~filterForm()
{
    delete ui;
}


void filterForm::setListTable(const QStringList tableList, const QString tableName)
{
    ui->tableComboBox->clear();
    ui->tableComboBox->addItem("Оберіть колонку", 0);
    ui->tableComboBox->insertSeparator(1);
    ui->tableComboBox->addItems(tableList);

    currentTabelSelect = tableName;
}


void filterForm::on_filterPushButton_clicked()
{
    // алгоритм создания запроса с учетом что у нас в комбоБоксах
    // можно создать ещё пример фильтр с условием between
    // просто добавить на форму лайн эдит и скрыть его
    // и если в выборе условия выбрать between то уменьшать размер лайнд эдита который есть
    // и потом врубать висибл второго эдита

    if (ui->tableComboBox->currentIndex() > 0 and ui->conditionComboBox->currentIndex() > 0 and !ui->conditionLineEdit->text().isEmpty())
    {
        QString strSqlFilter;

        strSqlFilter = "SELECT `" + currentTabelSelect + "`.*";
        strSqlFilter += "\nFROM `" + currentTabelSelect + "`";
        strSqlFilter += "\nWHERE `" + currentTabelSelect +"`.`" + ui->tableComboBox->currentText() + "` ";



        /*
         * Условие определение инт или стринг введен в условие
         *  если пригодится конечно всё это
         *
         * if (ui->conditionLineEdit->text().toInt())
        {
            //true
        }
        else
        {
            //false
        }

        */

        switch (ui->conditionComboBox->currentIndex())
        {
        case 2:
            strSqlFilter += "< ";
            break;
        case 3:
            strSqlFilter += "> ";
            break;
        case 4:
            strSqlFilter += "<= ";
            break;
        case 5:
            strSqlFilter += ">= ";
            break;
        case 6:
            strSqlFilter += "= ";
            break;
        case 7:
            strSqlFilter += "LIKE ";
            break;
        case 8:
            strSqlFilter += "BETWEEN ";
            break;
        }

        strSqlFilter +=  ui->conditionLineEdit->text();
        emit sendFilter(strSqlFilter, ui->tableComboBox->currentIndex() - 2);
    }
    else if (ui->tableComboBox->currentIndex() == 0)
    {
        QMessageBox::critical(this,"","Оберіть потрібну колонку!");
        ui->tableComboBox->setFocus();
    }
    else if (ui->conditionComboBox->currentIndex() == 0)
    {
        QMessageBox::critical(this,"","Оберіть умову!");
        ui->conditionComboBox->setFocus();
    }
    else
    {
        QMessageBox::critical(this,"","Введіть значення у умову фільтрування");
        ui->conditionLineEdit->setFocus();
    }
}


void filterForm::on_tableComboBox_currentTextChanged(const QString &arg1)
{
    ui->tableComboBox->clearFocus();
}


void filterForm::on_conditionComboBox_currentTextChanged(const QString &arg1)
{
    ui->conditionComboBox->clearFocus();
}


void filterForm::on_conditionLineEdit_editingFinished()
{
    ui->conditionLineEdit->clearFocus();
}

