#include <string>
#include <iostream>
#include <chrono>
#include <thread>

#ifdef ENABLE_CAF

#include "caf/all.hpp"
#include "caf/io/all.hpp"

#endif

#include "mainwindow/mainwindow.h"
#include <QApplication>

int qt_main(int argc, char* argv[]) {
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);


    QApplication a(argc, argv);
    QFont font;
    font.setPointSize(9);
    font.setFamily("Microsoft YaHei UI");
    a.setFont(font);

    MainWindow w;
    w.show();
    //w.printChild(&w);
    return a.exec();
}

#ifdef ENABLE_CAF
using namespace caf;

behavior mirror(event_based_actor* self) {
    // return the (initial) actor behavior
    return {
            // a handler for messages containing a single string
            // that replies with a string
            [=](const std::string& what) -> std::string {
                // prints "Hello World!" via aout (thread-safe cout wrapper)
                aout(self) << what << std::endl;
                // reply "!dlroW olleH"
                return std::string{what.rbegin(), what.rend()};
            },
    };
}

void hello_world(event_based_actor* self, const actor& buddy) {
    // send "Hello World!" to our buddy ...
    self->request(buddy, std::chrono::seconds(10), "Hello World!")
            .then(
                    // ... wait up to 10s for a response ...
                    [=](const std::string& what) {
                        // ... and print it
                        aout(self) << what << std::endl;
                    });
    aout(self) << "Fuck" << std::endl;
}

int caf_main(actor_system& sys, const actor_system_config& cfg) {
    // create a new actor that calls 'mirror()'
    auto mirror_actor = sys.spawn(mirror);
    // create another actor that calls 'hello_world(mirror_actor)';
    sys.spawn(hello_world, mirror_actor);


    // Qt main source
    auto [argc, argv] = cfg.c_args_remainder();
    return qt_main(argc, argv);
}


// creates a main function for us that calls our caf_main
CAF_MAIN()

#else

int main(int argc, char *argv[])
{
    return qt_main(argc, argv);
}
#endif
