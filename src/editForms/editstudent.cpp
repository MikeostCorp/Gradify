#include "editstudent.h"
#include "ui_editstudent.h"

editStudent::editStudent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editStudent)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування студента (%studentPIB%)");
}

editStudent::~editStudent()
{
    delete ui;
}
