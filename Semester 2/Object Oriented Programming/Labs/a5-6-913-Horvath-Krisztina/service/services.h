#pragma once
#include <utility>

#include "repository.h"
#include "WatchList.h"

class Service
{
private:
    Repository repo;
    WatchList watchList;

public:
    explicit Service(Repository  r): repo(std::move(r)) {}

    Repository get_repo() const { return this->repo; }

    /**
     * Adds a movie to the movie repo if it doesn't exist already.
     * return: 1 - if movie added
     *         0 - if it already exists*/
    int add_movie_serv(const std::string& title, const std::string& genre, const int year, const int likes, const std::string& trailer);

    /**
      * Removes a movie from the movie repo.
      * return: 1 - if successfully deleted
      *         0 - if it doesn't exist */
    int remove_movie_serv(const std::string& title, const std::string& genre, const int year);

    /**
      * Updates a movie by replacing it with the new movie
      * m - new movie, that will replace the old one
      * return: 1 - if movie updated successfully
      *         0 - otherwise */
    int update_movie_serv(const std::string& title, const std::string& genre, const int year, const int likes, const std::string& trailer, int index);


    /**
     * Converts a number given as a string to an integer
     * return: int(number) - if the string is a number
     *         -1 - otherwise*/
    int convert_to_int(const std::string& number);

    DynamicVector<Movie> get_all_movies() const { return this->repo.get_movies(); }

    DynamicVector<Movie> get_all_watchlist() const { return this->watchList.get_watchlist(); }

    /**
      * Adds a movie to the watchlist repo if it doesn't exist already.
      * return: 1 - if movie added
      *         0 - if it already exists*/
    int add_watchlist_serv(const Movie& m);

    /**
     * Removes a movie from the watchlist repo.
     * return: 1 - if successfully deleted
     *         0 - if it doesn't exist */
    int remove_watchlist_serv(const std::string& title, const std::string& genre, const int year);

    /**
     * Adds a like to a movie
     * title - string, title of the movie
     * genre - string, genre of the movie
     * year - int, year of the movie
     * Return: 1 - if the movie was updated successfully
     *         0 - otherwise*/
    int like_movie_serv(const std::string& title, const std::string& genre, const int year);

    /**
     * Returns a dynamic vector containing the movies with the given genre, if the genre is empty all movies are returned
     * genre - string, the genre that we are looking for*/
    WatchList display_by_genre_serv(const std::string& genre);

};
