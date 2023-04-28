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
    filterform.cpp \
    main.cpp \
    mainwindow.cpp \
    preloader.cpp \
    queryform.cpp \
    recordsForms/gradewindow.cpp \
    recordsForms/groupwindow.cpp \
    recordsForms/studentwindow.cpp \
    recordsForms/subjectwindow.cpp \
    recordsForms/teacherwindow.cpp

HEADERS += \
    aboutapp.h \
    appsetting.h \
    authorization.h \
    customWidgets/qlineeditwithbutton.h \
    customWidgets/qsearchbar.h \
    filterform.h \
    mainwindow.h \
    preloader.h \
    queryform.h \
    recordsForms/gradewindow.h \
    recordsForms/groupwindow.h \
    recordsForms/studentwindow.h \
    recordsForms/subjectwindow.h \
    recordsForms/teacherwindow.h

FORMS += \
    aboutapp.ui \
    appsetting.ui \
    authorization.ui \
    filterform.ui \
    mainwindow.ui \
    preloader.ui \
    queryform.ui \
    recordsForms/gradewindow.ui \
    recordsForms/groupwindow.ui \
    recordsForms/studentwindow.ui \
    recordsForms/subjectwindow.ui \
    recordsForms/teacherwindow.ui

TARGET = Gradify

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recources.qrc

ICON = img/AppIcon.icns

