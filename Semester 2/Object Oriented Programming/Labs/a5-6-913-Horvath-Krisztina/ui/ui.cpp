#include "ui.h"
#include <string>
#include <iostream>

void UI::start() {
    while(true)
    {
        print_menu();
        std::string cmd;
        std::getline(std::cin, cmd);
        if(cmd == "exit")
            break;

        if(cmd == "admin") {
            admin_mode();
            continue;
        }

        if(cmd == "user"){
            user_mode();
            continue;
        }

        std::cout << "Invalid command!\n";
    }
}

void UI::admin_mode() {
    while(true){
        print_menu_admin();
        std::string cmd;
        std::getline(std::cin, cmd);

        if(cmd == "exit")
            break;

        if(cmd == "add"){
            add_movie_ui();
            std::cout << "\n";
            continue;
        }

        if(cmd == "delete"){
            remove_movie_ui();
            std::cout << '\n';
            continue;
        }

        if(cmd == "update"){
            update_movie_ui();
            std::cout << "\n";
            continue;
        }

        if(cmd == "list"){
            list_movies();
            std::cout << "\n";
            continue;
        }

        std::cout << "Invalid command!\n\n";
    }
}

void UI::user_mode() {
    while(true){
        print_menu_user();
        std::string cmd;
        std::getline(std::cin, cmd);

        if(cmd == "exit")
            break;

        if(cmd == "list"){
            display_by_genre_ui();
            continue;
        }

        if(cmd == "delete"){
            delete_from_watchlist_ui();
            continue;
        }

        if(cmd == "watchlist"){
            list_watchlist_all();
            continue;
        }

        std::cout << " Invalid command!\n\n";

    }
}

void UI::print_menu() {
    std::cout << "Please select mode: admin/user\n";
    std::cout << "Mode: ";
}

void UI::print_menu_admin() {
    std::cout << "\nWhat would you like to do?\n";
    std::cout << "   add     - to add a movie to the database\n";
    std::cout << "   delete  - to delete a movie from the database\n";
    std::cout << "   update  - update a movie in the database\n";
    std::cout << "   list    - list all movies from the database\n";
    std::cout << "   exit\n";
    std::cout << "Option: ";
}

void UI::print_menu_user() {
    std::cout << "\nWhat would you like to do?\n";
    std::cout << "   list      - list movies with a certain genre\n";
    std::cout << "   delete    - delete a movie from the watchlist\n";
    std::cout << "   watchlist - list the watchlist\n";
    std::cout << "   exit\n";
    std::cout << "Option: ";

}

void UI::print_watchlist_menu(){
    std::cout << "\n******************Watching movie trailers******************";
    std::cout << "\nWhat would you like to do?\n";
    std::cout << "   add    - to add movie to watchlist\n";
    std::cout << "   next   - next movie form the list\n";
    std::cout << "   exit\n";
    std::cout << "Option: ";
}

void UI::list_movies() {
    DynamicVector<Movie> l = this->serv.get_all_movies();
    Movie m;
    for(int i = 0; i < l.get_size(); i++){
        m = l.get_elem(i);
        std::cout << i <<" Movie with title: " << m.get_title() << ", genre: " << m.get_genre() << ", year:" << m.get_year() << ", likes: " << m.get_likes() << ", trailer: " << m.get_trailer()<<"\n";
    }
}

void UI::add_movie_ui() {
    std::string title, genre, year, likes, trailer;
    std::cout << "Title: ";
    std::getline(std::cin, title);
    std::cout << "Genre: ";
    std::getline(std::cin, genre);
    std::cout << "Year: ";
    std::getline(std::cin, year);
    std::cout << "Likes: ";
    std::getline(std::cin, likes);
    std::cout << "Trailer: ";
    std::getline(std::cin, trailer);

    int int_year = this->serv.convert_to_int(year);
    int int_likes = this->serv.convert_to_int(likes);

    if(int_year == -1 || int_likes == - 1)
        std::cout<< "\t\tPlease make sure that you only introduce integers in the Year and Likes fields!\n";
    else if(this->serv.add_movie_serv(title, genre, int_year, int_likes, trailer) == 1){
        std::cout << "\t\tMovie added successfully!\n";
    }else
        std::cout << "\t\tError! Movie already exists, can't be added again!\n";
}

void UI::remove_movie_ui() {
    std::string title, genre, year;
    std::cout << "Title: ";
    std::getline(std::cin, title);
    std::cout << "Genre: ";
    std::getline(std::cin, genre);
    std::cout << "Year: ";
    std::getline(std::cin, year);

    int int_year = this->serv.convert_to_int(year);

    if(int_year == -1)
        std::cout<< "\t\tPlease make sure that you only introduce integers in the Year field!\n";
    else if(this->serv.remove_movie_serv(title, genre, int_year) == 1){
        std::cout << "\t\tMovie deleted successfully!\n";
    }else
        std::cout << "\t\tError! Movie doesn't exist, can't be deleted!\n";
}

void UI::update_movie_ui() {
    std::string title, genre, year, likes, trailer, nr;
    std::cout << "Please introduce the number of the movie in the list(count starts from 0):\n";
    std::getline(std::cin, nr);
    int int_nr = this->serv.convert_to_int(nr);
    std::cout << "Title: ";
    std::getline(std::cin, title);
    std::cout << "Genre: ";
    std::getline(std::cin, genre);
    std::cout << "Year: ";
    std::getline(std::cin, year);
    std::cout << "Likes: ";
    std::getline(std::cin, likes);
    std::cout << "Trailer: ";
    std::getline(std::cin, trailer);

    int int_year = this->serv.convert_to_int(year);
    int int_likes = this->serv.convert_to_int(likes);

    if(int_year == -1 || int_likes == - 1)
        std::cout<< "\t\tPlease make sure that you only introduce integers in the Year and Likes fields!\n";
    else if(this->serv.update_movie_serv(title, genre, int_year, int_likes, trailer, int_nr) == 1){
        std::cout << "\t\tMovie updated successfully!\n";
    }else
        std::cout << "\t\tError! Movie can't be updated because it doesn't exist!\n";

}

void UI::display_by_genre_ui() {
    std::string genre, genre_no_space;
    std::cout << "Genre: ";
    std::getline(std::cin, genre);
    WatchList w = this->serv.display_by_genre_serv(genre);

    Movie m;
    std::string cmd;
    int display_movie = 1;
    while(!w.is_empty()){
        if(display_movie){
            w.play_trailer_serv();
            m = w.get_current();
            std::cout << "Movie with title: " << m.get_title() << ", genre: " << m.get_genre() << ", year:" << m.get_year() << ", likes: " << m.get_likes() <<"\n";
            display_movie = 0;
        }

        print_watchlist_menu();
        std::getline(std::cin, cmd);

        if(cmd != "exit" && cmd != "add" && cmd != "next")
            std::cout << "\n\tInvalid command!\n";

        if(cmd == "exit")
            break;

        if(cmd == "add"){
            if(this->serv.add_watchlist_serv(m)) /// todo delete it from the w list
                std::cout << "\t\tMovie added successfully to the watchlist!\n";
            else
                std::cout << "\t\tError! Movie already exists, can't be added again!\n";
        }

        if(cmd == "next"){
            w.next();
            display_movie = 1;
        }

    }
    if(w.is_empty())
        std::cout << "\t\tThere are no movies that can be watched!\n";

}

void UI::list_watchlist_all(){
    DynamicVector<Movie> w = this->serv.get_all_watchlist();
    if(w.get_size() == 0){
        std::cout << "\n\tNo movies in the watchlist!\n";
        return;
    }
    for(int i = 0; i < w.get_size(); i++){
        Movie m = w.get_elem(i);
        std::cout << "Movie with title: " << m.get_title() << ", genre: " << m.get_genre() << ", year:" << m.get_year() << ", likes: " << m.get_likes() << ", trailer: " << m.get_trailer()<<"\n";
    }
}

void UI::delete_from_watchlist_ui() {
    std::string title, genre, year, like;
    std::cout << "Title: ";
    std::getline(std::cin, title);
    std::cout << "Genre: ";
    std::getline(std::cin, genre);
    std::cout << "Year: ";
    std::getline(std::cin, year);

    std::cout << "Like the movie(y/n): ";
    std::getline(std::cin, like);

    int int_year = this->serv.convert_to_int(year);

    if(int_year == -1)
        std::cout<< "\t\tPlease make sure that you only introduce integers in the Year field!\n";

    if(like == "y"){
        if(this->serv.like_movie_serv(title, genre, int_year))
            std::cout << "\t\tMovie was liked!\n";
        else
            std::cout << "\t\tThere was an error!\n";
    }
    else if(like == "n")
        std::cout << "\t\tMovie wasn't liked!\n";
    else
        std::cout << "\t\tInvalid command for liking!\n";


    if(this->serv.remove_watchlist_serv(title, genre, int_year) == 1){
        std::cout << "\t\tMovie deleted successfully from the watch list!\n";
    }else
        std::cout << "\t\tError! Movie doesn't exist in the watch list, can't be deleted!\n";
}

