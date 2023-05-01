#include "studentwindow.h"
#include "ui_studentwindow.h"

#include <QFile>
#include <QMessageBox>

studentWindow::studentWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування студента (%studentPIB%)");
    setFixedSize(width(), height());
    idRowEdit = -1;

    ui->groupComboBox->insertSeparator(1);
    ui->okLabel->setVisible(false);

    QRegularExpression numberRE("^\\+380\\d{9}");
    QValidator *numberValidator = new QRegularExpressionValidator(numberRE, this);
    ui->numberLineEdit->setValidator(numberValidator);

    ui->passLineEdit->setValidator(getValidatorPass());
    ui->nalogLineEdit->setValidator(getValidatorPass());
    isNewRow = false;
}


studentWindow::~studentWindow()
{
    delete ui;
}


void studentWindow::setBlackUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/whiteMenuIcon/studentsIco.png"));
    QFile file(":/styles/black/recordsForms/recordsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void studentWindow::setWhiteUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/blackMenuIcon/studenstIco.png"));
    QFile file(":/styles/white/recordsForms/recordsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void studentWindow::setSystemUI()
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


void studentWindow::setData(QString titleName, QStringList listData)
{
    isNewRow = false;

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

    ui->okLabel->setVisible(false);
    ui->lastNameLineEdit->setFocus();
}


void studentWindow::setComboBox(QStringList groupList)
{
    ui->groupComboBox->clear();
    ui->groupComboBox->addItem("Оберіть групу");
    ui->groupComboBox->insertSeparator(1);
    ui->groupComboBox->addItems(groupList);
}


void studentWindow::setTheme(const QString style)
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


void studentWindow::newRow()
{
    isNewRow = true;
    idRowEdit = -1;
    ui->okLabel->setVisible(false);

    ui->lastNameLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->surnameLineEdit->clear();
    ui->numberLineEdit->clear();
    ui->birthDayDataEdit->setDate(QDate::fromString("01/01/1950", "dd/MM/yyyy"));
    ui->addressLineEdit->clear();
    ui->passLineEdit->clear();
    ui->groupComboBox->setCurrentIndex(0);
    ui->nalogLineEdit->clear();
}


void studentWindow::on_cancelButton_clicked()
{
    this->close();
}


QString studentWindow::reverseDate(QString str)
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


QValidator *studentWindow::getValidatorPass()
{
    QRegularExpression passRE("^\\d{9}");
    QValidator *passValidator = new QRegularExpressionValidator(passRE, this);
    return passValidator;
}


QStringList studentWindow::getCurrentData()
{
    QStringList dataList;

    dataList << QString::number(idRowEdit);
    dataList << ui->lastNameLineEdit->text();
    dataList << ui->nameLineEdit->text();
    dataList << ui->surnameLineEdit->text();
    dataList << ui->numberLineEdit->text();
    dataList << QString::number(ui->birthDayDataEdit->date().year()) + "." +
                    QString::number(ui->birthDayDataEdit->date().month()) + "." +
                    QString::number(ui->birthDayDataEdit->date().day()) + ".";
    dataList << ui->addressLineEdit->text();
    dataList << ui->passLineEdit->text();
    dataList << ui->groupComboBox->currentText();
    dataList << ui->nalogLineEdit->text();

    return dataList;
}


void studentWindow::on_numberLineEdit_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
    {
        ui->numberLineEdit->setText("+380");
    }
}


void studentWindow::on_saveButton_clicked()
{
    if (not ui->lastNameLineEdit->text().isEmpty() and
        not ui->nameLineEdit->text().isEmpty() and
        not ui->surnameLineEdit->text().isEmpty() and
         ui->numberLineEdit->text().length() == 13 and
        not ui->addressLineEdit->text().isEmpty() and
        ui->passLineEdit->text().length() == 9 and
        ui->nalogLineEdit->text().length() == 9 and
         ui->groupComboBox->currentIndex() not_eq 0)
    {
        if (isNewRow)
        {
            ui->okLabel->setText("Запис додано");
            ui->okLabel->setVisible(true);
            emit sendData(getCurrentData(), true);
        }
        else
        {
            ui->okLabel->setText("Запис збережено");
            ui->okLabel->setVisible(true);
            emit sendData(getCurrentData(), false);
        }
    }
    else if (ui->lastNameLineEdit->text().isEmpty())
    {
        ui->lastNameLineEdit->setFocus();
        QMessageBox::critical(this,"","Введіть прізвище");
    }
    else if (ui->nameLineEdit->text().isEmpty())
    {
        ui->nameLineEdit->setFocus();
        QMessageBox::critical(this,"","Введіть ім'я");
    }
    else if (ui->surnameLineEdit->text().isEmpty())
    {
        ui->surnameLineEdit->setFocus();
        QMessageBox::critical(this,"","Введіть по батькові");
    }
    else if (ui->numberLineEdit->text().length() not_eq 13)
    {
        ui->numberLineEdit->setFocus();
        QMessageBox::critical(this,"","Введіть коректний номер телефону у форматі:\n"
                                        "(+3800000000000)");
    }
    else if (ui->addressLineEdit->text().isEmpty())
    {
        ui->addressLineEdit->setFocus();
        QMessageBox::critical(this,"","Введіть адресу проживання");
    }
    else if (ui->passLineEdit->text().length() not_eq 9 )
    {
        ui->passLineEdit->setFocus();
        QMessageBox::critical(this,"","Введіть коректний номер паспорту студента");
    }
    else if (ui->nalogLineEdit->text().length() not_eq 9)
    {
        ui->nalogLineEdit->setFocus();
        QMessageBox::critical(this,"","Введіть коректний ІНН студента");
    }
    else if (ui->groupComboBox->currentIndex() == 0)
    {
        ui->groupComboBox->setFocus();
        QMessageBox::critical(this,"","Оберіть групу студента");
    }
}
