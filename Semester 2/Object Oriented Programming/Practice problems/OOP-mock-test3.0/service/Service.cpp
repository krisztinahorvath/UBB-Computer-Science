#include "Service.h"
#include <fstream>

void Service::read_from_file() {
    std::string file_name = R"(C:\Facultate\OOP\tests\OOP-mock-test3.0\tasks.txt)";
    std::ifstream f(file_name);

    Task t{};
    while(f >> t){ /// todo works????
        tasks.push_back(t);
    }
    f.close();
}

void Service::write_to_file() {
    std::string file_name;
    std::ofstream f(file_name, std::ios::trunc);
    for(auto t:tasks)
        f << t << "\n";
    f.close();
}

Service::Service() {

}

Service::~Service() {

}

std::vector<Task> Service::get_sorted() {
    std::vector<Task> sorted = this->tasks;
    for(int i = 0; i < sorted.size() - 1; i++){
        for(int j = i + 1; j < sorted.size(); j++)
            if(sorted[i].get_priority() > sorted[j].get_priority())
            {
                Task aux = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = aux;
            }
    }

    for(int i = 0; i < sorted.size() - 1; i++){
        for(int j = i + 1; j < sorted.size(); j++)
            if(sorted[i].get_priority() == sorted[j].get_priority() && sorted[i].get_estimated_duration() > sorted[j].get_estimated_duration())
            {
                Task aux = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = aux;
            }
    }

    return sorted;
}

int Service::get_task_priority(int p) {
    int found = 0;
    int sum = 0;
    for(auto t: tasks)
        if(t.get_priority() == p){
            found = 1;
            sum += t.get_estimated_duration();
        }
    if(found == 0)
        return -1;
    return sum;
}
