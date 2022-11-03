#include "repository.h"
#include <bits/stdc++.h>

void Repository::add_movie(const Movie& m) {
    ///todo validate the movies
    int pos = find_movie(m.get_title(), m.get_genre(), m.get_year());
    if(pos != -1)
    {
        std::string error;
        error += std::string("\n\tThe movie already exists!\n");
        if(!error.empty())
            throw RepositoryException(error);
    }
    this->movies.push_back(m);
    write_to_file();
}

void Repository::remove_movie(const Movie &m) {
    int pos = find_movie(m.get_title(), m.get_genre(), m.get_year());
    if(pos == -1){
        std::string error;
        error += std::string("\n\tThe movie you are trying to delete does not exist!\n");
        throw RepositoryException(error);
    }
    this->movies.erase(this->movies.begin() + pos);
    write_to_file();
}

void Repository::update_movie(const Movie &m) {
    int pos = find_movie(m.get_title(), m.get_genre(), m.get_year());

    if(pos == -1){
        std::string error;
        error += std::string("\n\tThe movie you are trying to update does not exist!\n");
        throw RepositoryException(error);
    }
    this->movies[pos] =  m;
    write_to_file();
}

int Repository::find_movie(const std::string& title, const std::string& genre, const int year) {
    int pos = 0;
    for(const auto& i: this->movies){
        if(i.get_title() == title && i.get_genre() == genre && i.get_year() == year)
            return pos;
        pos++;
    }
    return -1;
}

Repository::Repository() = default;


void Repository::read_from_file() { /// todo maybe change this, throws exception just at the end??
    this->movies.clear();
    std::string file_name = R"(C:\Facultate\OOP\a14-913-Horvath-Krisztina\repo\movies.csv)";
    std::ifstream f(file_name);
    if(!f.is_open()){
        std::string error = "\n\tCouldn't open file for reading!\n";
        throw RepositoryException(error);
    }

    Movie m{};
    std::string error;
    while(f >> m){
        if(this->find_movie(m.get_title(), m.get_genre(), m.get_year()) != -1){
            error += std::string("\n\tThe movie exists already in the repository!\n");
            throw RepositoryException(error);
        }
        this->movies.push_back(m); ///
    } /// todo check if it isnt added twice

    f.close();
}

void Repository::write_to_file() {
    std::string file_name = R"(C:\Facultate\OOP\a14-913-Horvath-Krisztina\repo\movies.csv)";
    std::ofstream f(file_name, std::ios::trunc);;
    if(!f.is_open()){
        std::string error = "\n\tError! Couldn't open file for writing!\n";
        throw RepositoryException(error);
    }
    for(auto m: this->movies)
        f << m << "\n";
    f.close();

}

RepositoryException::RepositoryException(std::string &_message) : message(_message) {}

const char* RepositoryException::what() const noexcept {
    return message.c_str();
}