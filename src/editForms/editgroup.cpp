#include "editgroup.h"
#include "ui_editgroup.h"

editGroup::editGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editGroup)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування групи (%groupName%)");
    idRowEdit = -1;
}


editGroup::~editGroup()
{
    delete ui;
}


void editGroup::setData(QString titleName)
{
    idRowEdit = titleName.left(titleName.indexOf('.')).toInt();
    // выше строка нужна для последующей передачи верного айди в главную форму
    titleName.remove(0, titleName.indexOf('.') + 2);
    setWindowTitle("Редагування групи (" + titleName +")");
}
