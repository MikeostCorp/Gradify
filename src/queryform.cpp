#include "queryform.h"
#include "ui_queryform.h"

#include <QMessageBox>
#include <QTableView>
#include <QSqlTableModel>
#include <QInputDialog>

queryForm::queryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::queryForm)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint, true);
    setFixedSize(width(), height());
    close();
}


queryForm::~queryForm()
{
    delete ui;
}


void queryForm::on_mySQLPushButton_clicked()
{
    QMessageBox::information(this, "", "hello vinegret!\nIt's test!"); // когда это поменялось??
    ui->mySQLPushButton->setFocus();
    show();
}


void queryForm::on_succesStudentPushButton_clicked()
{
    bool ok;

    QString strSqlQuery;
    QStringList listGroup;

    QSqlQueryModel *queryModel = new QSqlQueryModel(this);
    QTableView *tableView = new QTableView(this);

    queryModel->setQuery("SELECT `Назва`"
                         "FROM `Групи`");
    tableView->setModel(queryModel);

    for (int row = 0; row < queryModel->rowCount(); ++row)
    {
        listGroup.append(tableView->model()->index(row,0).data().toString());
    }

    QString selectedGroup = QInputDialog::getItem(this, tr("Запит по успіншості групи"),
                                                     tr("Оберіть групу:"), listGroup,
                                                     0, false, &ok);

    if (ok)
    {
        strSqlQuery = "SELECT `Отримувач`, AVG(`Оцінка`) AS 'Середній бал'"
                      "FROM `Оцінки`, `Студенти`"
                      "WHERE `Студенти`.`Група` = '" + selectedGroup + "'"
                      "GROUP BY `Отримувач`"
                      "ORDER BY AVG(`Оцінка`) DESC;";

        emit sendQuery(strSqlQuery);
    }
}

