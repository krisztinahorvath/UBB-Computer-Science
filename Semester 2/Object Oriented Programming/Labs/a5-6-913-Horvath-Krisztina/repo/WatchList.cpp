#include "WatchList.h"


WatchList::WatchList() {
    this->index = 0;
}

int WatchList::add_watchlist(const Movie &m) {
    int pos = find_watchlist(m);
    if(pos == -1)
    {
        this->watchlist.add(m);
        return 1;
    }
    return 0;
}

int WatchList::remove_watchlist(const Movie& m){
    int pos = find_watchlist(m);
    if(pos == -1)
        return 0;
    this->watchlist.remove(pos);
    return 1;
}

int WatchList::find_watchlist(const Movie& m) {
    for(int i = 0; i < this->watchlist.get_size(); i++){
        Movie mov = this->watchlist.get_elem(i);
        if(m.get_title() == mov.get_title() && m.get_genre() == mov.get_genre() &&
        m.get_year() == mov.get_year())
            return i;
    }
    return -1;
}

void WatchList::next() {
    if(this->watchlist.get_size() == this->index + 1)
    {
        this->index = 0;
        return;
    }
    this->index++;
}

bool WatchList::is_empty() {
    if(this->watchlist.get_size() == 0)
        return true;
    return false;
}

void WatchList::play_trailer_serv(){
    if(this->watchlist.get_size() == 0)
        return;
    Movie m = this->get_current();
    m.play_trailer();
}

Movie WatchList::get_current() {
    return this->watchlist.get_elem(this->index);
}

Movie WatchList::find_movie_by_info(const std::string& title, const std::string& genre, int year) {
    Movie m;
    for(int i = 0; i < this->watchlist.get_size(); i++){
        m = this->watchlist.get_elem(i);
        if(m.get_title() == title && m.get_genre() == genre && m.get_year() == year)
            return m;
    }
    return Movie("", "", 0, 0, "");
}