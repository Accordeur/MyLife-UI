QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    new_file/newfile_dialog.cpp

HEADERS += \
    about_dialog.h \
    mainwindow.h \
    new_file/newfile_dialog.h

FORMS += \
    about_dialog.ui \
    mainwindow.ui \
    new_file/newfile_dialog.ui

TRANSLATIONS += \
    MyLife-UI_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
