QT       += core gui multimedia multimediawidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appsetting.cpp \
    authorization.cpp \
    filterform.cpp \
    main.cpp \
    mainwindow.cpp \
    preloader.cpp \
    queryform.cpp

HEADERS += \
    appsetting.h \
    authorization.h \
    filterform.h \
    mainwindow.h \
    preloader.h \
    queryform.h

FORMS += \
    appsetting.ui \
    authorization.ui \
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
