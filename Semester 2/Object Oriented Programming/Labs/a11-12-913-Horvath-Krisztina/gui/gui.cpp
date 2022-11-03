#include <QFormLayout>
#include "gui.h"
#include "CSVWatchList.h"
#include "HTMLWatchList.h"

GUI::GUI(Service *sr): serv(sr){
    this->setup_gui();
    admin_repo = new Repository();
    admin_repo->read_from_file();
    this->connect_signals_slots();


}

GUI::~GUI() {

}

void GUI::setup_gui() {
    QVBoxLayout* vL = new QVBoxLayout{};
    this->setLayout(vL);

    QLabel *mode_label = new QLabel{};
    QLabel *file_label = new QLabel{};
    QPushButton *admin_btn = new QPushButton{};
    QPushButton *user_btn = new QPushButton{};
    QRadioButton *csv_btn = new QRadioButton{};
    QRadioButton *html_btn = new QRadioButton{};

    mode_label->setText("Choose mode: ");
    admin_btn->setText("admin");
    mode_label->setBuddy(admin_btn);
    vL->addWidget(mode_label);
    vL->addWidget(admin_btn);
    user_btn->setText("user");
    vL->addWidget(user_btn);

    file_label->setText("Choose file_type: ");
    file_label->setBuddy(csv_btn);
    csv_btn->setText("csv");
    html_btn->setText("html");
    vL->addWidget(file_label);
    vL->addWidget(csv_btn);
    vL->addWidget(html_btn);

}

void GUI::connect_signals_slots() {
//    QObject::connect(this->admin_btn, SIGNAL(clicked()), this, SLOT(admin_form()));
//    QObject::connect(this->user_btn, SIGNAL(clicked()), this, SLOT(user_form()));
}

void GUI::admin_mode() {
//    WatchList *user_repo = nullptr;
//    if(this->csv_btn->isChecked())
//        user_repo = new CSVWatchlist();
//    if(this->html_btn->isChecked())
//        user_repo = new HTMLWatchList();
//
//    admin_repo->read_from_file();
//    this->serv = new Service{*admin_repo, user_repo};
//    AdminForm* a = new AdminForm{this->serv, admin_repo};
//    a->show();
//    a->resize(600, 400);
}

void GUI::user_mode() {
    WatchList *user_repo = nullptr;
    admin_repo->read_from_file();
    this->serv = new Service{*admin_repo, user_repo};

//    UserForm* u = new UserForm{this->serv, user_repo};
//    u->show();
//    u->resize(600, 400);
}

GUI::GUI() {
    this->setup_gui();
}

void Admin_gui::setup_gui() {

    QVBoxLayout* vL = new QVBoxLayout{};
    this->setLayout(vL);

    /// read from file
    QListWidget* admin_repo = new QListWidget{};
    QLabel* admin_repo_label = new QLabel{"Movies: "};
    admin_repo_label->setBuddy(admin_repo); /// todo add label

    QFormLayout* form_layout = new QFormLayout{};

    /// create labels and textboxes
    this->title = new QLineEdit{};
    QLabel* title_label = new QLabel{"&Title: "};
    title_label->setBuddy(title);
    form_layout->addRow(title_label, title);

    QLineEdit* genre_text_box = new QLineEdit{};
    QLabel* genre_label = new QLabel{"&Genre: "};
    genre_label->setBuddy(genre_text_box);
    form_layout->addRow(genre_label, genre_text_box);

    QLineEdit* year_text_box = new QLineEdit{};
    QLabel* year_label = new QLabel{"Year: "}; /// todo &Year??
    genre_label->setBuddy(year_text_box);
    form_layout->addRow(year_label, year_text_box);

    QLineEdit* likes_text_box = new QLineEdit{};
    QLabel* likes_label = new QLabel{"&Likes: "};
    likes_label->setBuddy(likes_text_box);
    form_layout->addRow(likes_label, likes_text_box);

    QLineEdit* trailer_text_box = new QLineEdit{};
    QLabel* trailer_label = new QLabel{"&Trailer: "};
    trailer_label->setBuddy(trailer_text_box);
    form_layout->addRow(trailer_label, trailer_text_box);

    vL->addLayout(form_layout);

    QWidget* actions = new QWidget{};
    QHBoxLayout* hL = new QHBoxLayout{};
    QPushButton* add_movie = new QPushButton{ "&Add" };
    QPushButton* delete_movie = new QPushButton{ "&Delete" };
    QPushButton* update_movie = new QPushButton{ "&Update" };
    QPushButton* filter_movie = new QPushButton{ "&Filter" };

    hL->addWidget(add_movie);
    hL->addWidget(delete_movie);
    hL->addWidget(update_movie);
    hL->addWidget(filter_movie);
    actions->setLayout(hL);

    /// add the actions widget to the window
    vL->addWidget(actions);

    user_repo = new QListWidget{};
    QLabel* user_repo_label = new QLabel{"Movies: "};
    user_repo_label->setBuddy(user_repo); /// todo add label
    vL->addWidget(user_repo);
    QObject::connect(title, &QLineEdit::textChanged, this, &Admin_gui::filter);

}

void Admin_gui::connect_signals_slots() {

}

void Admin_gui::filter() {
    std::string t = title->text().toStdString();
    std::vector<Movie> movies = this->serv->get_all_movies();
    this->user_repo->clear();
    if(t.empty())
        this->populate_list();
    for(auto m: movies)
        if(m.get_title() == t)
            this->user_repo->addItem(QString::fromStdString(m.get_title() + " - " + m.get_genre() + " - " +
                                                            std::to_string(m.get_year()) + " - " + std::to_string(m.get_likes()) + " - " + m.get_trailer()));

}

Admin_gui::Admin_gui(Service* s): serv(s) {
    user_repo = new QListWidget{};
    this->setup_gui();
    this->populate_list();
}

void Admin_gui::populate_list() {
    this->user_repo->clear();
    std::vector<Movie> movies = this->serv->get_all_movies();
    for(auto& m: movies)
        this->user_repo->addItem(QString::fromStdString(m.get_title() + " - " + m.get_genre() + " - " +
                                                             std::to_string(m.get_year()) + " - " + std::to_string(m.get_likes()) + " - " + m.get_trailer()));
}

Admin_gui::~Admin_gui() = default;

void User_gui::setup_gui() {
    QVBoxLayout* vL = new QVBoxLayout{};
    this->setLayout(vL);

    /// read from file
    QListWidget* admin_repo = new QListWidget{};
    QLabel* admin_repo_label = new QLabel{"Movies: "};
    admin_repo_label->setBuddy(admin_repo); /// todo add label

    QFormLayout* form_layout = new QFormLayout{};

    /// create labels and textboxes
    QLineEdit* title_text_box = new QLineEdit{};
    QLabel* title_label = new QLabel{"&Title: "};
    title_label->setBuddy(title_text_box);
    form_layout->addRow(title_label, title_text_box);

    QLineEdit* genre_text_box = new QLineEdit{};
    QLabel* genre_label = new QLabel{"&Genre: "};
    genre_label->setBuddy(genre_text_box);
    form_layout->addRow(genre_label, genre_text_box);

    QLineEdit* year_text_box = new QLineEdit{};
    QLabel* year_label = new QLabel{"Year: "}; /// todo &Year??
    genre_label->setBuddy(year_text_box);
    form_layout->addRow(year_label, year_text_box);

    vL->addLayout(form_layout);

    QWidget* actions = new QWidget{};
    QHBoxLayout* hL = new QHBoxLayout{};
    QPushButton* add_movie = new QPushButton{ "&Add" };
    QPushButton* delete_movie = new QPushButton{ "&Delete" };
    QPushButton* watchlist_movie = new QPushButton{"&WatchList" };
    QPushButton* next_movie = new QPushButton{"&Next" };
    QPushButton* open_movie = new QPushButton{"&Open"};

    hL->addWidget(add_movie);
    hL->addWidget(delete_movie);
    hL->addWidget(watchlist_movie);
    hL->addWidget(next_movie);
    hL->addWidget(open_movie);
    actions->setLayout(hL);

    /// add the actions widget to the window
    vL->addWidget(actions);

    QListWidget* user_repo = new QListWidget{};
    QLabel* user_repo_label = new QLabel{"Movies: "};
    user_repo_label->setBuddy(user_repo); /// todo add label
    vL->addWidget(user_repo);
}

User_gui::~User_gui() {

}

User_gui::User_gui(Service *serv): serv(serv) {
    this->setup_gui();
}
