//
// Created by krisz on 5/24/2022.
//

#include "Service.h"
#include <fstream>

Service::Service() {

}

Service::~Service() {

}

std::vector<Task> Service::get_sorted_tasks() {
    std::vector<Task> sorted = tasks;

    /// asc by priority
    for(int i = 0; i < sorted.size() - 1; i++)
        for(int j = i + 1; j < sorted.size(); j++)
            if(sorted[i].get_priority() > sorted[j].get_priority()){
                Task t = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = t;
            }

    /// desc by duration
    for(int i = 0; i < sorted.size() - 1; i++)
        for(int j = i + 1; j < sorted.size(); j++)
            if(sorted[i].get_priority() == sorted[j].get_priority() && sorted[i].get_estimated_duration() < sorted[j].get_estimated_duration()){
                Task t = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = t;
            }

    return sorted;
}

void Service::read_from_file() {
    std::string file_name = R"(C:\Facultate\OOP\tests\OOP-mock-test3.1\tasks.txt)";
    std::ifstream f(file_name);

    Task t{};
    while(f >> t)
        tasks.push_back(t);
    f.close();
}

std::vector<Task> Service::get_by_priority(int p) {
    std::vector<Task> priority;
    for(auto t: tasks)
        if(t.get_priority() == p)
            priority.push_back(t);
    return priority;
}
