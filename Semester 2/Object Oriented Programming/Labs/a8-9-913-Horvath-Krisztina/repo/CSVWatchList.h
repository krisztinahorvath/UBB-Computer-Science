#pragma once
#include "WatchList.h"
class CSVWatchlist: public WatchList
{
public:
    CSVWatchlist();

    CSVWatchlist(std::vector<Movie> vector1, int i);

    ~CSVWatchlist();

    void add_watchlist(const Movie& m) override { WatchList::add_watchlist(m); this->write_to_file(); }
    void remove_watchlist(const Movie& m) override {WatchList::remove_watchlist(m); this->write_to_file(); }

    void write_to_file() override;
    void open_in_app() override;
};
