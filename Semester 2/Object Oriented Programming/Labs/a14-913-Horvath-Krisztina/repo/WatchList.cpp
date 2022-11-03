#include "WatchList.h"
#include <algorithm>
#include <utility>


WatchList::WatchList() {
    this->index = 0; /// todo ??
}

WatchList::WatchList(std::vector<Movie> m, int i):  watchlist{std::move(m)}, index{i}{}

void WatchList::add_watchlist(const Movie &m) {
    int pos = find_watchlist(m);
    if(pos != -1)
    {
        std::string error;
        error += std::string("\t\tError! Movie already exists, can't be added again!\n");
        throw WatchListRepoException(error);
    }
    this->watchlist.push_back(m);; /// todo it is added here
}

void WatchList::remove_watchlist(const Movie& m){
    int pos = find_watchlist(m);
    if(pos == -1){
        std::string error;
        error += std::string("\t\tError! Movie doesn't exist in the watch list, can't be deleted!\n");
        throw WatchListRepoException(error);
    }
    this->watchlist.erase(this->watchlist.begin() + pos);
}

int WatchList::find_watchlist(const Movie& m) {
    int pos = 0;
    for(const auto& i: this->watchlist){
        if(m.get_title() == i.get_title() && m.get_genre() == i.get_genre() &&
           m.get_year() == i.get_year())
            return pos;
        pos++;
    }
    return -1;
}

void WatchList::next() {
    if(this->watchlist.size() == this->index + 1)
    {
        this->index = 0;
        return;
    }
    this->index++;
}

bool WatchList::is_empty() {
    if(this->watchlist.empty())
        return true;
    return false;
}

void WatchList::play_trailer_serv(){
    if(this->watchlist.empty())
        return;
    Movie m = this->get_current();
    m.play_trailer();
}

Movie WatchList::get_current() {
    return this->watchlist.at(this->index);
}

Movie WatchList::find_movie_by_info(const std::string& title, const std::string& genre, int year) {
    Movie m;
    for(auto & i : this->watchlist){
        m = i;
        if(m.get_title() == title && m.get_genre() == genre && m.get_year() == year)
            return m;
    }
    return Movie("", "", 0, 0, "");
}

WatchList::~WatchList() = default;

WatchListRepoException::WatchListRepoException(std::string &_message): message(_message){}

const char *WatchListRepoException::what() const noexcept {
    return message.c_str();
}