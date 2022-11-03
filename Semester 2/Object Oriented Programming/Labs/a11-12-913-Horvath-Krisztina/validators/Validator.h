#pragma once
#include <string>
#include <exception>
#include "movie.h"

class Validator{
private:
    int convert_to_int(const std::string &number);

public:
    Validator();
    ~Validator(); ///todo need?
    void validate_movie(std::string& title, std::string& genre, std::string& year, std::string& likes, std::string& trailer);
    void validate_title(const std::string& title);
    void validate_genre(const std::string& genre);
    void validate_year(const std::string& year);
    void validate_likes(const std::string& likes);
    void validate_trailer(const std::string& trailer);

};


class MovieException: public std::exception{
private:
    std::string message;

public:
    explicit MovieException(std::string  _message);
    const char *what() const noexcept override;
};