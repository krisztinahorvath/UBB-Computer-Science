#include "services.h"

int Service::add_movie_serv(const std::string &title, const std::string &genre, const int year, const int likes,
                            const std::string &trailer) {
    Movie m = Movie(title, genre, year, likes, trailer);

    return this->repo.add_movie(m);
}

int Service::remove_movie_serv(const std::string &title, const std::string &genre, const int year) {
    Movie m = Movie(title, genre, year, 0, "");

    return this->repo.remove_movie(m);
}

int Service::update_movie_serv(const std::string &title, const std::string &genre, const int year, const int likes,
                               const std::string &trailer, int index) {
    Movie m = Movie(title, genre, year, likes, trailer);

    return this->repo.update_movie(m, index);
}

int Service::convert_to_int(const std::string &number) {
    int ok = 1;
    for(int i = 0; i < number.size() && ok == 1 ; i++)
        if(!(number[i] >= '0' && number[i] <= '9'))
            ok = 0;
    if(ok == 0)
        return -1;
    return stoi(number);
}

///////////////////////////// a6

int Service::add_watchlist_serv(const Movie &m) {
    return this->watchList.add_watchlist(m);
}

int Service::remove_watchlist_serv(const std::string &title, const std::string &genre, const int year) {
    Movie m = Movie(title, genre, year, 0, "");

    return this->watchList.remove_watchlist(m);
}

int Service::like_movie_serv(const std::string &title, const std::string &genre, const int year){
    Movie m = this->watchList.find_movie_by_info(title, genre, year);
    Movie updated = Movie(m.get_title(), m.get_genre(), m.get_year(), m.get_likes() + 1, m.get_trailer());

    return this->repo.update_movie(updated, 0);  /// todo
}

WatchList Service::display_by_genre_serv(const std::string& genre) {
    if(genre.empty()){
        WatchList w;
        Movie m;
        for(int i = 0; i < this->repo.get_movies().get_size(); i++){
            m = this->repo.get_movies().get_elem(i);
            w.add_watchlist(m);
        }
        return w;
    }

    WatchList w;
    Movie m;
    for(int i = 0; i < this->repo.get_movies().get_size(); i++){
        m = this->repo.get_movies().get_elem(i);
        if(m.get_genre() == genre)
            w.add_watchlist(m);
    }
    return w;
}