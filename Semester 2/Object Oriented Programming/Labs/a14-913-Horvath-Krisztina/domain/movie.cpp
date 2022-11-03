#include "movie.h"
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <cstdio>

Movie::Movie(){   ///: title{""}, genre{""}, year{0}, likes{0}, trailer{""} {}
    this->title = "";
    this->genre = "";
    this->year = 0;
    this->likes = 0;
    this->trailer = "";
}

Movie::Movie(const std::string& title, const std::string& genre, const int year, const int likes, const std::string& trailer) {
    this->title = title;
    this->genre = genre;
    this->year = year;
    this->likes = likes;
    this->trailer = trailer;
}

bool Movie::operator==(const Movie& m) {
    if(this->title == m.get_title() && this->genre == m.get_genre() && this->year == m.get_year() && this->likes == m.get_likes() && this->trailer == m.get_trailer())
        return true;
    return false;
}

void Movie::play_trailer() {
    std::string link = "start " + this->get_trailer(); /// todo xdg-open
    system(link.c_str());
}

Movie& Movie::operator=(const Movie& m) = default;

std::vector<std::string> tokenize(const std::string& str, char delimiter){
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &is, Movie &m) {
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ',');
    if(tokens.size() != 5)
        return is;

    m.title = tokens[0];
    m.genre = tokens[1];
    m.year = std::stoi(tokens[2]);
    m.likes = std::stoi(tokens[3]);
    m.trailer = tokens[4];

    return is;
}


std::ostream &operator<<(std::ostream &os, Movie &m) {
    os << m.title << "," << m.genre << "," << std::to_string(m.year) << "," << std::to_string(m.likes) << "," << m.trailer;
    return os;
}

std::string Movie::to_string() const {
    std::stringstream buffer;
    buffer << "\nMovie with title: " << this->title << ", genre: " << this->genre << ", year: " << this->year<< ", likes: " << this->likes << ", trailer: " << this->trailer << "\n";
    return buffer.str();
}