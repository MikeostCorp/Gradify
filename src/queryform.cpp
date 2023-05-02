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
    QMessageBox::information(this, "", "hello vinegret!\nIt's test!");
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

    queryModel->setQuery("SELECT `Назва` "
                         "FROM `Групи`");

    tableView->setModel(queryModel);

    if (tableView->model()->rowCount() > 0)
    {
        for (int row = 0; row < queryModel->rowCount(); ++row)
        {
            listGroup.append(tableView->model()->index(row,0).data().toString());
        }

        QString selectedGroup = QInputDialog::getItem(this, tr("Запит по успіншості групи"),
                                                     tr("Оберіть групу:"), listGroup,
                                                     0, false, &ok);

        if (ok)
        {
            // make query

                strSqlQuery += "SELECT `Студенти`.`Прізвище`,`Студенти`.`Ім'я`,`Студенти`.`По батькові`";

                queryModel->setQuery("SELECT `Назва` "
                                     "FROM `Предмети`");
                tableView->setModel(queryModel);

                for (int row = 0; row < queryModel->rowCount(); ++row)
                {
                    //strSqlQuery += ", `Предмети`.`" + tableView->model()->index(row,0).data().toString() + "`";
                }

                //strSqlQuery += " AVG(`Оцінки`.`Оцінка`)";

                strSqlQuery += "\n FROM `Групи`, `Предмети`, `Оцінки`, `Студенти`";
                //strSqlQuery += "\nWHERE 'Оцінка'.'Отримувач' LIKE (%'Студенти'.'Прізвище' "
                //                                "+ 'Студенти'.'Ім'я' + 'Студенти'.'По батькові'%)";

            //strSqlQuery = "SELECT `Студенти`.`Ім'я`, `Студенти`.`Прізвище`, `Предмети`.`Назва`, `Оцінки`.`Оцінка`"
            //"FROM `Студенти`"
            //"INNER JOIN `Групи` ON `Студенти`.`Група` = `Група`.`Назва`"
            //"INNER JOIN `Оцінки` ON `Студенти`.`Група` = Grades.studentId"
            //"INNER JOIN `Предмети` ON `Оцінки`.`Отримувач` LIKE '% `Студенти`.`Ім'я` + "
            //    "`Студенти`.`Прізвище` %' Subject.id"
            //"WHERE 'Групи'.'Назва' = '" + selectedGroup + "'";

               // WHERE grupa = grupa

                strSqlQuery = "SELECT `Студенти`.`Прізвище`, `Студенти`.`Ім'я`, `Студенти`.`По батькові`,  `Предмети`.`Назва`, AVG(g.grade) as `Середня оцінка`"
                "FROM `Студенти`"
                "JOIN `Групи` ON `Студенти`.`Група` = `Групи`.`Назва`"
                "WHERE  `Групи`.`Назва` = `Студенти`.`Група`"
                "GROUP BY `Студенти`.`Прізвище`, `Студенти`.`Ім'я`, `Студенти`.`По батькові`,  `Предмети`.`Назва`"
                "HAVING COUNT(*) = (SELECT COUNT(*) FROM `Предемти`)";


                QMessageBox::information(this,"",strSqlQuery);
                //strSqlQuery += "LIKE '%" + ui->conditionLineEdit->text() + "'";
                emit sendQuery(strSqlQuery);

        }
    }
}

