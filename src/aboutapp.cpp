#include "aboutapp.h"
#include "ui_aboutapp.h"

#include <QFile>
#include <QPalette>

aboutApp::aboutApp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aboutApp)
{
    ui->setupUi(this);
    setWindowTitle("Про Gradify");
    setFixedSize(width(), height());
}


aboutApp::~aboutApp()
{
    delete ui;
}


void aboutApp::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::ActivationChange)
    {
        if (not isActiveWindow())
        {
            close();
        }
    }
}


void aboutApp::setBlackUI()
{
    QFile file(":/styles/black/aboutApp/aboutApp.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void aboutApp::setWhiteUI()
{
    QFile file(":/styles/white/aboutApp/aboutApp.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}


void aboutApp::setSystemUI()
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


void aboutApp::setTheme(const QString &style)
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
