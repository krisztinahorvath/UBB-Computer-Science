#pragma once
#include <vector>
#include "Client.h"

class RealEstateAgency {
private:
    std::vector<Client *> clients;
    std::vector<Dwelling > dwellings;
    /// todo add dwellings??

public:
    RealEstateAgency();
    ~RealEstateAgency();
    Dwelling add_dwelling(double price, bool is_profitable);
    void add_client(Client* c);
    void remove_client(std::string name);
    std::vector<Client *> get_interested_clients(Dwelling d);
    std::vector<Client *>  get_clients() { return clients;}
    std::vector<Dwelling> get_dwellings() { return dwellings;}
    void write_to_file(std::string file_name);
    int find_client_pos(std::string name);

};

