#include "movie.h"
#include <string>

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
    std::string link = "xdg-open " + this->get_trailer();
    system(link.c_str());
}
