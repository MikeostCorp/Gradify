#include "subjectwindow.h"
#include "ui_subjectwindow.h"

#include <QFile>
#include <QMessageBox>

SubjectWindow::SubjectWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SubjectWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Редагування предмета (%subjectName%)");
    setFixedSize(width(), height());
    idRowEdit = -1;

    ui->controlComboBox->insertSeparator(1);
    ui->typeComboBox->insertSeparator(1);
    ui->teacherComboBox->insertSeparator(1);
    ui->allTimeSpinBox->setReadOnly(true);
    ui->okLabel->setVisible(false);
    isNewRow = false;

    connect(ui->lectureTimeSpinBox,
            &QSpinBox::valueChanged,
            this,
            &SubjectWindow::setCurrentAllTime);
    connect(ui->labTimeSpinBox, &QSpinBox::valueChanged, this, &SubjectWindow::setCurrentAllTime);
    connect(ui->seminarSpinBox, &QSpinBox::valueChanged, this, &SubjectWindow::setCurrentAllTime);
    connect(ui->soloWorkSpinBox, &QSpinBox::valueChanged, this, &SubjectWindow::setCurrentAllTime);
}

SubjectWindow::~SubjectWindow()
{
    delete ui;
}

void SubjectWindow::setBlackUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/whiteMenuIcon/subjectIco.png"));
    QFile file(":/styles/black/RecordsWindows/RecordsWindows.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}

void SubjectWindow::setWhiteUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/blackMenuIcon/subjectIco.png"));
    QFile file(":/styles/white/RecordsWindows/RecordsWindows.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}

void SubjectWindow::setSystemUI()
{
    QPalette basePalette;
    QColor baseColor = basePalette.base().color();
    QColor newBase = QColor::fromRgbF(1 - baseColor.redF(),
                                      1 - baseColor.greenF(),
                                      1 - baseColor.blueF());

    if (newBase.name() == "#000000") {
        setWhiteUI();
    } else {
        setBlackUI();
    }
}

void SubjectWindow::setData(QString titleName, QStringList listData)
{
    isNewRow = false;

    idRowEdit = listData[0].toInt();
    titleName.remove(0, titleName.indexOf('.') + 2);
    setWindowTitle("Редагування предмета (" + titleName + ")");

    ui->nameLineEdit->setFocus();

    ui->nameLineEdit->setText(listData[1]);
    ui->typeComboBox->setCurrentText(listData[2]);
    ui->teacherComboBox->setCurrentText(listData[3]);
    ui->allTimeSpinBox->setValue(listData[4].toInt());
    ui->lectureTimeSpinBox->setValue(listData[5].toInt());
    ui->labTimeSpinBox->setValue(listData[6].toInt());
    ui->seminarSpinBox->setValue(listData[7].toInt());
    ui->soloWorkSpinBox->setValue(listData[8].toInt());
    ui->semesrtLearnSpinBox->setValue(listData[9].toInt());
    ui->controlComboBox->setCurrentText(listData[10]);

    ui->okLabel->setVisible(false);
}

void SubjectWindow::setTeacherComboBox(const QStringList teacherList)
{
    ui->teacherComboBox->clear();
    ui->teacherComboBox->addItem("Оберіть викладача");
    ui->teacherComboBox->insertSeparator(1);
    ui->teacherComboBox->addItems(teacherList);
}

void SubjectWindow::setTheme(const QString style)
{
    if (style == "black") {
        setBlackUI();
    } else if (style == "white") {
        setWhiteUI();
    } else {
        setSystemUI();
    }
}

void SubjectWindow::newRow()
{
    setWindowTitle("Додавання предмета");
    isNewRow = true;
    idRowEdit = -1;
    ui->okLabel->setVisible(false);

    ui->nameLineEdit->clear();
    ui->typeComboBox->setCurrentIndex(0);
    ui->teacherComboBox->setCurrentIndex(0);
    ui->allTimeSpinBox->setValue(4);
    ui->lectureTimeSpinBox->setValue(1);
    ui->labTimeSpinBox->setValue(1);
    ui->seminarSpinBox->setValue(1);
    ui->soloWorkSpinBox->setValue(1);
    ui->semesrtLearnSpinBox->setValue(1);
    ui->controlComboBox->setCurrentIndex(0);
}

void SubjectWindow::on_cancelButton_clicked()
{
    this->close();
}

void SubjectWindow::on_saveButton_clicked()
{
    if (not ui->nameLineEdit->text().isEmpty() and ui->typeComboBox->currentIndex() not_eq 0
        and ui->teacherComboBox->currentIndex() not_eq 0
        and ui->controlComboBox->currentIndex() not_eq 0) {
        if (isNewRow) {
            ui->okLabel->setText("Запис додано");
            ui->okLabel->setVisible(true);
            emit sendData(getCurrentData(), true);
        } else {
            ui->okLabel->setText("Запис збережено");
            ui->okLabel->setVisible(true);
            emit sendData(getCurrentData(), false);
        }
    } else if (ui->nameLineEdit->text().isEmpty()) {
        ui->nameLineEdit->setFocus();
        QMessageBox::critical(this, "", "Введіть назву предмета");
    } else if (ui->typeComboBox->currentIndex() == 0) {
        ui->typeComboBox->setFocus();
        QMessageBox::critical(this, "", "Оберіть тип предмету");
    } else if (ui->teacherComboBox->currentIndex() == 0) {
        ui->teacherComboBox->setFocus();
        QMessageBox::critical(this, "", "Оберіть викладача предмету");
    } else if (ui->controlComboBox->currentIndex() == 0) {
        ui->controlComboBox->setFocus();
        QMessageBox::critical(this, "", "Оберіть семестровий контроль з предмету");
    }
}

void SubjectWindow::setCurrentAllTime()
{
    ui->allTimeSpinBox->setValue(ui->lectureTimeSpinBox->value() + ui->labTimeSpinBox->value()
                                 + ui->seminarSpinBox->value() + ui->soloWorkSpinBox->value());
}

QStringList SubjectWindow::getCurrentData()
{
    QStringList dataList;

    dataList << QString::number(idRowEdit);
    dataList << ui->nameLineEdit->text();
    dataList << ui->typeComboBox->currentText();
    dataList << ui->teacherComboBox->currentText();
    dataList << QString::number(ui->allTimeSpinBox->value());
    dataList << QString::number(ui->lectureTimeSpinBox->value());
    dataList << QString::number(ui->labTimeSpinBox->value());
    dataList << QString::number(ui->seminarSpinBox->value());
    dataList << QString::number(ui->soloWorkSpinBox->value());
    dataList << QString::number(ui->semesrtLearnSpinBox->value());
    dataList << ui->controlComboBox->currentText();

    return dataList;
}
