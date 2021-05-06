QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    central_widget/centraldelegate.cpp \
    central_widget/centralmodel.cpp \
    central_widget/centralwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    new_file/newfile.cpp

HEADERS += \
    about.h \
    central_widget/centraldelegate.h \
    central_widget/centralmodel.h \
    central_widget/centralwidget.h \
    mainwindow.h \
    new_file/newfile.h

FORMS += \
    about.ui \
    central_widget/centralwidget.ui \
    mainwindow.ui \
    new_file/newfile.ui

TRANSLATIONS += \
    MyLife-UI_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
