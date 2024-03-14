#include "querywindow.h"
#include "ui_querywindow.h"

#include <QDateEdit>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QTableView>
#include <QVBoxLayout>
#include <mainwindow.h>

QueryWindow::QueryWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::queryForm)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint, true);
    setFixedSize(width(), height());
    close();

    changedGradeTable = -1;
}

QueryWindow::~QueryWindow()
{
    delete ui;
}

void QueryWindow::on_mySQLPushButton_clicked()
{
    ui->mySQLPushButton->setFocus();
    show();
    emit clearFilter();
}

void QueryWindow::on_succesStudentPushButton_clicked()
{
    bool ok;

    QString strSqlQuery;
    QStringList listGroup;

    /*
    QSqlQueryModel *queryModel = new QSqlQueryModel(this);
    QTableView *tableView = new QTableView(this);

    queryModel->setQuery("SELECT `Назва`"
                         "FROM `Групи`");
    tableView->setModel(queryModel);

    for (int row = 0; row < queryModel->rowCount(); ++row) {
        listGroup.append(tableView->model()->index(row, 0).data().toString());
    }

    QString selectedGroup = QInputDialog::getItem(this,
                                                  tr("Запит по успішності групи"),
                                                  tr("Оберіть групу:"),
                                                  listGroup,
                                                  0,
                                                  false,
                                                  &ok);

    if (ok) {
        strSqlQuery = "SELECT `Отримувач`, AVG(`Оцінка`) AS 'Середній бал' "
                      "FROM `Оцінки`, `Студенти` "
                      "WHERE `Студенти`.`Прізвище` = SUBSTRING_INDEX(`Отримувач`, ' ', 1) "
                      "AND `Студенти`.`Група` = '"
                      + selectedGroup
                      + "' "
                        "GROUP BY `Отримувач` "
                        "ORDER BY AVG(`Оцінка`) DESC;";

        emit sendQuery(strSqlQuery);
    }
    */
}

void QueryWindow::on_searchGradeStudentButton_clicked()
{

    /*
    if (changedGradeTable == 2) {
        bool ok;

        QString strSqlQuery;
        QStringList listGroup;


        QSqlQueryModel *queryModel = new QSqlQueryModel(this);
        QTableView *tableView = new QTableView(this);

        queryModel->setQuery("SELECT `Назва`"
                             "FROM `Групи`");
        tableView->setModel(queryModel);

        for (int row = 0; row < queryModel->rowCount(); ++row) {
            listGroup.append(tableView->model()->index(row, 0).data().toString());
        }

        QString selectedGroup = QInputDialog::getItem(this,
                                                      tr("Оберіть групу студента"),
                                                      tr("Оберіть групу:"),
                                                      listGroup,
                                                      0,
                                                      false,
                                                      &ok);

        if (ok) {
            QStringList studentList;

            queryModel->setQuery("SELECT `Прізвище`, `Ім\'я` ,`По батькові`"
                                 "FROM `Студенти`"
                                 "WHERE `Студенти`.`Група` = '"
                                 + selectedGroup + "'");
            tableView->setModel(queryModel);

            for (int row = 0; row < queryModel->rowCount(); ++row) {
                studentList.append(tableView->model()->index(row, 0).data().toString() + " "
                                   + tableView->model()->index(row, 1).data().toString() + " "
                                   + tableView->model()->index(row, 2).data().toString());
            }

            QString selectedStudent = QInputDialog::getItem(this,
                                                            tr("Оберіть студента"),
                                                            tr("Оберіть студента для запиту:"),
                                                            studentList,
                                                            0,
                                                            false,
                                                            &ok);
            if (ok) {
                QString dateStr = getDateWithDialog();

                if (dateStr not_eq "NULL") {
                    strSqlQuery = "`Оцінки`.`Отримувач` = '" + selectedStudent
                                  + "' "
                                    "AND `Оцінки`.`Дата виставлення` = '"
                                  + dateStr + "'";
                    emit sendFilter(strSqlQuery, "Дата виставлення");
                }
            }
        }
    } else {
        QMessageBox::information(this, "", "Для цього запиту потрібно\nвідкрити таблицю оцінок");
    }
    */
}

QString QueryWindow::getDateWithDialog()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Оберіть дату");

    QDateEdit dateEdit;
    dateEdit.setDisplayFormat("dd.MM.yyyy");
    dateEdit.setMinimumDate(QDate::fromString("01/01/2000", "dd/MM/yyyy"));
    dateEdit.setCalendarPopup(false);

    QLabel labelText("Введіть дату для пошуку оцінок");
    QPushButton okButton("Ок");
    QPushButton cancelButton("Скасувати");

    QVBoxLayout mainLayout(&dialog);
    mainLayout.addWidget(&labelText);
    mainLayout.addWidget(&dateEdit);

    QHBoxLayout buttonLayout;
    buttonLayout.addStretch();
    buttonLayout.addWidget(&okButton, QMessageBox::YesRole);
    buttonLayout.addWidget(&cancelButton, QMessageBox::NoRole);

    mainLayout.addLayout(&buttonLayout);

    QObject::connect(&okButton, &QPushButton::clicked, [&dateEdit, &dialog]() { dialog.accept(); });

    QObject::connect(&cancelButton, &QPushButton::clicked, [&dialog]() { dialog.reject(); });

    dialog.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    dialog.setFixedSize(dialog.sizeHint());
    dialog.exec();

    if (dialog.result() == QDialog::Accepted) {
        return dateEdit.date().toString("yyyy-MM-dd");
    } else {
        return "NULL";
    }
}

void QueryWindow::selectedGradeTable(int status)
{
    changedGradeTable = status;
}

void QueryWindow::on_avgScorePushButton_clicked()
{
    QString query = "SELECT `Групи`.`Назва`, ROUND(AVG(CAST(`Оцінки`.`Оцінка` as float)), 2) as "
                    "`Середня оцінка`"
                    "FROM `Групи`, `Студенти`, `Оцінки`"
                    "WHERE `Групи`.`Назва` = `Студенти`.`Група`"
                    "AND SUBSTRING_INDEX(`Оцінки`.`Отримувач`, ' ', 1) = `Студенти`.`Прізвище`"
                    "GROUP BY(`Групи`.`Назва`)";

    emit sendQuery(query);
}
