#pragma once
#include <vector>
#include "movie.h"

class WatchList {
protected:
    std::vector<Movie> watchlist;
    int index; /// index of the current element
    std::string type;

public:
    WatchList();
    WatchList(std::vector<Movie> m, int index);
    ~WatchList();

    std::string get_type() { return this->type;}
    int get_size() const { return this->watchlist.size(); }


    virtual void add_watchlist(const Movie& m);


    virtual void remove_watchlist(const Movie& m);

    /**
     * Returns the current movie(indicated by the index) from the watchlist*/
    Movie get_current();

    /**
     * Goes to the next movie in the watchlist, if it's the last it goes back to the first one in the repo*/
    void next();

    /**
     * Checks if the watchlist repo is empty
     * Return: true - if repo empty
     *         false - otherwise*/
    bool is_empty();

    /**
     * Plays the current movies trailer*/
    void play_trailer_serv();

    /**
   * Finds in the watchlist a movie and it returns its position in the repo
     * Return:  the position of the movie - if found
     *          -1 - otherwise*/
    int find_watchlist(const Movie& m);

    /**
     * Finds a movie by title, genre and year
     * Return: movie - if found
     *         empty movie - otherwise*/
    Movie find_movie_by_info(const std::string& title, const std::string& genre, int year);

    std::vector<Movie> get_watchlist() const{ return this->watchlist; }



//    WatchList get_watchlist_genre(std::vector<Movie> repo, std::string genre);

    virtual void write_to_file() = 0;
    virtual void open_in_app() = 0;
};


class WatchListRepoException: public std::exception {
private:
    std::string message;
public:
    explicit WatchListRepoException(std::string& _message);

    const char *what() const noexcept override;
};