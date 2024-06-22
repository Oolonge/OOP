#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a1(argc, argv);
    // boost::asio::io_context io;
    // Cabin cabin(io);
    // cabin.move();
    // Doors door(io);
    // door.startOpening();
    // sleep(1);
    // door.startClosing();
    // sleep(1);
    // door.startOpening();
    // cout << "finished..." << endl;
    // io.run();

    MainWindow w;
    w.show();
    return a1.exec();
}
