#include "gradewindow.h"
#include "ui_gradewindow.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTableView>

GradeWindow::GradeWindow(QWidget *parent, DatabaseHandler *dbHandler)
    : QWidget(parent)
    , ui(new Ui::GradeWindow)
    , dbHandler(dbHandler)
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

    connect(this, &GradeWindow::requestDataFromDatabase, dbHandler, &DatabaseHandler::fetchData);
}

GradeWindow::~GradeWindow()
{
    delete ui;
}

void GradeWindow::setBlackUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/whiteMenuIcon/gradesIco.png"));
    QFile file(":/styles/black/RecordsWindows/RecordsWindows.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}

void GradeWindow::setWhiteUI()
{
    ui->mainImage->setPixmap(QPixmap(":/img/blackMenuIcon/gradesIco.png"));
    QFile file(":/styles/white/RecordsWindows/RecordsWindows.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}

void GradeWindow::setSystemUI()
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

void GradeWindow::setData(QString titleName, QStringList listData)
{
    isNewRow = false;
    setGroupComboBox();

    idRowEdit = listData[0].toInt();
    titleName.remove(0, titleName.indexOf('.') + 2);
    setWindowTitle("Редагування оцінки (" + titleName + ")");

    ui->gradeSpinBox->setFocus();
    ui->subjectComboBox->setCurrentText(listData[1]);

    QString cutStr = listData[2];
    QStringList FIOStr;

    QSqlQueryModel *queryModel = new QSqlQueryModel();
    QTableView *tableView = new QTableView();

    FIOStr.append(cutStr.left(cutStr.indexOf(' ')));
    cutStr.remove(0, cutStr.indexOf(' ') + 1);
    FIOStr.append(cutStr.left(cutStr.lastIndexOf(' ')));
    cutStr.remove(0, cutStr.lastIndexOf(' ') + 1);
    FIOStr.append(cutStr);

    QString queryMy = "SELECT `Група`"
                      "\nFROM `Студенти`"
                      "\nWHERE `Студенти`.`Прізвище` = '"
                      + FIOStr[0] + "'" + " AND `Студенти`.`Ім\'я` = '" + FIOStr[1] + "'"
                      + " AND `Студенти`.`По батькові` = '" + FIOStr[2] + "'";

    queryModel->setQuery(queryMy);
    tableView->setModel(queryModel);
    ui->groupComboBox->setCurrentText(tableView->model()->index(0, 0).data().toString());

    ui->whoTakeComboBox->setCurrentText(listData[2]);
    ui->gradeSpinBox->setValue(listData[3].toInt());
    ui->typeGradeComboBox->setCurrentText(listData[4]);
    ui->takeDateEdit->setDate(QDate::fromString(reverseDate(listData[5]), "dd/MM/yyyy"));

    ui->okLabel->setVisible(false);
}

void GradeWindow::setDataStudentComboBox(const QStringList list)
{
    ui->whoTakeComboBox->clear();
    ui->whoTakeComboBox->addItem("Оберіть отримувача");
    ui->whoTakeComboBox->insertSeparator(1);
    ui->whoTakeComboBox->addItems(list);
}

void GradeWindow::setDataSubjectComboBox(const QStringList list)
{
    ui->subjectComboBox->clear();
    ui->subjectComboBox->addItem("Оберіть предмет");
    ui->subjectComboBox->insertSeparator(1);
    ui->subjectComboBox->addItems(list);
}

void GradeWindow::setTheme(const QString style)
{
    if (style == "black") {
        setBlackUI();
    } else if (style == "white") {
        setWhiteUI();
    } else {
        setSystemUI();
    }
}

void GradeWindow::newRow()
{
    setWindowTitle("Додавання оцінки");
    setGroupComboBox();
    isNewRow = true;
    idRowEdit = -1;
    ui->okLabel->setVisible(false);
    ui->whoTakeComboBox->setEnabled(false);

    ui->subjectComboBox->setCurrentIndex(0);
    ui->whoTakeComboBox->setCurrentIndex(0);
    ui->gradeSpinBox->setValue(2);
    ui->typeGradeComboBox->setCurrentIndex(0);
    ui->takeDateEdit->setDate(QDate::currentDate());
    QString::number(ui->takeDateEdit->date().year()) + "."
        + QString::number(ui->takeDateEdit->date().month()) + "."
        + QString::number(ui->takeDateEdit->date().day()) + ".";
}

void GradeWindow::on_cancelButton_clicked()
{
    this->close();
}

QString GradeWindow::reverseDate(QString str)
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

QStringList GradeWindow::getCurrentData()
{
    QStringList dataList;

    dataList << QString::number(idRowEdit);
    dataList << ui->subjectComboBox->currentText();
    dataList << ui->whoTakeComboBox->currentText();
    dataList << QString::number(ui->gradeSpinBox->value());
    dataList << ui->typeGradeComboBox->currentText();
    dataList << QString::number(ui->takeDateEdit->date().day()) + "."
                    + QString::number(ui->takeDateEdit->date().month()) + "."
                    + QString::number(ui->takeDateEdit->date().year());

    return dataList;
}

void GradeWindow::on_saveButton_clicked()
{
    if (ui->subjectComboBox->currentIndex() not_eq 0
        and ui->whoTakeComboBox->currentIndex() not_eq 0
        and ui->typeGradeComboBox->currentIndex() not_eq 0) {
        if (isNewRow) {
            ui->okLabel->setText("Запис додано");
            ui->okLabel->setVisible(true);
            emit sendData(getCurrentData(), true);
        } else {
            ui->okLabel->setText("Запис збережено");
            ui->okLabel->setVisible(true);
            emit sendData(getCurrentData(), false);
        }
    } else if (ui->subjectComboBox->currentIndex() == 0) {
        ui->subjectComboBox->setFocus();
        QMessageBox::critical(this, "", "Оберіть з якого предмету оцінка");
    } else if (ui->groupComboBox->currentIndex() == 0) {
        ui->groupComboBox->setFocus();
        QMessageBox::critical(this, "", "Для вибору отримувача оберіть спочатку його групу");
    } else if (ui->whoTakeComboBox->currentIndex() == 0) {
        ui->whoTakeComboBox->setFocus();
        QMessageBox::critical(this, "", "Оберіть хто отримав оцінку");
    } else if (ui->typeGradeComboBox->currentIndex() == 0) {
        ui->typeGradeComboBox->setFocus();
        QMessageBox::critical(this, "", "Оберіть тип оцінки");
    }
}

void GradeWindow::on_groupComboBox_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->whoTakeComboBox->setCurrentIndex(0);
        ui->whoTakeComboBox->setEnabled(false);
    } else {
        ui->whoTakeComboBox->setEnabled(true);

        QStringList studentList;
        QEventLoop loop;

        auto handler
            = connect(dbHandler, &DatabaseHandler::dataReady, this, [&](const QByteArray &data) {
                  qDebug() << "Raw data received:" << data;
                  QJsonDocument doc = QJsonDocument::fromJson(data);
                  QJsonArray jsonArray = doc.array();

                  for (const QJsonValue &value : jsonArray) {
                      if (value.isObject()) {
                          QJsonObject studentData = value.toObject();

                          if (studentData.contains("Прізвище") && studentData.contains("Ім'я")
                              && studentData.contains("По батькові")
                              && studentData.contains("Група")
                              && studentData["Група"] == ui->groupComboBox->currentText()) {
                              QString fullName = studentData["Прізвище"].toString() + " "
                                                 + studentData["Ім'я"].toString() + " "
                                                 + studentData["По батькові"].toString();
                              studentList.append(fullName);
                          } else {
                              qDebug() << "Missing one or more keys in studentData";
                          }
                      } else {
                          qDebug() << "Value is not an object";
                      }
                  }
                  disconnect(dbHandler, &DatabaseHandler::dataReady, this, nullptr);
                  loop.quit();
              });

        emit requestDataFromDatabase("Студенти");
        loop.exec();

        setDataStudentComboBox(studentList);
    }
}

void GradeWindow::setGroupComboBox()
{
    ui->groupComboBox->clear();
    ui->groupComboBox->addItem("Оберіть групу отримувача");
    ui->groupComboBox->insertSeparator(1);

    QStringList listGroup;
    QEventLoop loop;

    auto handler = connect(dbHandler, &DatabaseHandler::dataReady, this, [&](const QByteArray &data) {
        qDebug() << "Raw data received:" << data;
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonArray jsonArray = doc.array();

        for (const QJsonValue &value : jsonArray) {
            if (value.isObject()) {
                QJsonObject groupData = value.toObject();

                if (groupData.contains("Назва")) {
                    QString groupName = groupData["Назва"].toString();
                    listGroup.append(groupName);
                } else {
                    qDebug() << "Missing one or more keys in groupData";
                }
            } else {
                qDebug() << "Value is not an object";
            }
        }
        disconnect(dbHandler, &DatabaseHandler::dataReady, this, nullptr);
        loop.quit();
    });

    emit requestDataFromDatabase("Групи");
    loop.exec();

    ui->groupComboBox->addItems(listGroup);
}
