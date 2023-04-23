#include "editgrade.h"
#include "ui_editgrade.h"

editGrade::editGrade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editGrade)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування оцінки (якої)");
}

editGrade::~editGrade()
{
    delete ui;
}
