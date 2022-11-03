//
// Created by krisz on 6/5/2022.
//

#include "User.h"
#include <vector>

User::User() {

}

User::~User() {

}
std::vector<std::string> tokenize(const std::string &str, char delimiter){
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while(getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::ostream &operator<<(std::ostream &os, User& u) {
    os << u.name;
    return os;
}

std::istream &operator>>(std::istream &is, User &u) {
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = tokenize(line, '\n'); /// todo???

    if(tokens.size() != 1)
        return is;

    u.name = tokens[0];
    return is;
}

Question::Question() {

}

std::ostream &operator<<(std::ostream &os, Question &q) {
    os << q.id << ";" << q.text << ";" << q.name;
    return os;
}

std::istream &operator>>(std::istream &is, Question &q) {
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ';'); /// todo???

    if(tokens.size() != 3)
        return is;

    q.id = stoi(tokens[0]);
    q.text = tokens[1];
    q.name = tokens[2];
    return is;
}

Answer::Answer() {

}

std::ostream &operator<<(std::ostream &os, Answer &a) {
    os << a.id << ";" << a.question_id << ";" << a.name << ";" << a.text << ";" << a.number_of_votes;
    return os;
}

std::istream &operator>>(std::istream &is, Answer &a) {
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ';'); /// todo???

    if(tokens.size() != 5)
        return is;

    a.id = stoi(tokens[0]);
    a.question_id = stoi(tokens[1]);
    a.name = tokens[2];
    a.text = tokens[3];
    a.number_of_votes = stoi(tokens[4]);
    return is;
}
