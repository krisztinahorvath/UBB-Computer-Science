#include <QApplication>
#include <QPushButton>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Repository repo{};
    Service serv{repo};
    std::vector<GUI*> g;

    GUI* wnd = new GUI{serv};
    g.push_back(wnd);

    std::string title = "Presenter";

    wnd->setWindowTitle(title.c_str());
    wnd->show();
    wnd->resize(600, 400);

    for(auto i: serv.get_participants()){
        GUI* wn = new GUI{serv};
        g.push_back(wn);
        std::string t = i.get_name();

        wn->setWindowTitle(t.c_str());
        wn->show();
        wn->resize(600, 400);
    }
//    std::string title = "Presenter";
//    GUI* wnd = new GUI{serv};
//    wnd->setWindowTitle(title.c_str());
//    wnd->show();
//    wnd->resize(600, 400);
//    g.push_back(wnd);

     QApplication::exec();

     for(auto i: g)
         delete i;

}
