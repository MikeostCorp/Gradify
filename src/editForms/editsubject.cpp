#include "editsubject.h"
#include "ui_editsubject.h"

editSubject::editSubject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editSubject)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування предмета (%subjectName%)");

}

editSubject::~editSubject()
{
    delete ui;
}
