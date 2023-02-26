/********************************************************************************
** Form generated from reading UI file 'preloader.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRELOADER_H
#define UI_PRELOADER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_preloader
{
public:

    void setupUi(QWidget *preloader)
    {
        if (preloader->objectName().isEmpty())
            preloader->setObjectName("preloader");
        preloader->resize(400, 400);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/appIcon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        preloader->setWindowIcon(icon);

        retranslateUi(preloader);

        QMetaObject::connectSlotsByName(preloader);
    } // setupUi

    void retranslateUi(QWidget *preloader)
    {
        preloader->setWindowTitle(QCoreApplication::translate("preloader", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class preloader: public Ui_preloader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRELOADER_H
