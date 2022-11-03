//
// Created by krisz on 5/3/2022.
//

#include <fstream>
#include "Service.h"

void Service::add_department(HospitalDepartment* d) {
    this->repo.push_back(d);
}

std::vector<HospitalDepartment *> Service::get_all_efficient_departments() {
    std::vector<HospitalDepartment *> res;
    for(auto d: this->repo)
        if(d->isEfficient())
            res.push_back(d);

    return res;
}

Service::Service() {

}

Service::~Service() {

}


void Service::write_to_file(std::string file_name) {
    std::ofstream f(file_name, std::ios::trunc);
    std::vector<HospitalDepartment *> srt = sorted();
    for(auto h: srt)
        f << h->toString();
    f.close();
}

std::vector<HospitalDepartment *> Service::sorted() {
    std::vector<HospitalDepartment *> res = this->get_all_departments();
    for(int i = 0; i < res.size() - 1; i++){
        for(int j = i + 1; j < res.size(); j++){
            if(res[i]->get_name() > res[j]->get_name()){
                HospitalDepartment* h = res[i];
                res[i] = res[j];
                res[j] = h;

            }
        }

    }

    return res;
}
