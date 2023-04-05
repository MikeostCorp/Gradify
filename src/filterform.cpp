#include "filterform.h"
#include "ui_filterform.h"

#include <QFile>
#include <QGraphicsDropShadowEffect>


filterForm::filterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::filterForm)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint, true);
    setFixedSize(width(), height());
    close();
}


filterForm::~filterForm()
{
    delete ui;
}


void filterForm::setListTable(const QStringList tableList)
{
    ui->tableComboBox->clear();
    ui->tableComboBox->addItem("Оберіть колонку", 0);
    ui->tableComboBox->insertSeparator(1);
    ui->tableComboBox->addItems(tableList);
}


void filterForm::on_filterPushButton_clicked()
{
    // алгоритм создания запроса с учетом что у нас в комбоБоксах
    // можно создать ещё пример фильтр с условием between
    // просто добавить на форму лайн эдит и скрыть его
    // и если в выборе условия выбрать between то уменьшать размер лайнд эдита который есть
    // и потом врубать висибл второго эдита

    emit sendFilter(ui->tableComboBox->currentText());
}

