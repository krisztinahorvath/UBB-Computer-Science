#include "Service.h"
#include <fstream>

void Service::add_building_serv(Building *b) {
    this->repo.push_back(b);
}

std::vector<Building *> Service::get_all_to_be_restored() {
    std::vector<Building *> aux;
    for(auto b: this->repo)
        if(b->mustBeRestored())
            aux.push_back(b);
    return aux;

}

std::vector<Building *> Service::get_all_to_be_demolished() {
    std::vector<Building *> aux;
    for(auto b: this->repo)
        if(b->canBeDemolished())
            aux.push_back(b);
    return aux;
}

void Service::write_to_file(const std::string& file_name, std::vector<Building *> buildings) {
    std::ofstream f(file_name, std::ios::trunc);
    if(!f.is_open())
        return;
    for(auto b : buildings)
        f << b->toString() << "\n";
    f.close();
}

std::vector<Building *>Service::must_be_restored_year(int year) {
    std::vector<Building *> build = this->get_all_to_be_restored();
    std::vector<Building *> res;
    for(auto b: build){
        if(b->get_year() > year)
            res.push_back(b);
    }
    return res;
}

Service::Service() = default;

Service::~Service() = default; 
