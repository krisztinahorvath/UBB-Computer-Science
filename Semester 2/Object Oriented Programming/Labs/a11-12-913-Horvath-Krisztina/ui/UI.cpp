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

        if(cmd == "open"){
            open_in_app();
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
    std::cout << "   open      - open in app\n";
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
    std::vector<Movie> l = this->serv.get_all_movies();
    if(l.empty())
        std::cout << "No movies in the repository!\n";

    for(const auto& i: l){
        std::cout << i.to_string();
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
    try{
        valid.validate_movie(title, genre, year, likes, trailer);
        this->serv.add_movie_serv(title, genre, stoi(year), stoi(likes), trailer);
        std::cout << "\n\tThe movie was added successfully!\n";
    }
    catch (RepositoryException& e)
    {
        std::cout << "\n\t" << e.what();
    }
    catch (MovieException& e){
        std::cout << e.what();
    }
    catch(std::invalid_argument& e){
        std::cout << "\n\tPlease make sure to only introduce integers in the year and likes fields!\n";
    }
    catch(...){

    }
}

void UI::remove_movie_ui() {
    std::string title, genre, year;
    std::cout << "Title: ";
    std::getline(std::cin, title);
    std::cout << "Genre: ";
    std::getline(std::cin, genre);
    std::cout << "Year: ";
    std::getline(std::cin, year);

    int ok = 0;

    try{
        valid.validate_title(title);
    }
    catch (MovieException& e){
        std:: cout << e.what();
        ok++;
    }

    try{
        valid.validate_genre(genre);
    }
    catch (MovieException& e){
        std:: cout << e.what();
        ok++;
    }

    try{
        valid.validate_year(year);
    }
    catch (MovieException& e){
        std:: cout << e.what();
        ok++;
    }

    if(ok == 0){
        try{
            this->serv.remove_movie_serv(title, genre, stoi(year));
            std::cout << "\t\tMovie deleted successfully!\n";
        }
        catch(RepositoryException& e){
            std::cout << e.what();
        }
        catch(std::invalid_argument& e){
            std::cout << "\n\tPlease make sure to only introduce integers in the year field!\n";
        }
        catch(MovieException& e){
            std::cout << e.what();
        }
        catch(...){

        }
    }
}

void UI::update_movie_ui() {
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

    try
    {
        valid.validate_movie(title, genre, year, likes, trailer);
        this->serv.update_movie_serv(title, genre, stoi(year), stoi(likes), trailer);
        std::cout <<"\n\n" << "Movie updated successfully!\n";
    }
    catch (RepositoryException& e){
        std::cout << e.what();
    }
    catch (std::invalid_argument& e){
        std::cout << "\n\tPlease make sure to only introduce integers in the year and likes fields!\n";
    }
    catch (MovieException& e){
        std::cout << e.what();
    }
    catch(...){

    }
}

void UI::display_by_genre_ui() {
    std::string genre, genre_no_space;
    std::cout << "Genre: ";
    std::getline(std::cin, genre);
    WatchList* w = this->serv.display_by_genre_serv(genre);

    Movie m;
    std::string cmd;
    int display_movie = 1;
    while(!w->is_empty()){
        if(display_movie){
            w->play_trailer_serv();
            m = w->get_current();
            std::cout << m.to_string();
            display_movie = 0;
        }

        print_watchlist_menu();
        std::getline(std::cin, cmd);

        if(cmd != "exit" && cmd != "add" && cmd != "next")
            std::cout << "\n\tInvalid command!\n";

        if(cmd == "exit")
            break;

        if(cmd == "add"){
            try{
                this->serv.add_watchlist_serv(m);
                std::cout << "\t\tMovie added successfully to the watchlist!\n";
            }
            catch(WatchListRepoException& e){
                std::cout << e.what();
            }
            catch(...){

            }
        }

        if(cmd == "next"){
            w->next();
            display_movie = 1;
        }

    }
    if(w->is_empty())
        std::cout << "\t\tThere are no movies that can be watched!\n";

}

void UI::list_watchlist_all(){
    std::vector<Movie> w = this->serv.get_all_watchlist();
    if(w.empty()){
        std::cout << "\n\tNo movies in the watchlist!\n";
        return;
    }
    for (const auto& m: w)
        std::cout << m.to_string();
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

    int ok = 0;

    try{
        valid.validate_title(title);
    }
    catch (MovieException& e){
        std:: cout << e.what();
        ok++;
    }

    try{
        valid.validate_genre(genre);
    }
    catch (MovieException& e){
        std:: cout << e.what();
        ok++;
    }

    try{
        valid.validate_year(year);
    }
    catch (MovieException& e){
        std:: cout << e.what();
        ok++;
    }

    if(ok == 0){
        if(like == "y"){
            try{
                this->serv.like_movie_serv(title, genre, stoi(year));
                std::cout << "\t\tMovie was liked!\n";
            }
            catch (RepositoryException& e){
                std::cout << e.what();
            }
        }
        else if(like == "n")
            std::cout << "\t\tMovie wasn't liked!\n";
        else
            std::cout << "\t\tInvalid command for liking!\n";

        try{
            this->serv.remove_watchlist_serv(title, genre, stoi(year));
            std::cout << "\t\tMovie deleted successfully from the watch list!\n";
        }
        catch (WatchListRepoException& e){
            std::cout << e.what();
        }
    }
}

void UI::open_in_app() {
    watchList->open_in_app();
}