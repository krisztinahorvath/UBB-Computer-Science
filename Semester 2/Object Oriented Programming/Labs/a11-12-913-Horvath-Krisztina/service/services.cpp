#include "services.h"
#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
#include "CSVWatchList.h"
#include "HTMLWatchList.h"

void Service::add_movie_serv(const std::string &title, const std::string &genre, const int year, const int likes,
                             const std::string &trailer) {
    Movie m = Movie(title, genre, year, likes, trailer);

    this->repo.add_movie(m);
}

void Service::remove_movie_serv(const std::string &title, const std::string &genre, const int year) {
    Movie m = Movie(title, genre, year, 0, "");

    this->repo.remove_movie(m);
}

void Service::update_movie_serv(const std::string &title, const std::string &genre, const int year, const int likes,
                                const std::string &trailer) {
    Movie m = Movie(title, genre, year, likes, trailer);

    this->repo.update_movie(m);
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

void Service::add_watchlist_serv(const Movie &m) {
    this->watchList->add_watchlist(m);
}

void Service::remove_watchlist_serv(const std::string &title, const std::string &genre, const int year) {
    Movie m = Movie(title, genre, year, 0, "");

    this->watchList->remove_watchlist(m);
}

void Service::like_movie_serv(const std::string &title, const std::string &genre, const int year){
    Movie m = this->watchList->find_movie_by_info(title, genre, year);
    Movie updated = Movie(m.get_title(), m.get_genre(), m.get_year(), m.get_likes() + 1, m.get_trailer());

    this->repo.update_movie(updated);
}


WatchList * Service::display_by_genre_serv(const std::string& genre) {
    if(genre.empty()){

        std::vector<Movie> watch;
        std::vector<Movie> mov = this->repo.get_movies();

        std::copy_n(mov.begin(), mov.size(), std::back_inserter(watch));

        WatchList* w;
        auto c = new CSVWatchlist(watch, 0);
        w = c;
        return w;
    }

    std::vector<Movie> watch;
    std::vector<Movie> m = this->repo.get_movies();

    std::copy_if(m.begin(), m.end(), std::back_inserter(watch), [&genre](Movie& mv) {return mv.get_genre() == genre;});

    WatchList* w;
    auto c = new CSVWatchlist(watch, 0);
    w = c;
    return w;
}