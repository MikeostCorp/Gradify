#include "editstudent.h"
#include "ui_editstudent.h"

#include <QFile>
#include <QMessageBox>

editStudent::editStudent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editStudent)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування студента (%studentPIB%)");
    setFixedSize(width(), height());
    idRowEdit = -1;

    ui->groupComboBox->insertSeparator(1);

    QRegularExpression numberRE("^\\+380\\d{9}");
    QValidator *numberValidator = new QRegularExpressionValidator(numberRE, this);
    ui->numberLineEdit->setValidator(numberValidator);
}


editStudent::~editStudent()
{
    delete ui;
}


void editStudent::setBlackUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/whiteMenuIcon/studentsIco.png"));
    QFile file(":/styles/black/editForms/editForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void editStudent::setWhiteUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/blackMenuIcon/studenstIco.png"));
    QFile file(":/styles/white/editForms/editForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void editStudent::setSystemUI()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(), 1 - baseColor.greenF(), 1 - baseColor.blueF());

    if (newBase.name() == "#000000")
    {
        setWhiteUI();
    }
    else
    {
        setBlackUI();
    }
}


void editStudent::setData(QString titleName, QStringList listData)
{
    idRowEdit = titleName.left(titleName.indexOf('.')).toInt();
    titleName.remove(0, titleName.indexOf('.') + 2);
    setWindowTitle("Редагування студента (" + titleName +")");


    ui->lastNameLineEdit->setFocus();
}


void editStudent::setTheme(const QString style)
{
    if (style == "black")
    {
        setBlackUI();
    }
    else if (style == "white")
    {
        setWhiteUI();
    }
    else
    {
        setSystemUI();
    }
}


void editStudent::on_cancelButton_clicked()
{
    this->close();
}


QString editStudent::reverseDate()
{

}


void editStudent::on_numberLineEdit_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
    {
        ui->numberLineEdit->setText("+380");
    }
}

