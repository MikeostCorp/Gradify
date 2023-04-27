#include "editgrade.h"
#include "ui_editgrade.h"

#include <QFile>
#include <QMessageBox>

editGrade::editGrade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editGrade)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування оцінки (%grade%)");
    setFixedSize(width(), height());
    idRowEdit = -1;

    ui->subjectComboBox->insertSeparator(1);
    ui->typeGradeComboBox->insertSeparator(1);
    ui->whoTakeComboBox->insertSeparator(1);
}


editGrade::~editGrade()
{
    delete ui;
}


void editGrade::setBlackUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/whiteMenuIcon/raitingIco.png"));
    QFile file(":/styles/black/editForms/editForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void editGrade::setWhiteUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/blackMenuIcon/raitingIco.png"));
    QFile file(":/styles/white/editForms/editForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void editGrade::setSystemUI()
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


void editGrade::setData(QString titleName, QStringList listData)
{
    idRowEdit = listData[0].toInt();
    titleName.remove(0, titleName.indexOf('.') + 2);
    setWindowTitle("Редагування оцінки (" + titleName +")");

    ui->gradeSpinBox->setFocus();

    ui->subjectComboBox->setCurrentText(listData[1]);
    ui->whoTakeComboBox->setCurrentText(listData[2]);
    ui->teacherComboBox->setCurrentText(listData[3]);
    ui->gradeSpinBox->setValue(listData[4].toInt());
    ui->typeGradeComboBox->setCurrentText(listData[5]);
    ui->takeDateEdit->setDate(QDate::fromString(reverseDate(listData[6]), "dd/MM/yyyy"));
}


void editGrade::setDataStudentComboBox(QStringList list)
{
    ui->whoTakeComboBox->clear();
    ui->whoTakeComboBox->addItem("Оберіть отримувача");
    ui->whoTakeComboBox->insertSeparator(1);
    ui->whoTakeComboBox->addItems(list);
}


void editGrade::setDataTeacherComboBox(QStringList list)
{
    ui->teacherComboBox->clear();
    ui->teacherComboBox->addItem("Оберіть хто виставив");
    ui->teacherComboBox->insertSeparator(1);
    ui->teacherComboBox->addItems(list);
}


void editGrade::setDataSubjectComboBox(QStringList list)
{
    ui->subjectComboBox->clear();
    ui->subjectComboBox->addItem("Оберіть предмет");
    ui->subjectComboBox->insertSeparator(1);
    ui->subjectComboBox->addItems(list);
}


void editGrade::setTheme(const QString style)
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

void editGrade::on_cancelButton_clicked()
{
    this->close();
}


QString editGrade::reverseDate(QString str)
{
    QString newStrDate;

    newStrDate = str[str.length() - 2];
    newStrDate += str[str.length() - 1];
    newStrDate += "/";
    newStrDate += str[str.length() - 5];
    newStrDate += str[str.length() - 4];
    newStrDate += "/";
    newStrDate += str[str.length() - 10];
    newStrDate += str[str.length() - 9];
    newStrDate += str[str.length() - 8];
    newStrDate += str[str.length() - 7];

    return newStrDate;
}

//Оберіть хто виставив

