#pragma once
#include "movie.h"

class Repository
{
private:
    DynamicVector<Movie> movies;

public:
    Repository() = default;

    /**
     * Adds a movie to the repo if it doesn't exist already.
     * return: 1 - if movie added
     *         0 - if it already exists*/
    int add_movie(const Movie& m);

     /**
      * Removes a movie from the repo.
      * return: 1 - if successfully deleted
      *         0 - if it doesn't exist */
     int remove_movie(const Movie& m);

     /**
      * Updates a movie by replacing it with the new movie
      * m - new movie, that will replace the old one
      * return: 1 - if movie updated successfully
      *         0 - otherwise */
     int update_movie(const Movie& m, int index);

     /**
      * Returns a movie based on its title, genre and year.
      * return: position of that movie in the repo if it exists
      *         -1 - otherwise*/
     int find_movie(const std::string& title, const std::string& genre, const int year);

     DynamicVector<Movie> get_movies() const{ return this->movies; }
};
