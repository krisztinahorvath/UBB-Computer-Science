#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class Weather {
private:
    int start;
    int end;
    int temperature;
    int prec_probability;
    std::string description;

public:
    Weather();
    ~Weather();
    Weather(int start, int end, int t, int prec, std::string desc): start(start), end(end), prec_probability(prec), description(desc){}
    int get_start() { return start; }
    int get_end() { return end;}
    int get_temp() { return temperature; }
    int get_prec_probability() { return prec_probability; };
    std::string get_d() { return description; }

    friend std::istream& operator>>(std::istream& is, Weather& t);

    std::string to_string() const;

};

