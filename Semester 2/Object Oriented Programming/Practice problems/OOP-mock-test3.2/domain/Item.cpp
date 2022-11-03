//
// Created by krisz on 5/24/2022.
//

#include "Item.h"

Item::Item() {
    category = "";
    name = "";
    quantity = 0;
}

Item::~Item() {

}

std::string Item::to_string() const {
    std::stringstream buffer;
    buffer << category << " | " << name << " | " << quantity;
    return buffer.str();
}

std::vector<std::string> tokenize(const std::string &str, char delimiter){
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while(getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &is, Item &i) {
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = tokenize(line, '|');

    if(tokens.size() != 3)
        return is;

    i.category = tokens[0];
    i.name = tokens[1];
    i.quantity = stoi(tokens[2]);

    return is;
}

