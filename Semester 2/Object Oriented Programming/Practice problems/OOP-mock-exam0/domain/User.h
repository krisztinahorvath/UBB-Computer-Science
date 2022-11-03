#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "utilities.h"


class User {
private:
    std::string name;
    std::string type;

public:
    User();
    User(std::string n, std::string t): name(n), type(t){};
    ~User();

    friend std::istream& operator>>(std::istream& is, User& i);
    friend std::ostream& operator<<(std::ostream& is, User& i);
    std::string to_string();

    std::string get_name() { return name;}
    std::string get_type() { return type;}


};


