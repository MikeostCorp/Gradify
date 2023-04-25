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

DISTFILES += \
    img/whiteMenuIcon/okayIndicator.png \
    styles/black/aboutApp/aboutApp.qss \
    styles/black/appSetting/appSetting.qss \
    styles/black/authorization/authorization.qss \
    styles/black/editForms/editForms.qss \
    styles/black/mainWindow/mainWindow.qss \
    styles/black/mainWindow/outLoginButton.qss \
    styles/black/mainWindow/selectButtonTableStyle.qss \
    styles/other/preloader/preloader.qss \
    styles/white/aboutApp/aboutApp.qss \
    styles/white/appSetting/appSetting.qss \
    styles/white/authorization/authorization.qss \
    styles/white/editForms/editForms.qss \
    styles/white/mainWindow/mainWindow.qss \
    styles/white/mainWindow/outLoginButton.qss \
    styles/white/mainWindow/selectButtonTableStyle.qss
