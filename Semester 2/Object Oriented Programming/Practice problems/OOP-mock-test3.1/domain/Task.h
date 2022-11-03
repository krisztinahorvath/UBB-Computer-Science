#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

class Task {
private:
    std::string description;
    int estimated_duration;
    int priority;

public:
    Task();
    ~Task();
    Task(std::string d, int dur, int p): description(d), estimated_duration(dur), priority(p) {}
    std::string get_description() { return this->description; }
    int get_estimated_duration() { return this->estimated_duration; }
    int get_priority() { return priority; }

    friend std::istream& operator>>(std::istream& is, Task& t);
    std::string to_string() const;
};

