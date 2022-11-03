#pragma once
#include "movie.h"
#include <vector>

class Repository
{
private:
    std::vector<Movie> movies;

public:
    Repository();

    void write_to_file();

    /**
     * Adds a movie to the repo if it doesn't exist already.
     * return: 1 - if movie added
     *         0 - if it already exists*/
    void add_movie(const Movie& m);

    /**
     * Removes a movie from the repo.
     * return: 1 - if successfully deleted
     *         0 - if it doesn't exist */
    void remove_movie(const Movie& m);

    /**
     * Updates a movie by replacing it with the new movie
     * m - new movie, that will replace the old one
     * return: 1 - if movie updated successfully
     *         0 - otherwise */
    void update_movie(const Movie& m);

    /**
     * Returns a movie based on its title, genre and year.
     * return: position of that movie in the repo if it exists
     *         -1 - otherwise*/
    int find_movie(const std::string& title, const std::string& genre, const int year);

    std::vector<Movie> get_movies() const{ return this->movies; }

    void read_from_file();
};

class RepositoryException: public std::exception {
private:
    std::string message;
public:
    explicit RepositoryException(std::string& _message);

    const char *what() const noexcept override;
};