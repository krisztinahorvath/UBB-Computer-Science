#pragma once
#include "Weather.h"

class Service {
    std::vector<Weather> times;

public:
    Service();
    ~Service();
    std::vector<Weather> get_all_times() { return times; }
    std::vector<Weather> get_sorted_times();
    void read_from_file();
    int get_time(std::string d, int s);

};

