#include "Task.h"
#include <sstream>
#include <vector>

Task::~Task() = default;

std::vector<std::string> tokenize(const std::string& str, char delimiter){
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &is, Task &t) {
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = tokenize(line, '|');

    if(tokens.size() != 3)
        return is;
    t.description = tokens[0];
    t.estimated_duration = std::stoi(tokens[1]);
    t.priority = std::stoi(tokens[2]);

    return is;
}

std::ostream &operator<<(std::ostream &os, Task &t) {
    os << t.description << "|" << t.estimated_duration << "|" << t.priority;
    return os;
}

std::string Task::to_string() const {
    std::stringstream buffer;
    buffer << this->description << " | " << this->estimated_duration << " | " << this->priority;
    return buffer.str();
}

Task::Task() {
    description = "";
    estimated_duration = 0;
    priority = 0;
}
