/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *leftMenuFrame;
    QVBoxLayout *verticalLayout_2;
    QFrame *upMenuFrame;
    QLabel *mainLogoImg;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *thirdTableButton;
    QLabel *label_2;
    QLabel *mainMenuLebel;
    QLabel *label;
    QPushButton *firstTableButton;
    QPushButton *secondTableButton;
    QPushButton *fourthTableButton;
    QSpacerItem *verticalMenuSpacer_2;
    QPushButton *settingButton;
    QSpacerItem *verticalMenuSpacer;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 600);
        MainWindow->setMinimumSize(QSize(1000, 600));
        MainWindow->setStyleSheet(QString::fromUtf8("MainWindow\n"
"{\n"
"background-color: rgb(29, 31, 32);\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setLayoutDirection(Qt::LeftToRight);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        leftMenuFrame = new QFrame(centralwidget);
        leftMenuFrame->setObjectName(QString::fromUtf8("leftMenuFrame"));
        leftMenuFrame->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(leftMenuFrame->sizePolicy().hasHeightForWidth());
        leftMenuFrame->setSizePolicy(sizePolicy);
        leftMenuFrame->setMinimumSize(QSize(210, 570));
        leftMenuFrame->setMaximumSize(QSize(210, 9999));
        leftMenuFrame->setAutoFillBackground(false);
        leftMenuFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(41,45,48);"));
        leftMenuFrame->setFrameShape(QFrame::StyledPanel);
        leftMenuFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(leftMenuFrame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        upMenuFrame = new QFrame(leftMenuFrame);
        upMenuFrame->setObjectName(QString::fromUtf8("upMenuFrame"));
        upMenuFrame->setStyleSheet(QString::fromUtf8("border: 0px"));
        upMenuFrame->setFrameShape(QFrame::StyledPanel);
        upMenuFrame->setFrameShadow(QFrame::Raised);
        mainLogoImg = new QLabel(upMenuFrame);
        mainLogoImg->setObjectName(QString::fromUtf8("mainLogoImg"));
        mainLogoImg->setGeometry(QRect(20, 20, 45, 45));
        pushButton_4 = new QPushButton(upMenuFrame);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(15, 262, 180, 29));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy1);
        pushButton_4->setMinimumSize(QSize(180, 29));
        pushButton_4->setMaximumSize(QSize(180, 29));
        pushButton_4->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    border-radius:  6px;\n"
"    background-color:  rgb(41,45,48);\n"
"    color:  rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color:  rgb(98, 98, 98);\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_4->setIcon(icon);
        pushButton_4->setAutoRepeatDelay(300);
        pushButton_5 = new QPushButton(upMenuFrame);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(15, 320, 180, 29));
        sizePolicy1.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy1);
        pushButton_5->setMinimumSize(QSize(180, 29));
        pushButton_5->setMaximumSize(QSize(180, 29));
        pushButton_5->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    border-radius:  6px;\n"
"    background-color:  rgb(41,45,48);\n"
"    color:  rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color:  rgb(98, 98, 98);\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/3.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon1);
        pushButton_6 = new QPushButton(upMenuFrame);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(15, 291, 180, 29));
        sizePolicy1.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy1);
        pushButton_6->setMinimumSize(QSize(180, 29));
        pushButton_6->setMaximumSize(QSize(180, 29));
        pushButton_6->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    border-radius:  6px;\n"
"    background-color:  rgb(41,45,48);\n"
"    color:  rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color:  rgb(98, 98, 98);\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_6->setIcon(icon2);
        thirdTableButton = new QPushButton(upMenuFrame);
        thirdTableButton->setObjectName(QString::fromUtf8("thirdTableButton"));
        thirdTableButton->setGeometry(QRect(15, 172, 180, 29));
        sizePolicy1.setHeightForWidth(thirdTableButton->sizePolicy().hasHeightForWidth());
        thirdTableButton->setSizePolicy(sizePolicy1);
        thirdTableButton->setMinimumSize(QSize(180, 29));
        thirdTableButton->setMaximumSize(QSize(180, 29));
        thirdTableButton->setCursor(QCursor(Qt::PointingHandCursor));
        thirdTableButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    border-radius:  6px;\n"
"    background-color:  rgb(41,45,48);\n"
"    color:  rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color:  rgb(98, 98, 98);\n"
"}"));
        thirdTableButton->setIcon(icon2);
        label_2 = new QLabel(upMenuFrame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(15, 242, 51, 16));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setStyleSheet(QString::fromUtf8(""));
        mainMenuLebel = new QLabel(upMenuFrame);
        mainMenuLebel->setObjectName(QString::fromUtf8("mainMenuLebel"));
        mainMenuLebel->setGeometry(QRect(80, 20, 111, 51));
        label = new QLabel(upMenuFrame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(15, 94, 51, 16));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setStyleSheet(QString::fromUtf8(""));
        firstTableButton = new QPushButton(upMenuFrame);
        firstTableButton->setObjectName(QString::fromUtf8("firstTableButton"));
        firstTableButton->setGeometry(QRect(15, 114, 180, 29));
        sizePolicy1.setHeightForWidth(firstTableButton->sizePolicy().hasHeightForWidth());
        firstTableButton->setSizePolicy(sizePolicy1);
        firstTableButton->setMinimumSize(QSize(180, 29));
        firstTableButton->setMaximumSize(QSize(180, 29));
        firstTableButton->setCursor(QCursor(Qt::PointingHandCursor));
        firstTableButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    border-radius:  6px;\n"
"    background-color:  rgb(41,45,48);\n"
"    color:  rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color:  rgb(98, 98, 98);\n"
"}"));
        firstTableButton->setIcon(icon);
        firstTableButton->setAutoRepeatDelay(300);
        secondTableButton = new QPushButton(upMenuFrame);
        secondTableButton->setObjectName(QString::fromUtf8("secondTableButton"));
        secondTableButton->setGeometry(QRect(15, 143, 180, 29));
        sizePolicy1.setHeightForWidth(secondTableButton->sizePolicy().hasHeightForWidth());
        secondTableButton->setSizePolicy(sizePolicy1);
        secondTableButton->setMinimumSize(QSize(180, 29));
        secondTableButton->setMaximumSize(QSize(180, 29));
        secondTableButton->setCursor(QCursor(Qt::PointingHandCursor));
        secondTableButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    border-radius:  6px;\n"
"    background-color:  rgb(41,45,48);\n"
"    color:  rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color:  rgb(98, 98, 98);\n"
"}"));
        secondTableButton->setIcon(icon2);
        fourthTableButton = new QPushButton(upMenuFrame);
        fourthTableButton->setObjectName(QString::fromUtf8("fourthTableButton"));
        fourthTableButton->setGeometry(QRect(15, 201, 180, 29));
        sizePolicy1.setHeightForWidth(fourthTableButton->sizePolicy().hasHeightForWidth());
        fourthTableButton->setSizePolicy(sizePolicy1);
        fourthTableButton->setMinimumSize(QSize(180, 29));
        fourthTableButton->setMaximumSize(QSize(180, 29));
        fourthTableButton->setCursor(QCursor(Qt::PointingHandCursor));
        fourthTableButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    border-radius:  6px;\n"
"    background-color:  rgb(41,45,48);\n"
"    color:  rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color:  rgb(98, 98, 98);\n"
"}"));
        fourthTableButton->setIcon(icon2);

        verticalLayout_2->addWidget(upMenuFrame);

        verticalMenuSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalMenuSpacer_2);

        settingButton = new QPushButton(leftMenuFrame);
        settingButton->setObjectName(QString::fromUtf8("settingButton"));
        settingButton->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(settingButton->sizePolicy().hasHeightForWidth());
        settingButton->setSizePolicy(sizePolicy3);
        settingButton->setCursor(QCursor(Qt::PointingHandCursor));
        settingButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    border-radius:  6px;\n"
"    background-color:  rgb(41,45,48);\n"
"    color:  rgb(255, 255, 255);\n"
"}\n"
""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/pinkMenuicon/settinfIco.png"), QSize(), QIcon::Normal, QIcon::Off);
        settingButton->setIcon(icon3);
        settingButton->setIconSize(QSize(25, 25));

        verticalLayout_2->addWidget(settingButton);

        verticalMenuSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalMenuSpacer);


        horizontalLayout->addWidget(leftMenuFrame);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(3, 20, 20, 20);
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(710, 0));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(41,45,48);\n"
"border-radius: 16px; "));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(1);
        sizePolicy4.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy4);
        label_6->setStyleSheet(QString::fromUtf8("border-radius:  6px;\n"
"background-color: rgb(61,65,68);"));

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(5);
        sizePolicy5.setVerticalStretch(5);
        sizePolicy5.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy5);
        label_7->setStyleSheet(QString::fromUtf8("border-radius:  6px;\n"
"background-color:  rgb(255,255,255);"));

        verticalLayout->addWidget(label_7);


        horizontalLayout_3->addWidget(frame_2);


        horizontalLayout->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        mainLogoImg->setText(QString());
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "  \320\237\320\276 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\320\260\320\274             ", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "  \320\237\320\276 \320\276\321\206\321\226\320\275\320\272\320\260\320\274                   ", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "  \320\237\320\276 \320\262\320\270\320\272\320\273\320\260\320\264\320\260\321\207\320\260\320\274           ", nullptr));
        thirdTableButton->setText(QCoreApplication::translate("MainWindow", "  \320\236\321\206\321\226\320\275\320\272\320\270                          ", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600; color:#989898;\">\320\227\320\262\321\226\321\202\320\270</span></p></body></html>", nullptr));
        mainMenuLebel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700;\">Data Base<br/></span><span style=\" font-size:12pt;\">\320\235\321\203\320\266\320\275\320\276 \321\204\320\270\320\272\321\201\320\260\320\275\321\203\321\202\321\214<br/>\320\272\320\260\321\207\320\265\321\201\321\202\320\262\320\276 \320\273\320\276\320\263\320\276</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600; color:#989898;\">\320\242\320\260\320\261\320\273\320\270\321\206\321\226</span></p></body></html>", nullptr));
        firstTableButton->setText(QCoreApplication::translate("MainWindow", "  \320\241\321\202\321\203\320\264\320\265\320\275\321\202\320\270                     ", nullptr));
        secondTableButton->setText(QCoreApplication::translate("MainWindow", "  \320\222\320\270\320\272\320\273\320\260\320\264\320\260\321\207\321\226                     ", nullptr));
        fourthTableButton->setText(QCoreApplication::translate("MainWindow", "  \320\223\321\200\321\203\320\277\320\270                             ", nullptr));
        settingButton->setText(QCoreApplication::translate("MainWindow", "  \320\235\320\260\320\273\320\260\321\210\321\202\321\203\320\262\320\260\320\275\320\275\321\217          ", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">\320\242\321\203\321\202 \321\204\320\270\320\273\321\214\321\202\321\200\321\213 \320\273\320\270\320\261\320\276 \320\265\321\211\321\221 \320\272\320\260\320\272\320\260\321\217-\321\202\320\276 \320\270\320\275\321\204\320\260<br/>\320\272\320\275\320\276\320\277\320\272\320\260 \320\264\320\273\321\217 \320\276\321\202\320\272\321\200\321\213\321\202\320\270\321\217 \320\276\321\202\320\264\320\265\320\273\321\214\320\275\320\276\320\271 \321\204\320\276\321\200\320\274\321\213 \320\264\320\273\321\217 \321\200\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\275\320\270\321\217 \320\276\321\202\320\264\320\265\320\273\321\214\320\275\320\276\320\271 \320\267\320\260\320\277\320\270\321\201\320\270<br/>\321\206\320\262\320\265\321\202 \320\274\320\276\320\266\320\275\320\276 \320\277\320\276\321\201\321\202\320\260\320\262\320\270\321\202\321\214 \320\272\320\260\320\272 \321\203 \321\204\321\200\320\265\320\271\320\274\320\260"
                        " </p><p align=\"center\">\320\234\320\225\320\235\320\257\320\225\320\242\320\241\320\257 \320\240\320\220\320\227\320\234\320\225\320\240 \320\234\320\225\320\224\320\233\320\225\320\235\320\225\320\225 \320\247\320\225\320\234 \320\243 \320\242\320\220\320\221\320\233\320\230\320\246\320\253</p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" color:#111111;\">\320\241\320\260\320\274\320\260 \321\202\320\260\320\261\320\273\320\270\321\206\320\260 (\320\261\321\213\320\273\320\276 \320\261\321\213 \320\272\321\200\321\203\321\202\320\276 \320\265\321\221 \320\267\320\260\320\264\320\270\320\267\320\260\320\271\320\275\320\270\321\202\321\214)</span></p><p align=\"center\"><span style=\" color:#111111;\">\320\234\320\225\320\235\320\257\320\225\320\242\320\241\320\257 \320\240\320\220\320\227\320\234\320\225\320\240 \320\221\320\253\320\241\320\242\320\240\320\225\320\225 \320\222\320\253\320\250\320\225</span></p><p align=\"center\"><span style=\" color:#111111;\">background-color: rgb(61,65,68); \320\275\320\260 \321\204\320\276\320\275 \320\261\321\213</span></p><p align=\"center\"><span style=\" color:#111111;\">ds</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
