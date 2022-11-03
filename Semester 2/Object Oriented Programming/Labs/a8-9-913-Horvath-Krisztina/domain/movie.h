#pragma once
#include <string>
#include <iostream>
#include <vector>

class Movie
{
private:
    std::string title;
    std::string genre;
    int year;
    int likes;
    std::string trailer;

public:
    Movie();
    Movie(const std::string& title, const std::string& genre, const int year, const int likes, const std::string& trailer);

    std::string get_title() const { return this->title; }
    std::string get_genre() const { return this->genre; }
    int get_year() const { return this->year; }
    int get_likes() const { return this->likes; }
    std::string get_trailer() const { return this->trailer; }

    bool operator==(const Movie& m);

    void play_trailer();

    Movie& operator=(const Movie& m);

    friend std::istream& operator>>(std::istream& is, Movie &m);
    friend std::ostream& operator<<(std::ostream& os, Movie& m);

    std::string to_string() const;
};