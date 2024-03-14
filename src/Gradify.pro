QT       += core gui printsupport charts network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 app_bundle

QMAKE_CXXFLAGS += -pedantic -Wextra -Wall

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DatabaseHandler/databasehandler.cpp \
    aboutappwindow.cpp \
    appsettingswindow.cpp \
    customWidgets/qlineeditwithbutton.cpp \
    customWidgets/qsearchbar.cpp \
    filterwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    preloader.cpp \
    querywindow.cpp \
    recordsForms/gradewindow.cpp \
    recordsForms/groupwindow.cpp \
    recordsForms/studentwindow.cpp \
    recordsForms/subjectwindow.cpp \
    recordsForms/teacherwindow.cpp \
    statisticsForms/gradestatistics.cpp \
    statisticsForms/groupstatistics.cpp \
    statisticsForms/studentstatistics.cpp \
    statisticsForms/subjectstatistics.cpp \
    statisticsForms/teacherstatistics.cpp

HEADERS += \
    DatabaseHandler/databasehandler.h \
    aboutappwindow.h \
    appsettingswindow.h \
    customWidgets/qlineeditwithbutton.h \
    customWidgets/qsearchbar.h \
    filterwindow.h \
    loginwindow.h \
    mainwindow.h \
    preloader.h \
    querywindow.h \
    recordsForms/gradewindow.h \
    recordsForms/groupwindow.h \
    recordsForms/studentwindow.h \
    recordsForms/subjectwindow.h \
    recordsForms/teacherwindow.h \
    statisticsForms/gradestatistics.h \
    statisticsForms/groupstatistics.h \
    statisticsForms/studentstatistics.h \
    statisticsForms/subjectstatistics.h \
    statisticsForms/teacherstatistics.h

FORMS += \
    aboutappwindow.ui \
    appsettingswindow.ui \
    filterwindow.ui \
    loginwindow.ui \
    mainwindow.ui \
    preloader.ui \
    querywindow.ui \
    recordsForms/gradewindow.ui \
    recordsForms/groupwindow.ui \
    recordsForms/studentwindow.ui \
    recordsForms/subjectwindow.ui \
    recordsForms/teacherwindow.ui \
    statisticsForms/gradestatistics.ui \
    statisticsForms/groupstatistics.ui \
    statisticsForms/studentstatistics.ui \
    statisticsForms/subjectstatistics.ui \
    statisticsForms/teacherstatistics.ui


TARGET = Gradify

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recources.qrc

ICON = img/AppIcon.icns
