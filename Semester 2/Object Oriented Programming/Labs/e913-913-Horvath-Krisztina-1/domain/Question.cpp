//
// Created by krisz on 6/6/2022.
//

#include "Question.h"

Question::Question() {

}

std::vector<std::string> tokenize(const std::string &str, char delimiter){
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while(getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::ostream &operator<<(std::ostream &os, Question &q) {
    os << q.id << ";" << q.text << ";" << q.correct_answer << ";" << q.score;
    return os;
}

std::istream &operator>>(std::istream &is, Question& q) {
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ';');

    if(tokens.size() != 4)
        return is;

    q.id = stoi(tokens[0]);
    q.text = tokens[1];
    q.correct_answer = tokens[2];
    q.score = stoi(tokens[3]);

    return is;
}

std::string Question::to_string() {
    std::stringstream buffer;
    buffer << id << ";" << text << ";" << correct_answer << ";" << score;
    return buffer.str();
}

std::string Question::to_string_part() {
    std::stringstream buffer;
    buffer << id << ";" << text << ";"  << score;
    return buffer.str();
}

std::istream &operator>>(std::istream &is, Participant &p) {
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ';');

    if(tokens.size() != 2)
        return is;

    p.name = tokens[0];
    p.score = stoi(tokens[1]);

    return is;
}

std::ostream &operator<<(std::ostream &os, Participant &p) {
    os << p.name << ";" << p.score;
    return os;
}

std::string Participant::to_string() {
    std::stringstream buffer;
    buffer << name << ";" << score;
    return buffer.str();
}

Participant::Participant() {

}
