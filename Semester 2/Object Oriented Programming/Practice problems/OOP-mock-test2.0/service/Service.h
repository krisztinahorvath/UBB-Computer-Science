#pragma once
#include <vector>
#include "HospitalDepartment.h"

class Service {
private:
    std::vector<HospitalDepartment *> repo;

    std::vector<HospitalDepartment*> sorted();

public:
    Service();
    ~Service();
    void add_department(HospitalDepartment* d);
    std::vector<HospitalDepartment *> get_all_departments(){ return this->repo;}
    std::vector<HospitalDepartment *> get_all_efficient_departments();
    void write_to_file(std::string file_name);



};


