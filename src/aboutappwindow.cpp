#include "aboutappwindow.h"
#include "ui_aboutappwindow.h"

#include <QFile>
#include <QPalette>

AboutAppWindow::AboutAppWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AboutAppWindow)
{
    ui->setupUi(this);
    setWindowTitle("Про Gradify");
    setFixedSize(width(), height());
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

AboutAppWindow::~AboutAppWindow()
{
    delete ui;
}

void AboutAppWindow::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::ActivationChange) {
        if (not isActiveWindow()) {
            close();
        }
    }
}

void AboutAppWindow::setBlackUI()
{
    QFile file(":/styles/black/AboutAppWindow/AboutAppWindow.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}

void AboutAppWindow::setWhiteUI()
{
    QFile file(":/styles/white/AboutAppWindow/AboutAppWindow.qss");
    file.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(file.readAll()));
    file.close();
}

void AboutAppWindow::setSystemUI()
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

void AboutAppWindow::setTheme(const QString &style)
{
    if (style == "black") {
        setBlackUI();
    } else if (style == "white") {
        setWhiteUI();
    } else {
        setSystemUI();
    }
}
