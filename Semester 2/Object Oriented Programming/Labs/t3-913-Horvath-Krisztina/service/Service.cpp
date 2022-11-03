//
// Created by krisz on 5/25/2022.
//

#include "Service.h"
#include <fstream>

std::vector<Weather> Service::get_sorted_times() {
    std::vector<Weather> w = times;
    for(int i = 0; i < w.size() - 1; i++)
        for(int j = i + 1; j < w.size(); j++)
            if(w[i].get_start() > w[j].get_start()){
                Weather wed = w[i];
                w[i] = w[j];
                w[j] = wed;
            }
    return w;
}

Service::Service() {

}

Service::~Service() {

}

void Service::read_from_file() {
    std::string file_name = R"(C:\Facultate\OOP\tests\t3-913-Horvath-Krisztina\times.txt)";

    std::ifstream f(file_name);

    Weather t{};
    while(f >> t)
        times.push_back(t);
    f.close();
}

int Service::get_time(std::string d, int s) {
    int sum = 0;
    for(auto i: times)
        if(i.get_start() == s && s && i.get_d() == d)
            sum += i.get_end() - i.get_end();

    return sum;
}
