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
    RecordsWindows/gradewindow.cpp \
    RecordsWindows/groupwindow.cpp \
    RecordsWindows/studentwindow.cpp \
    RecordsWindows/subjectwindow.cpp \
    RecordsWindows/teacherwindow.cpp \
    StatisticsWindows/gradestatistics.cpp \
    StatisticsWindows/groupstatistics.cpp \
    StatisticsWindows/studentstatistics.cpp \
    StatisticsWindows/subjectstatistics.cpp \
    StatisticsWindows/teacherstatistics.cpp

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
    RecordsWindows/gradewindow.h \
    RecordsWindows/groupwindow.h \
    RecordsWindows/studentwindow.h \
    RecordsWindows/subjectwindow.h \
    RecordsWindows/teacherwindow.h \
    StatisticsWindows/gradestatistics.h \
    StatisticsWindows/groupstatistics.h \
    StatisticsWindows/studentstatistics.h \
    StatisticsWindows/subjectstatistics.h \
    StatisticsWindows/teacherstatistics.h

FORMS += \
    aboutappwindow.ui \
    appsettingswindow.ui \
    filterwindow.ui \
    loginwindow.ui \
    mainwindow.ui \
    preloader.ui \
    querywindow.ui \
    RecordsWindows/gradewindow.ui \
    RecordsWindows/groupwindow.ui \
    RecordsWindows/studentwindow.ui \
    RecordsWindows/subjectwindow.ui \
    RecordsWindows/teacherwindow.ui \
    StatisticsWindows/gradestatistics.ui \
    StatisticsWindows/groupstatistics.ui \
    StatisticsWindows/studentstatistics.ui \
    StatisticsWindows/subjectstatistics.ui \
    StatisticsWindows/teacherstatistics.ui


TARGET = Gradify

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recources.qrc

ICON = img/AppIcon.icns
