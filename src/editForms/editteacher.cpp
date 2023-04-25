#include "editteacher.h"
#include "ui_editteacher.h"

editTeacher::editTeacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editTeacher)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування викладача (%teacherName%)");
    idRowEdit = -1;
}


editTeacher::~editTeacher()
{
    delete ui;
}


void editTeacher::setData(QString titleName)
{
    idRowEdit = titleName.left(titleName.indexOf('.')).toInt();
    titleName.remove(0, titleName.indexOf('.') + 2);
    setWindowTitle("Редагування викладача (" + titleName +")");
}
