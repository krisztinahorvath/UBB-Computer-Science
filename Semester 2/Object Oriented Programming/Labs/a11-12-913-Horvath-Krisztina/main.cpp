//#pragma once

#include "repository.h"
#include "WatchList.h"
#include "CSVWatchList.h"
#include "HTMLWatchList.h"
#include "services.h"
#include "UI.h"

#include <fstream>
#include <QApplication>
#include <QPushButton>
#include <iostream>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QtWidgets/QFormLayout>

#include "gui.h"

int admin_window(int argc, char *argv[]){
    QApplication a(argc, argv);
    QWidget* window = new QWidget{};
    QVBoxLayout* vL = new QVBoxLayout{};
    window->setLayout(vL);

    /// read from file
    QListWidget* admin_repo = new QListWidget{};
    QLabel* admin_repo_label = new QLabel{"Movies: "};
    admin_repo_label->setBuddy(admin_repo); /// todo add label

    std::string line;
    int i = 0; /// todo they are in reverse order at reading
    std::string file_name = R"(C:\Facultate\OOP\a11-12-913-Horvath-Krisztina\repo\movies.csv)";
    std::ifstream f(file_name);
    if(f.is_open()){
        while(std::getline(f, line)){
            QListWidgetItem* movie = new QListWidgetItem(line.c_str());
            QFont font("Consolas", 12, 10, false);
            movie->setFont(font);
            admin_repo->insertItem(i, movie);
        }
    }

    vL->addWidget(admin_repo);


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

    QListWidget* user_repo = new QListWidget{};
    QLabel* user_repo_label = new QLabel{"Movies: "};
    user_repo_label->setBuddy(user_repo); /// todo add label
    vL->addWidget(user_repo);



    window->resize(1200, 1000);
    window->show();
    return QApplication::exec();
}


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository repo;
    repo.read_from_file();
    WatchList* watch;

    Service *serv =  new Service{repo, watch}; /// todo ??

    GUI gui{};
    gui.show();
    gui.resize(600, 400);

    Admin_gui admin{serv};
    admin.show();
    admin.resize(600, 400);

    User_gui user{serv};
    user.show();
    user.resize(600, 400);

    return QApplication::exec();
}
