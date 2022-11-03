
#include "Weather.h"

Weather::Weather() {

}

Weather::~Weather() {

}

std::vector<std::string> tokenize(const std::string &str, char delimiter){
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while(getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &is, Weather &t) {
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ';');

    if(tokens.size() != 5)
        return is;

    t.start = stoi(tokens[0]);
    t.end = stoi(tokens[1]);
    t.temperature = stoi(tokens[2]);
    t.prec_probability = stoi(tokens[3]);
    t.description = tokens[4];

    return is;
}

std::string Weather::to_string() const {
    std::stringstream buffer;
    buffer << start << ";" << end << ";" << temperature << ";" << prec_probability << ";" << description;
    return buffer.str();
}
