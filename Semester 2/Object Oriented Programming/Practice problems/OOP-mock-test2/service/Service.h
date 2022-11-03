#pragma once
#include "building.h"
#include <vector>

class Service {
private:
    std::vector<Building*> repo;

public:
    Service();
    ~Service();
    void add_building_serv(Building* b);
    std::vector<Building *> get_all_buildings() { return this->repo;} /// todo return vector of buildings
    std::vector<Building *> get_all_to_be_restored();
    std::vector<Building *> get_all_to_be_demolished();
    void write_to_file(const std::string& file_name, std::vector<Building *> buildings);
    std::vector<Building *> must_be_restored_year(int year);


};



