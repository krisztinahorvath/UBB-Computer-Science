#pragma once
#include "WatchList.h"

class HTMLWatchList: public WatchList
{
public:
    HTMLWatchList();
    ~HTMLWatchList();

    void add_watchlist(const Movie& m) override { WatchList::add_watchlist(m); this->write_to_file(); }
    void remove_watchlist(const Movie& m) override {WatchList::remove_watchlist(m); this->write_to_file(); }

    void write_to_file() override;
    void open_in_app() override;
};