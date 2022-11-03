//
// Created by krisz on 5/4/2022.
//

#include "RealEstateAgency.h"
#include <fstream>

Dwelling RealEstateAgency::add_dwelling(double price, bool is_profitable) {
//    Dwelling*k;
    auto d  = Dwelling(price, is_profitable);
    dwellings.push_back(d); /// todo fix
    return d;
}

void RealEstateAgency::add_client(Client *c) {
    clients.push_back(c);

}

void RealEstateAgency::remove_client(std::string name) {
    int pos = find_client_pos(name);
    clients.erase(clients.begin() + pos);

}

std::vector<Client *> RealEstateAgency::get_interested_clients(Dwelling d) {
    std::vector<Client *> res;
    for(auto i: clients)
        if(i->is_interested(d))
            res.push_back(i);
    return res;
}

void RealEstateAgency::write_to_file(std::string file_name) {
    std::ofstream f(file_name, std::ios::trunc);
    for(auto i:clients)
        f << i->to_string() <<"\n";
    f.close();

}

RealEstateAgency::RealEstateAgency() {

}

RealEstateAgency::~RealEstateAgency() {

}

int RealEstateAgency::find_client_pos(std::string name) {
    int pos = 0;
    for(auto c: clients){
        if(c->get_name() == name){
            return pos;
        }
        pos++;
    }
    return -1;
}
