#include <QApplication>
#include <QPushButton>
#include "gui.h"
#include <assert.h>

void test(){
    Repository r{};
    assert(r.get_questions().size() == 0);
    Question q{15, "ceva", "ana"};
    r.add_question(q);
    assert(r.get_questions().size() == 1);

    Repository rr{};
    Service s{rr};
    assert(s.get_questions().size() == 4);
    s.add_question_serv("ana", "ceva", 19);
    assert(s.get_questions().size() == 5);

    assert(s.get_answers_for_question(19).size() == 0);
    assert(s.get_answers_for_question(15).size() == 1);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    test();
    Repository repo{};
    Service serv{repo};

    std::vector<GUI*> g;

    for(auto u: repo.get_users()){
        GUI* wnd = new GUI{serv};
        g.push_back(wnd);
        std::string title = u.get_name();
        wnd->setWindowTitle(title.c_str());

        wnd->show();
        wnd->resize(600, 400);

    }
    /// for search

    GUI* wnd = new GUI{serv};
    g.push_back(wnd);
    std::string title = "Search Window";
    wnd->setWindowTitle(title.c_str());

    wnd->show();
    wnd->resize(600, 400);

    QApplication::exec();

    for(auto u: g){
        delete u;
    }


}
