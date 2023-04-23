#include "editteacher.h"
#include "ui_editteacher.h"

editTeacher::editTeacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editTeacher)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування викладача (%teacherName%)");
}

editTeacher::~editTeacher()
{
    delete ui;
}
