#include "editteacher.h"
#include "ui_editteacher.h"

#include <QFile>
#include <QMessageBox>

editTeacher::editTeacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editTeacher)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування викладача (%teacherName%)");
    setFixedSize(width(), height());
    idRowEdit = -1;

    ui->categoryComboBox->insertSeparator(1);
    ui->specialComboBox->insertSeparator(1);

    QRegularExpression numberRE("^\\+380\\d{9}");
    QValidator *numberValidator = new QRegularExpressionValidator(numberRE, this);
    ui->numberLineEdit->setValidator(numberValidator);
}


editTeacher::~editTeacher()
{
    delete ui;
}


void editTeacher::setBlackUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/whiteMenuIcon/teachersIco.png"));
    QFile file(":/styles/black/editForms/editForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void editTeacher::setWhiteUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/blackMenuIcon/teachersIco.png"));
    QFile file(":/styles/white/editForms/editForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void editTeacher::setSystemUI()
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


void editTeacher::setData(QString titleName, QStringList listData)
{
    idRowEdit = listData[0].toInt();
    titleName.remove(0, titleName.indexOf('.') + 2);
    setWindowTitle("Редагування викладача (" + titleName +")");

    ui->lastNameLineEdit->setFocus();
    ui->lastNameLineEdit->setFocus();
    ui->lastNameLineEdit->setText(listData[1]);
    ui->nameLineEdit->setText(listData[2]);
    ui->surnameLineEdit->setText(listData[3]);
    ui->numberLineEdit->setText(listData[4]);
    ui->birthDayDataEdit->setDate(QDate::fromString(reverseDate(listData[5]), "dd/MM/yyyy"));
    ui->addressLineEdit->setText(listData[6]);

    ui->categoryComboBox->setCurrentText(listData[7]);
    ui->specialComboBox->setCurrentText(listData[8]);
}


void editTeacher::setTheme(const QString style)
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


void editTeacher::on_cancelButton_clicked()
{
    this->close();
}


QString editTeacher::reverseDate(QString str)
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


void editTeacher::on_numberLineEdit_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
    {
        ui->numberLineEdit->setText("+380");
    }
}

