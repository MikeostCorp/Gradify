#include "editsubject.h"
#include "ui_editsubject.h"

#include <QFile>
#include <QMessageBox>

editSubject::editSubject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editSubject)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування предмета (%subjectName%)");
    setFixedSize(width(), height());
    idRowEdit = -1;

    ui->controlComboBox->insertSeparator(1);
    ui->typeComboBox->insertSeparator(1);
}


editSubject::~editSubject()
{
    delete ui;
}


void editSubject::setBlackUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/whiteMenuIcon/subjectIco.png"));
    QFile file(":/styles/black/editForms/editForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void editSubject::setWhiteUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/blackMenuIcon/subjectIco.png"));
    QFile file(":/styles/white/editForms/editForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void editSubject::setSystemUI()
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


void editSubject::setData(QString titleName, QStringList listData)
{
    idRowEdit = listData[0].toInt();
    titleName.remove(0, titleName.indexOf('.') + 2);
    setWindowTitle("Редагування предмета (" + titleName +")");

    ui->nameLineEdit->setFocus();

    ui->nameLineEdit->setText(listData[1]);
    ui->typeComboBox->setCurrentText(listData[2]);
    ui->allTimeSpinBox->setValue(listData[3].toInt());
    ui->lectureTimeSpinBox->setValue(listData[4].toInt());
    ui->labTimeSpinBox->setValue(listData[5].toInt());
    ui->seminarSpinBox->setValue(listData[6].toInt());
    ui->soloWorkSpinBox->setValue(listData[7].toInt());
    ui->semesrtLearnSpinBox->setValue(listData[8].toInt());
    ui->controlComboBox->setCurrentText(listData[9]);

    ui->okLabel->setVisible(false);
}


void editSubject::setTheme(const QString style)
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


void editSubject::on_cancelButton_clicked()
{
    this->close();
}


void editSubject::on_saveButton_clicked()
{
    if (!ui->nameLineEdit->text().isEmpty() and
         ui->typeComboBox->currentIndex() != 0 and
         ui->controlComboBox->currentIndex() != 0)
    {
        ui->okLabel->setVisible(true);
        emit sendData(getCurrentData());
    }
    else if (ui->nameLineEdit->text().isEmpty())
    {
        ui->nameLineEdit->setFocus();
        QMessageBox::critical(this,"","Введіть назву предмета");
    }
    else if (ui->typeComboBox->currentIndex() == 0)
    {
        ui->typeComboBox->setFocus();
        QMessageBox::critical(this,"","Оберіть тип предмету");
    }
    else if (ui->controlComboBox->currentIndex() == 0)
    {
        ui->typeComboBox->setFocus();
        QMessageBox::critical(this,"","Оберіть семестровий контроль з предмету");
    }
}


QStringList editSubject::getCurrentData()
{
    QStringList dataList;

    dataList << QString::number(idRowEdit);
    dataList << ui->nameLineEdit->text();
    dataList << ui->typeComboBox->currentText();
    dataList << QString::number(ui->allTimeSpinBox->value());
    dataList << QString::number(ui->lectureTimeSpinBox->value());
    dataList << QString::number(ui->labTimeSpinBox->value());
    dataList << QString::number(ui->seminarSpinBox->value());
    dataList << QString::number(ui->soloWorkSpinBox->value());
    dataList << QString::number(ui->semesrtLearnSpinBox->value());
    dataList << ui->controlComboBox->currentText();

    return dataList;
}

