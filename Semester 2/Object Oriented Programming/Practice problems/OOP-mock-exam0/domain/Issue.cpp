//
// Created by krisz on 6/4/2022.
//

#include "Issue.h"
#include "utilities.h"

Issue::Issue() {

}

Issue::~Issue() {

}

std::istream &operator>>(std::istream &is, Issue& i) {
    std::string line;
    std::getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ';');

    if(tokens.size() != 4)
        return is;

    i.description = tokens[0];
    i.status = tokens[1];
    i.reporter = tokens[2];
    i.solver = tokens[3];
    return is;
}

std::string Issue::to_string() {
    std::stringstream buffer;

    buffer << description << ";" << status << ";" << reporter << ";" << solver;
    return buffer.str();
}

std::ostream &operator<<(std::ostream &is, Issue &i) {
    is << i.description << ";" << i.status << ";" << i.reporter << ";" << i.solver;
    return is;
}
