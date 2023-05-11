#include "gradestatistics.h"
#include "ui_gradestatistics.h"

#include <QFile>
#include <QChart>
#include <QBarSeries>
#include <QChartView>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QMessageBox>
#include <QPieSeries>
#include <QTableView>
#include <QSqlQueryModel>

gradeStatistics::gradeStatistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gradeStatistics)
{
    ui->setupUi(this);

    setWindowTitle("Статистика оцінок");

    series = new QPieSeries();

    chart = new QChart();
    chart->addSeries(series);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(450);

    ui->specialChart->addWidget(chartView);

    ui->categoryComboBox->insertSeparator(1);

    clearTeacherComboBox();
    clearSubjectComboBox();
    clearPieChart();
}

gradeStatistics::~gradeStatistics()
{
    delete ui;
}


void gradeStatistics::setBlackUI()
{
    QFile file(":/styles/black/statisticsForms/statisticsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeDark);
    chartView->chart()->setBackgroundBrush(QColor (49, 51, 52));
}


void gradeStatistics::setWhiteUI()
{
    QFile file(":/styles/white/statisticsForms/statisticsForms.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();

    chartView->chart()->setTheme(QChart::ChartThemeLight);
    chartView->chart()->setBackgroundBrush(QColor (255, 255, 255));
}


void gradeStatistics::setSystemUI()
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


void gradeStatistics::updateTeaceherComboBox()
{
    ui->teacherComboBox->setEnabled(true);

    QStringList teacherList;
    QSqlQueryModel *virualQueryModel = new QSqlQueryModel();
    QTableView *virtualTable = new QTableView();

    virualQueryModel->setQuery("SELECT `Прізвище`, `Ім\'я`, `По батькові`"
                               "FROM `Викладачі`"
                               "WHERE `Викладачі`.`Категорія` = '" + ui->categoryComboBox->currentText() + "'");
    virtualTable->setModel(virualQueryModel);

    for (int row = 0; row < virualQueryModel->rowCount(); ++row)
    {
        teacherList.append(virtualTable->model()->index(row, 0).data().toString() + " "
                           + virtualTable->model()->index(row, 1).data().toString() + " "
                           + virtualTable->model()->index(row, 2).data().toString());
    }

    ui->teacherComboBox->clear();
    ui->teacherComboBox->addItem("Оберіть викладача", 0);
    ui->teacherComboBox->insertSeparator(1);
    ui->teacherComboBox->addItems(teacherList);
}


void gradeStatistics::clearTeacherComboBox()
{
    ui->teacherComboBox->clear();
    ui->teacherComboBox->addItem("Оберіть викладача");
}


void gradeStatistics::clearSubjectComboBox()
{
    ui->subjectComboBox->clear();
    ui->subjectComboBox->addItem("Оберіть предмет");
}


void gradeStatistics::clearPieChart()
{
    series->clear();
    series->append("Приклад", 1);
}


void gradeStatistics::setTheme(const QString &style)
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


void gradeStatistics::on_categoryComboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->teacherComboBox->setEnabled(false);
        ui->subjectComboBox->setEnabled(false);

        clearTeacherComboBox();
        clearSubjectComboBox();
    }
    else if (index > 0)
    {
        updateTeaceherComboBox();
    }
}


void gradeStatistics::on_teacherComboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->subjectComboBox->setEnabled(false);
        clearSubjectComboBox();
    }
    else if (index > 0)
    {
        ui->subjectComboBox->setEnabled(true);

        QStringList subjectList;
        QSqlQueryModel *virualQueryModel = new QSqlQueryModel();
        QTableView *virtualTable = new QTableView();

        virualQueryModel->setQuery("SELECT `Назва`"
                                   "FROM `Предмети`"
                                   "WHERE `Предмети`.`Викладач` = '" + ui->teacherComboBox->currentText() + "'");
        virtualTable->setModel(virualQueryModel);


        if (virualQueryModel->rowCount() == 0)
        {
            ui->subjectComboBox->clear();
            ui->subjectComboBox->addItem("Немає предметів");
        }
        else
        {
            for (int row = 0; row < virualQueryModel->rowCount(); ++row)
            {
                subjectList.append(virtualTable->model()->index(row, 0).data().toString());
            }

            ui->subjectComboBox->clear();
            ui->subjectComboBox->addItem("Оберіть предмет", 0);
            ui->subjectComboBox->insertSeparator(1);
            ui->subjectComboBox->addItems(subjectList);
        }
    }
}


void gradeStatistics::on_subjectComboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        clearPieChart();
    }
    else if (index > 0)
    {
        series->clear();

        QStringList subjectList;
        QSqlQueryModel *virualQueryModel = new QSqlQueryModel(this);
        QTableView *virtualTable = new QTableView(this);

        for (int i = 2; i <= 5; i++)
        {
            virualQueryModel->setQuery("SELECT COUNT(`Оцінка`)"
                                       "FROM `Оцінки`"
                                       "WHERE `Оцінки`.`Предмет` = '" + ui->subjectComboBox->currentText() + "'"
                                         "AND `Оцінки`.`Оцінка` = '" + QString::number(i) + "'"
                                       "GROUP BY `Оцінки`.`Оцінка`");
            virtualTable->setModel(virualQueryModel);

            switch (i)
            {
            case 2:
                series->append("Незадовільно", virtualTable->model()->index(0, 0).data().toInt());
                break;
            case 3:
                series->append("Задовільно", virtualTable->model()->index(0, 0).data().toInt());
                break;
            case 4:
                series->append("Добре", virtualTable->model()->index(0, 0).data().toInt());
                break;
            case 5:
                series->append("Відмінно", virtualTable->model()->index(0, 0).data().toInt());
                break;
            }
        }
    }
}

