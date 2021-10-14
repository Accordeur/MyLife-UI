QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../include
LIBS += -L$$PWD/../lib -lgflags -lglog -lcaf_core -lcaf_io -lcaf_openssl
DESTDIR += $$PWD/../bin

CONFIG(debug, debug|release) {
    LIBS += -lgtestd -lgmockd
    DEFINES += ENABLE_TEST
}

DEFINES += ENABLE_CAF



SOURCES += \
    configure/config.cpp \
    configure/config_node_interface.cpp \
    configure/tab_bar_node.cpp \
    configure/view_tree_node.cpp \
    mainwindow/about_dialog.cpp \
    main.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/newfile_dialog.cpp \
    mainwindow/toolbar/setup_workspace.cpp \
    mainwindow/toolbar/tabbar.cpp \
    mainwindow/toolbar/toolbar.cpp \
    mainwindow/view_dock/viewdock.cpp \
    test/config_test.cpp

HEADERS += \
    configure/config.h \
    configure/config_node_interface.h \
    configure/tab_bar_node.h \
    configure/view_tree_node.h \
    mainwindow/about_dialog.h \
    mainwindow/mainwindow.h \
    mainwindow/newfile_dialog.h \
    mainwindow/toolbar/setup_workspace.h \
    mainwindow/toolbar/tabbar.h \
    mainwindow/toolbar/toolbar.h \
    mainwindow/view_dock/viewdock.h

FORMS += \
    mainwindow/about_dialog.ui \
    mainwindow/mainwindow.ui \
    mainwindow/newfile_dialog.ui \
    mainwindow/toolbar/setup_workspace.ui \
    mainwindow/toolbar/toolbar.ui \
    mainwindow/view_dock/viewdock.ui

TRANSLATIONS += \
    MyLife-UI_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
