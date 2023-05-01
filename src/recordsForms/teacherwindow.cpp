#include "teacherwindow.h"
#include "ui_teacherwindow.h"

#include <QFile>
#include <QMessageBox>

teacherWindow::teacherWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacherWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування викладача (%teacherName%)");
    setFixedSize(width(), height());
    idRowEdit = -1;

    ui->categoryComboBox->insertSeparator(1);
    ui->specialComboBox->insertSeparator(1);
    ui->okLabel->setVisible(false);

    QRegularExpression numberRE("^\\+380\\d{9}");
    QValidator *numberValidator = new QRegularExpressionValidator(numberRE, this);
    ui->numberLineEdit->setValidator(numberValidator);

    isNewRow = false;
}


teacherWindow::~teacherWindow()
{
    delete ui;
}


void teacherWindow::setBlackUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/whiteMenuIcon/teachersIco.png"));
    QFile file(":/styles/black/recordsForms/recordsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void teacherWindow::setWhiteUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/blackMenuIcon/teachersIco.png"));
    QFile file(":/styles/white/recordsForms/recordsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void teacherWindow::setSystemUI()
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


void teacherWindow::setData(QString titleName, QStringList listData)
{
    isNewRow = false;

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

    ui->okLabel->setVisible(false);
    ui->lastNameLineEdit->setFocus();
}


void teacherWindow::setTheme(const QString style)
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


void teacherWindow::newRow()
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
    ui->categoryComboBox->setCurrentIndex(0);
    ui->specialComboBox->setCurrentIndex(0);
}


void teacherWindow::on_cancelButton_clicked()
{
    this->close();
}


QString teacherWindow::reverseDate(QString str)
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


QStringList teacherWindow::getCurrentData()
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
    dataList << ui->categoryComboBox->currentText();
    dataList << ui->specialComboBox->currentText();

    return dataList;
}


void teacherWindow::on_numberLineEdit_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
    {
        ui->numberLineEdit->setText("+380");
    }
}


void teacherWindow::on_saveButton_clicked()
{
    if (!ui->lastNameLineEdit->text().isEmpty() and
        !ui->nameLineEdit->text().isEmpty() and
        !ui->surnameLineEdit->text().isEmpty() and
         ui->numberLineEdit->text().length() == 13 and
        !ui->addressLineEdit->text().isEmpty() and
         ui->categoryComboBox->currentIndex() != 0 and
         ui->specialComboBox->currentIndex() != 0)
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
    else if (ui->numberLineEdit->text().length() != 13)
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
    else if (ui->categoryComboBox->currentIndex() == 0)
    {
        ui->categoryComboBox->setFocus();
        QMessageBox::critical(this,"","Оберіть категорію вчителя");
    }
    else if (ui->specialComboBox->currentIndex() == 0)
    {
        ui->specialComboBox->setFocus();
        QMessageBox::critical(this,"","Оберіть спеціальність вчителя");
    }
}

