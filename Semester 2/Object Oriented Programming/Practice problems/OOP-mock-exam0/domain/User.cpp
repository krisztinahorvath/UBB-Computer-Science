//
// Created by krisz on 6/4/2022.
//

#include "User.h"

User::User() {
    name = "";
    type = "";
}



std::istream &operator>>(std::istream &is, User &i) {
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ';');

    if(tokens.size() != 2)
        return is;

    i.name = tokens[0];
    i.type = tokens[1];
    return is;
}

std::ostream &operator<<(std::ostream &is, User &i) {
    is << i.name << ";" << i.type<<"\n";
    return is;
}

std::string User::to_string() {
    std::stringstream buffer;
    buffer << name << ";" << type<<"\n";
    return buffer.str();
}

User::~User() = default;
