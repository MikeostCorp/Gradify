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
    idRowEdit = listData[0].toInt();
    titleName.remove(0, titleName.indexOf('.') + 2);
    setWindowTitle("Редагування студента (" + titleName +")");

    ui->lastNameLineEdit->setFocus();

    ui->lastNameLineEdit->setFocus();
    ui->lastNameLineEdit->setText(listData[1]);
    ui->nameLineEdit->setText(listData[2]);
    ui->surnameLineEdit->setText(listData[3]);
    ui->numberLineEdit->setText(listData[4]);
    ui->birthDayDataEdit->setDate(QDate::fromString(reverseDate(listData[5]), "dd/MM/yyyy"));
    ui->addressLineEdit->setText(listData[6]);

    ui->passLineEdit->setText(listData[7]);
    ui->groupComboBox->setCurrentText(listData[8]);
    ui->nalogLineEdit->setText(listData[9]);
}


void editStudent::setComboBox(QStringList groupList)
{
    ui->groupComboBox->clear();
    ui->groupComboBox->addItem("Оберіть групу");
    ui->groupComboBox->insertSeparator(1);
    ui->groupComboBox->addItems(groupList);
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


QString editStudent::reverseDate(QString str)
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


void editStudent::on_numberLineEdit_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
    {
        ui->numberLineEdit->setText("+380");
    }
}

