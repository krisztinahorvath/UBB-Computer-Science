//
// Created by krisz on 5/24/2022.
//

#include "Task.h"

Task::Task() {
    description = "";
    estimated_duration = 0;
    priority = 0;
}

Task::~Task() {

}

std::string Task::to_string() const {
    std::stringstream buffer;
    buffer << description << " | " << estimated_duration << "|" << priority;
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

std::istream &operator>>(std::istream &is, Task& t){
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = tokenize(line, '|');

    if(tokens.size() != 3)
        return is;

    t.description = tokens[0];
    t.estimated_duration = stoi(tokens[1]);
    t.priority = stoi(tokens[2]);

    return is;
}
