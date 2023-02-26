#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeEvent(QEvent *event) override;

private slots:
    void on_firstTableButton_clicked();

    void on_secondTableButton_clicked();

    void on_thirdTableButton_clicked();

    void clearStyleButtonTable();

    void on_fourthTableButton_clicked();

private:
    Ui::MainWindow *ui;

    bool appThemeStyle; // if false - dark, true - white;

    QString defaultButtonTableStyle;
    QString selectButtonTableStyle;


};
#endif // MAINWINDOW_H
