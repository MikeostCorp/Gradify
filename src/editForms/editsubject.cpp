#include "editsubject.h"
#include "ui_editsubject.h"

editSubject::editSubject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editSubject)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування предмета (%subjectName%)");
    idRowEdit = -1;
}


editSubject::~editSubject()
{
    delete ui;
}


void editSubject::setData(QString titleName)
{
    idRowEdit = titleName.left(titleName.indexOf('.')).toInt();
    titleName.remove(0, titleName.indexOf('.') + 2);
    setWindowTitle("Редагування предмета (" + titleName +")");
}
