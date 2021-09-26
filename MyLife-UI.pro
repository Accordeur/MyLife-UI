QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    mainwindow/about_dialog.cpp \
    main.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/newfile_dialog.cpp \
    mainwindow/toolbar/tabbar.cpp \
    mainwindow/toolbar/toolbar.cpp

HEADERS += \
    mainwindow/about_dialog.h \
    mainwindow/mainwindow.h \
    mainwindow/newfile_dialog.h \
    mainwindow/toolbar/tabbar.h \
    mainwindow/toolbar/toolbar.h

FORMS += \
    mainwindow/about_dialog.ui \
    mainwindow/mainwindow.ui \
    mainwindow/newfile_dialog.ui \
    mainwindow/toolbar/toolbar.ui

TRANSLATIONS += \
    MyLife-UI_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
