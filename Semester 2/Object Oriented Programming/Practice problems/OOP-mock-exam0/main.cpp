#include <QApplication>
#include <QPushButton>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Service serv = Service();
    serv.read_file_issues();
    serv.read_from_users();

    std::vector<GUI*> guis;

    for(auto u:serv.get_users()){
        GUI* g = new GUI{serv};
        guis.push_back(g);
        std::string title = u.get_name() + ' ' + u.get_type();
        g->setWindowTitle(title.c_str());

        g->show();
        g->resize(600, 400);
    }

    QApplication::exec();
    serv.write_file_issues();

    for(auto g: guis)
        delete g;
}
