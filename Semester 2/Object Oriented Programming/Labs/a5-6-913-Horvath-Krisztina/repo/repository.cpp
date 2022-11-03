#include "repository.h"

int Repository::add_movie(const Movie& m) {
    int pos = find_movie(m.get_title(), m.get_genre(), m.get_year());
    if(pos == -1)
    {
//        this->movies.add(m);
        m+this->movies;
        return 1;

    }
    return 0;
}

int Repository::remove_movie(const Movie &m) {
    int pos = find_movie(m.get_title(), m.get_genre(), m.get_year());
    if(pos == -1)
        return 0;
    this->movies.remove(pos);
    return 1;
}

int Repository::update_movie(const Movie &m, int index) {
//    int pos = find_movie(m.get_title(), m.get_genre(), m.get_year());

    if(index < 0 || index > this->movies.get_size())
        return 0;
//    if(pos == -1)
//        return 0;

    this->movies.update(index, m);
    return 1;
}

int Repository::find_movie(const std::string& title, const std::string& genre, const int year) {
    Movie m;
    for(int i = 0; i < this->movies.get_size(); i++){
        m = this->movies.get_elem(i);
        if(m.get_title() == title && m.get_genre() == genre && m.get_year() == year)
            return i;
    }
    return -1;
}
