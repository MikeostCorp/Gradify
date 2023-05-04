#include "gradewindow.h"
#include "ui_gradewindow.h"

#include <QFile>
#include <QMessageBox>

gradeWindow::gradeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gradeWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування оцінки (%grade%)");
    setFixedSize(width(), height());
    idRowEdit = -1;

    ui->subjectComboBox->insertSeparator(1);
    ui->typeGradeComboBox->insertSeparator(1);
    ui->whoTakeComboBox->insertSeparator(1);
    ui->okLabel->setVisible(false);
    isNewRow = false;
}


gradeWindow::~gradeWindow()
{
    delete ui;
}


void gradeWindow::setBlackUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/whiteMenuIcon/raitingIco.png"));
    QFile file(":/styles/black/recordsForms/recordsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void gradeWindow::setWhiteUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/blackMenuIcon/raitingIco.png"));
    QFile file(":/styles/white/recordsForms/recordsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void gradeWindow::setSystemUI()
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


void gradeWindow::setData(QString titleName, QStringList listData)
{
    isNewRow = false;

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

    ui->okLabel->setVisible(false);
}


void gradeWindow::setDataStudentComboBox(QStringList list)
{
    ui->whoTakeComboBox->clear();
    ui->whoTakeComboBox->addItem("Оберіть отримувача");
    ui->whoTakeComboBox->insertSeparator(1);
    ui->whoTakeComboBox->addItems(list);
}


void gradeWindow::setDataTeacherComboBox(QStringList list)
{
    ui->teacherComboBox->clear();
    ui->teacherComboBox->addItem("Оберіть хто виставив");
    ui->teacherComboBox->insertSeparator(1);
    ui->teacherComboBox->addItems(list);
}


void gradeWindow::setDataSubjectComboBox(QStringList list)
{
    ui->subjectComboBox->clear();
    ui->subjectComboBox->addItem("Оберіть предмет");
    ui->subjectComboBox->insertSeparator(1);
    ui->subjectComboBox->addItems(list);
}


void gradeWindow::setTheme(const QString style)
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


void gradeWindow::newRow()
{
    setWindowTitle("Додавання оцінки");
    isNewRow = true;
    idRowEdit = -1;
    ui->okLabel->setVisible(false);

    ui->subjectComboBox->setCurrentIndex(0);
    ui->whoTakeComboBox->setCurrentIndex(0);
    ui->teacherComboBox->setCurrentIndex(0);
    ui->gradeSpinBox->setValue(2);
    ui->typeGradeComboBox->setCurrentIndex(0);
    ui->takeDateEdit->setDate(QDate::fromString("23/09/2001", "dd/MM/yyyy"));
    QString::number(ui->takeDateEdit->date().year()) + "." +
                    QString::number(ui->takeDateEdit->date().month()) + "." +
                    QString::number(ui->takeDateEdit->date().day()) + ".";
}


void gradeWindow::on_cancelButton_clicked()
{
    this->close();
}


QString gradeWindow::reverseDate(QString str)
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


QStringList gradeWindow::getCurrentData()
{
    QStringList dataList;

    dataList << QString::number(idRowEdit);
    dataList << ui->subjectComboBox->currentText();
    dataList << ui->whoTakeComboBox->currentText();
    dataList << ui->teacherComboBox->currentText();
    dataList << QString::number(ui->gradeSpinBox->value());
    dataList << ui->typeGradeComboBox->currentText();
    dataList << QString::number(ui->takeDateEdit->date().year()) + "." +
                    QString::number(ui->takeDateEdit->date().month()) + "." +
                    QString::number(ui->takeDateEdit->date().day()) + ".";

    return dataList;

}


void gradeWindow::on_saveButton_clicked()
{
    if (ui->subjectComboBox->currentIndex() not_eq 0 and
        ui->whoTakeComboBox->currentIndex() not_eq 0 and
        ui->teacherComboBox->currentIndex() not_eq 0 and
        ui->typeGradeComboBox->currentIndex() not_eq 0)
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
    else if (ui->subjectComboBox->currentIndex() == 0)
    {
        ui->subjectComboBox->setFocus();
        QMessageBox::critical(this,"","Оберіть з якого предмету оцінка");
    }
    else if (ui->whoTakeComboBox->currentIndex() == 0)
    {
        ui->whoTakeComboBox->setFocus();
        QMessageBox::critical(this,"","Оберіть хто отримав оцінку");
    }
    else if (ui->teacherComboBox->currentIndex() == 0)
    {
        ui->teacherComboBox->setFocus();
        QMessageBox::critical(this,"","Оберіть хто виставив оцінку");
    }
    else if (ui->typeGradeComboBox->currentIndex() == 0)
    {
        ui->typeGradeComboBox->setFocus();
        QMessageBox::critical(this,"","Оберіть тип оцінки");
    }
}

