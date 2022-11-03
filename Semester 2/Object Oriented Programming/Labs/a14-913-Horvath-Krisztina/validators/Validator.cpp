#include "Validator.h"

#include <utility>

void Validator::validate_title(const std::string &title) {
    if(title.empty()){
        std::string error = "\n\tError! The title field can't be empty!\n";
        throw MovieException(error);
    }
}

void Validator::validate_genre(const std::string &genre) {
    if(genre.empty()){
        std::string error = "\n\tError! The genre field can't be empty!\n";
        throw MovieException(error);
    }

    if(!std::isupper(genre[0])){
        std::string error = "\n\tThe genre should start with a capital letter!\n";
        throw MovieException(error);
    }
}

void Validator::validate_year(const std::string &year) {
    if(year.empty()){
        std::string error = "\n\tError! The year field can't be empty!\n";
        throw MovieException(error);
    }

    int int_year = this->convert_to_int(year);
    if(int_year == -1){
        std::string error = "\n\tError! Only introduce integers in the year field!\n";
        throw MovieException(error);
    }

    if(int_year < 1888 || int_year > 2050){
        std::string error = "\n\tError! The year should be between 1888 and 2050!\n";
        throw MovieException(error);
    }

}

void Validator::validate_likes(const std::string &likes) {
    if(likes.empty()){
        std::string error = "\n\tError! The likes field can't be empty!\n";
        throw MovieException(error);
    }
    int int_likes = this->convert_to_int(likes);
    if(int_likes == -1){
        std::string error = "\n\tError! Only introduce integers in the like field!\n";
        throw MovieException(error);
    }
}

void Validator::validate_trailer(const std::string &trailer) {
    if(trailer.empty()){
        std::string error = "\n\tError! The trailer field can't be empty!\n";
        throw MovieException(error);
    }

    int http = trailer.find("http");
    int www = trailer.find("www");
    if(http != 0 && www != 0){
        std::string error = "\n\tThe trailer should start with http or www!\n";
        throw MovieException(error);
    }
}

int Validator::convert_to_int(const std::string &number) {
    int ok = 1;
    for(int i = 0; i < number.size() && ok == 1 ; i++)
        if(!(number[i] >= '0' && number[i] <= '9'))
            ok = 0;
    if(ok == 0)
        return -1;
    return stoi(number);
}

void Validator::validate_movie(std::string &title, std::string &genre, std::string &year, std::string &likes,
                               std::string &trailer) {
    std::string errors;

    try{
        validate_title(title);
    }
    catch (MovieException& e){
        errors.append(e.what());
    }

    try{
        validate_genre(genre);
    }
    catch (MovieException& e){
        errors.append(e.what());
    }

    try{
        validate_year(year);
    }
    catch (MovieException& e){
        errors.append(e.what());
    }

    try{
        validate_likes(likes);
    }
    catch (MovieException& e){
        errors.append(e.what());
    }

    try{
        validate_trailer(trailer);
    }
    catch (MovieException& e){
        errors.append(e.what());
    }

    if(!errors.empty())
        throw MovieException(errors);

}

Validator::Validator() = default;

Validator::~Validator() = default;

MovieException::MovieException(std::string  _message): message(std::move(_message)) {}

const char *MovieException::what() const noexcept {
    return message.c_str();
}