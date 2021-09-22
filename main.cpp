#include "mainwindow/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);
    QFont font;
    font.setPointSize(9);
    font.setFamily("Microsoft YaHei UI");
    a.setFont(font);

    MainWindow w;
    w.show();
    return a.exec();
}
