#include <QApplication>
#include <QPushButton>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Service serv;
    serv.read_from_file();

    GUI gui{serv};
    gui.show();
    gui.resize(600, 400);
    
    return QApplication::exec();
}
