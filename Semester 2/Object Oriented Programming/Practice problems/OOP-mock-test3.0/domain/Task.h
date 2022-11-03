#pragma once
#include <string>
#include <utility>
#include <iostream>

class Task {
private:
    std::string description;
    int estimated_duration;
    int priority;

public:
    Task();
    Task(std::string d, int dur, int p):description(std::move(d)), estimated_duration(dur), priority(p) {}
    ~Task();
    int get_priority() const { return this->priority; }
    int get_estimated_duration() const { return this->estimated_duration; }
    std::string get_description() const { return this->description; }
    friend std::istream& operator>>(std::istream& is, Task& t);
    friend std::ostream& operator<<(std::ostream& os, Task& t);

    std::string to_string() const;

};


