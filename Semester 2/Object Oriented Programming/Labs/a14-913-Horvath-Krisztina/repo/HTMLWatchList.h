#pragma once
#include "WatchList.h"

#include <utility>

class HTMLWatchList: public WatchList
{
public:
    HTMLWatchList();

    HTMLWatchList(std::vector<Movie> vector1, int i);

    ~HTMLWatchList();

    void add_watchlist(const Movie& m) override { WatchList::add_watchlist(m); this->write_to_file(); }
    void remove_watchlist(const Movie& m) override {WatchList::remove_watchlist(m); this->write_to_file(); }

    void write_to_file() override;
    void open_in_app() override;
};