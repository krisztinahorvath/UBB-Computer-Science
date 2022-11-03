#pragma once
#include "Service.h"

class UI {
private:
    Service serv;

public:
    explicit UI(Service serv): serv(serv) {}
    UI();
    ~UI();
    void start();
    static void print_menu();
    void add_building_ui();
    void show_all();
    void show_must_be_restored();
    void save_to_file();


};
