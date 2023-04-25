QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutapp.cpp \
    appsetting.cpp \
    authorization.cpp \
    customWidgets/qlineeditwithbutton.cpp \
    customWidgets/qsearchbar.cpp \
    editForms/editgrade.cpp \
    editForms/editgroup.cpp \
    editForms/editstudent.cpp \
    editForms/editsubject.cpp \
    editForms/editteacher.cpp \
    filterform.cpp \
    main.cpp \
    mainwindow.cpp \
    preloader.cpp \
    queryform.cpp

HEADERS += \
    aboutapp.h \
    appsetting.h \
    authorization.h \
    customWidgets/qlineeditwithbutton.h \
    customWidgets/qsearchbar.h \
    editForms/editgrade.h \
    editForms/editgroup.h \
    editForms/editstudent.h \
    editForms/editsubject.h \
    editForms/editteacher.h \
    filterform.h \
    mainwindow.h \
    preloader.h \
    queryform.h

FORMS += \
    aboutapp.ui \
    appsetting.ui \
    authorization.ui \
    editForms/editgrade.ui \
    editForms/editgroup.ui \
    editForms/editstudent.ui \
    editForms/editsubject.ui \
    editForms/editteacher.ui \
    filterform.ui \
    mainwindow.ui \
    preloader.ui \
    queryform.ui

TARGET = Gradify

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recources.qrc

ICON = img/AppIcon.icns

