#include "editgrade.h"
#include "ui_editgrade.h"

editGrade::editGrade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editGrade)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування оцінки (%grade%)");
    idRowEdit = -1;
}


editGrade::~editGrade()
{
    delete ui;
}


void editGrade::setData(QString titleName)
{
    idRowEdit = titleName.left(titleName.indexOf('.')).toInt();
    titleName.remove(0, titleName.indexOf('.') + 2);
    setWindowTitle("Редагування оцінки (" + titleName +")");
}
