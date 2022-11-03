#pragma once
#include "RealEstateAgency.h"

class UI {
private:
    RealEstateAgency serv;

public:
    UI(RealEstateAgency serv): serv(serv) {}
    ~UI();
    void print_menu();
    void start();
    void add_client();
    void remove_client();
    void show_all();
    void add_dwelling();
    void write_to_file();

};
