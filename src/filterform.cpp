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
    ui->conditionLineEdit_2->setVisible(false);
    close();
}


filterForm::~filterForm()
{
    delete ui;
}


void filterForm::setListTable(const QStringList tableList, const QString tableName)
{
    if (currentTabelSelect != tableName)
    {
        currentTabelSelect = tableName;

        ui->tableComboBox->clear();
        ui->conditionLineEdit->clear();
        ui->conditionLineEdit_2->clear();

        ui->tableComboBox->addItem("Оберіть колонку", 0);
        ui->tableComboBox->insertSeparator(1);
        ui->tableComboBox->addItems(tableList);
        ui->conditionComboBox->setCurrentIndex(0);
    }
}


void filterForm::setNormalLineEdit()
{
    ui->conditionLineEdit->setPlaceholderText("Текст");
    ui->conditionLineEdit->resize(61, ui->conditionLineEdit->height());
    //ui->conditionLineEdit->clear(); пока в коментирование, не удобно юзеру будет если он
    //                                меняет условие то чистится и само значение условия

    ui->conditionLineEdit_2->setVisible(false);
    ui->conditionLineEdit_2->clear();
}


void filterForm::on_filterPushButton_clicked()
{
    if (ui->tableComboBox->currentIndex() > 0 and ui->conditionComboBox->currentIndex() > 0 and !ui->conditionLineEdit->text().isEmpty())
    {
        QString strSqlFilter;
        strSqlFilter = "SELECT `" + currentTabelSelect + "`.*";
        strSqlFilter += "\nFROM `" + currentTabelSelect + "`";
        strSqlFilter += "\nWHERE `" + currentTabelSelect +"`.`" + ui->tableComboBox->currentText() + "` ";

        if (ui->conditionComboBox->currentIndex() >= 2 and ui->conditionComboBox->currentIndex() <= 6)
        {
            strSqlFilter += ui->conditionComboBox->currentText() + " " + ui->conditionLineEdit->text();
        }
        else if (ui->conditionComboBox->currentIndex() == 7)
        {
            strSqlFilter += "LIKE '" + ui->conditionLineEdit->text() + "%'";
        }
        else if (ui->conditionComboBox->currentIndex() == 8)
        {
            if (!ui->conditionLineEdit_2->text().isEmpty() and ui->conditionLineEdit->text().toInt() < ui->conditionLineEdit_2->text().toInt())
            {
                strSqlFilter += "BETWEEN " + ui->conditionLineEdit->text() + " AND " + ui->conditionLineEdit_2->text();
            }
            else if (ui->conditionLineEdit->text().toInt() >= ui->conditionLineEdit_2->text().toInt())
            {
                QMessageBox::critical(this, "", "Перше значення повине бути меншим за друге!");
                ui->conditionLineEdit->setFocus();
                return;
            }
            else
            {
                QMessageBox::critical(this, "", "Для цього оператора потрібно 2 значення!");
                ui->conditionLineEdit_2->setFocus();
                return;
            }
        }

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


void filterForm::on_conditionComboBox_currentTextChanged(const QString &arg1)
{
    ui->conditionComboBox->clearFocus();

    if (ui->conditionComboBox->currentText() == "<"
            or ui->conditionComboBox->currentText() == ">"
            or ui->conditionComboBox->currentText() == "<="
            or ui->conditionComboBox->currentText() == ">="
            or ui->conditionComboBox->currentText() == "=")
    {
        ui->conditionLineEdit->setInputMask("DDDDDDDD");   // only numbers
        setNormalLineEdit();
    }
    else if (ui->conditionComboBox->currentText() == "between")
    {
        ui->conditionLineEdit_2->setVisible(true);

        ui->conditionLineEdit->setPlaceholderText("1");
        ui->conditionLineEdit_2->setPlaceholderText("2");

        ui->conditionLineEdit->resize(ui->conditionLineEdit->height() + 10,
                                      ui->conditionLineEdit->height());

        ui->conditionLineEdit_2->resize(ui->conditionLineEdit->height() + 10,
                                        ui->conditionLineEdit->height());

        ui->conditionLineEdit_2->move(ui->conditionLineEdit->x() + 35,
                                      ui->conditionLineEdit->y());

        ui->conditionLineEdit->setInputMask("DDDDDDDD");
        ui->conditionLineEdit_2->setInputMask("DDDDDDDD");

    }
    else if (ui->conditionComboBox->currentText() == "like")
    {
        ui->conditionLineEdit->setInputMask("");
        setNormalLineEdit();
    }
}


void filterForm::on_conditionLineEdit_editingFinished()
{
    ui->conditionLineEdit->clearFocus();
}


void filterForm::on_tableComboBox_currentTextChanged(const QString &arg1)
{
    ui->tableComboBox->clearFocus();
}
