#include "editgroup.h"
#include "ui_editgroup.h"

editGroup::editGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editGroup)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування групи (%groupName%)");
}

editGroup::~editGroup()
{
    delete ui;
}
