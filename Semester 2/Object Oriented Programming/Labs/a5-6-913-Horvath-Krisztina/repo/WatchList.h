#pragma once
#include "DynamicVector.h"
#include "movie.h"

class WatchList {
private:
    DynamicVector<Movie> watchlist;
    int index; /// index of the current element

public:
    WatchList();

    int get_size() const { return this->watchlist.get_size(); }

    /** Adds a movie to the watchlist repo
     * m - movie to be added to the watchlist repo
     * Return: 1 - if the movie was added successfully
     *         0 - otherwise
     * */
    int add_watchlist(const Movie& m);

    /** Removes a movie from the watchlist repo
     * m - movie to be removed from the watchlist repo
     * Return: 1 - if the movie was added successfully
     *         0 - otherwise
     * */
    int remove_watchlist(const Movie& m);

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

    DynamicVector<Movie> get_watchlist() const{ return this->watchlist; }

};


