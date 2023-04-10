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
    ui->conditionLineEdit_2->setVisible(false);
    currentTabelSelect = "NULL";
    close();
}


filterForm::~filterForm()
{
    delete ui;
}


void filterForm::setListTable(QString tableName, const QMap<QString, QString> tableNameType)
{
    if (currentTabelSelect != tableName)
    {
        ui->conditionComboBox->setEnabled(false);
        QStringList columnList = tableNameType.keys();

        ui->tableComboBox->clear();
        ui->conditionLineEdit->clear();
        ui->conditionLineEdit_2->clear();

        ui->tableComboBox->addItem("Оберіть колонку", 0);
        ui->tableComboBox->insertSeparator(1);
        ui->tableComboBox->addItems(columnList);
        ui->conditionComboBox->setCurrentIndex(0);

        currentTabelSelect = tableName;
        typeColumnsMap = tableNameType;

        ui->conditionLineEdit->setPlaceholderText("Текст");
        ui->conditionLineEdit->setValidator(nullptr);
    }
}


void filterForm::on_filterPushButton_clicked()
{
    if (ui->tableComboBox->currentIndex() > 0 and ui->conditionComboBox->currentIndex() > 0)
    {
        QString strSqlFilter;
        strSqlFilter = "SELECT `" + currentTabelSelect + "`.*";
        strSqlFilter += "\nFROM `" + currentTabelSelect + "`";
        strSqlFilter += "\nWHERE `" + currentTabelSelect +"`.`" + ui->tableComboBox->currentText() + "` ";

        if (currentPlaceHolderText == "Число")
        {
            if (ui->conditionComboBox->currentText() != "between")
            {
                strSqlFilter += ui->conditionComboBox->currentText() + " " + ui->conditionLineEdit->text();
            }
            else if (ui->conditionComboBox->currentText() == "between" and !ui->conditionLineEdit_2->text().isEmpty()
                     and ui->conditionLineEdit->text().toInt() < ui->conditionLineEdit_2->text().toInt())
            {
                strSqlFilter += "BETWEEN " + ui->conditionLineEdit->text() + " AND " + ui->conditionLineEdit_2->text();
            }
            else if (ui->conditionComboBox->currentText() == "between" and ui->conditionLineEdit_2->text().isEmpty())
            {
                QMessageBox::critical(this,"","Введіть значення умови фільтрування!");
                ui->conditionLineEdit_2->setFocus();
                return;
            }
            else if (ui->conditionComboBox->currentText() == "between"
                     and ui->conditionLineEdit->text().toInt() >= ui->conditionLineEdit_2->text().toInt())
            {
                QMessageBox::critical(this,"","Перше значення повине бути меншим за друге!");
                ui->conditionLineEdit->setFocus();
                return;
            }
        }
        else if (currentPlaceHolderText == "Текст")
        {
            if (ui->conditionComboBox->currentText() == "like%")
            {
                strSqlFilter += "LIKE '" + ui->conditionLineEdit->text() + "%'";
            }
            else if (ui->conditionComboBox->currentText() == "%like")
            {
                strSqlFilter += "LIKE '%" + ui->conditionLineEdit->text() + "'";
            }
            else if (ui->conditionComboBox->currentText() == "%like%")
            {
                strSqlFilter += "LIKE '%" + ui->conditionLineEdit->text() + "%'";
            }
        }
        else if (currentPlaceHolderText == "Дата")
        {
            if (ui->conditionComboBox->currentText() != "between")
            {
                strSqlFilter += ui->conditionComboBox->currentText() + " '" + reverseDate(ui->conditionLineEdit->text()) + "'";
            }
            /*else if (ui->conditionComboBox->currentText() == "between" and !ui->conditionLineEdit_2->text().isEmpty()
                     and ui->conditionLineEdit->text().toInt() < ui->conditionLineEdit_2->text().toInt())
            {
                strSqlFilter += "BETWEEN '" + reverseDate(ui->conditionLineEdit->text()) + "' AND '"
                        + reverseDate(ui->conditionLineEdit_2->text()) + "'";
            }
            else if (ui->conditionComboBox->currentText() == "between" and ui->conditionLineEdit_2->text().isEmpty())
            {
                QMessageBox::critical(this,"","Введіть значення умови фільтрування!");
                ui->conditionLineEdit_2->setFocus();
                return;
            }
            else if (ui->conditionComboBox->currentText() == "between"
                     and ui->conditionLineEdit->text().toInt() >= ui->conditionLineEdit_2->text().toInt())
            {
                QMessageBox::critical(this,"","Перше значення повине бути меншим за друге!");
                ui->conditionLineEdit->setFocus();
                return;
            }*/
        }

        emit sendFilter(strSqlFilter, ui->tableComboBox->currentText());
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
        QMessageBox::critical(this,"","Введіть значення умови фільтрування");
        ui->conditionLineEdit->setFocus();
    }
}


void filterForm::on_conditionComboBox_currentTextChanged(const QString &arg1)
{
    ui->conditionComboBox->clearFocus();

    if (ui->conditionComboBox->currentText() == "between")
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
    }
    else
    {
        ui->conditionLineEdit->setPlaceholderText(currentPlaceHolderText);
        ui->conditionLineEdit->resize(61, ui->conditionLineEdit->height());
        ui->conditionLineEdit_2->setVisible(false);
        ui->conditionLineEdit_2->clear();
    }
}


void filterForm::on_conditionLineEdit_editingFinished()
{
    ui->conditionLineEdit->clearFocus();
}


void filterForm::on_tableComboBox_currentTextChanged(const QString &arg1)
{
    ui->tableComboBox->clearFocus();

    if (typeColumnsMap.value(arg1) == "string")
    {
        setStringTypeComboBox();
    }
    else if (typeColumnsMap.value(arg1) == "int")
    {
        setIntTypeComboBox();
    }
    else if (typeColumnsMap.value(arg1) == "date")
    {
        setDateTypeComboBox();
    }
}


void filterForm::setIntTypeComboBox()
{
    ui->conditionComboBox->setEnabled(true);
    ui->conditionComboBox->clear();
    ui->conditionComboBox->addItem("Оберіть умову", 0);
    ui->conditionComboBox->insertSeparator(1);
    ui->conditionComboBox->addItem(">", 2);
    ui->conditionComboBox->addItem("<", 3);
    ui->conditionComboBox->addItem("<=", 4);
    ui->conditionComboBox->addItem(">=", 5);
    ui->conditionComboBox->addItem("=", 6);
    ui->conditionComboBox->addItem("between", 7);

    ui->conditionLineEdit->setValidator(new QIntValidator(0, 10000, this));
    ui->conditionLineEdit_2->setValidator(new QIntValidator(0, 10000, this));

    currentPlaceHolderText = "Число";
    ui->conditionLineEdit->setPlaceholderText(currentPlaceHolderText);
}


void filterForm::setStringTypeComboBox()
{
    ui->conditionComboBox->setEnabled(true);
    ui->conditionComboBox->clear();
    ui->conditionComboBox->addItem("Оберіть умову", 0);
    ui->conditionComboBox->insertSeparator(1);
    ui->conditionComboBox->addItem("like%", 2);
    ui->conditionComboBox->addItem("%like", 3);
    ui->conditionComboBox->addItem("%like%", 4);

    ui->conditionLineEdit->setValidator(nullptr);
    ui->conditionLineEdit_2->setValidator(nullptr);

    currentPlaceHolderText = "Текст";
    ui->conditionLineEdit->setPlaceholderText(currentPlaceHolderText);
}


void filterForm::setDateTypeComboBox()
{
    ui->conditionComboBox->setEnabled(true);
    ui->conditionComboBox->clear();
    ui->conditionComboBox->addItem("Оберіть умову", 0);
    ui->conditionComboBox->insertSeparator(1);
    ui->conditionComboBox->addItem(">", 2);
    ui->conditionComboBox->addItem("<", 3);
    ui->conditionComboBox->addItem("<=", 4);
    ui->conditionComboBox->addItem(">=", 5);
    ui->conditionComboBox->addItem("=", 6);
    //ui->conditionComboBox->addItem("between", 7);


    // можно доделать регулярное выражение чтобы не вводить больше 31 дня и 12 месяцев
    ui->conditionLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^(\\d\\d)\\.(\\d\\d)\\.(\\d\\d)$"), this));
    ui->conditionLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^(\\d\\d)\\.(\\d\\d)\\.(\\d\\d)$"), this));
    currentPlaceHolderText = "Дата";
    ui->conditionLineEdit->setPlaceholderText(currentPlaceHolderText);

}

QString filterForm::reverseDate(QString str)
{
    QString tempStr = str;

    tempStr[0] = str[str.length() - 2];
    tempStr[1] = str[str.length() - 1];

    tempStr[str.length() - 2] = str[0];
    tempStr[str.length() - 1] = str[1];

    return tempStr;
}
