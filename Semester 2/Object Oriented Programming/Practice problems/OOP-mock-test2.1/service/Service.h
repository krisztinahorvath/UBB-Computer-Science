#pragma once
#include "Appliance.h"
#include <vector>

class Service {
private:
    std::vector<Appliance *> repo;

public:
    Service();
    ~Service();
    void add_appliance(Appliance* a);
    std::vector<Appliance * > get_all_appliances() {return this->repo;}

};
