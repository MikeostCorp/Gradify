#include "editstudent.h"
#include "ui_editstudent.h"

editStudent::editStudent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editStudent)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування студента (%studentPIB%)");
    idRowEdit = -1;
}


editStudent::~editStudent()
{
    delete ui;
}


void editStudent::setData(QString titleName)
{
    idRowEdit = titleName.left(titleName.indexOf('.')).toInt();
    titleName.remove(0, titleName.indexOf('.') + 2);
    setWindowTitle("Редагування студента (" + titleName +")");
}
