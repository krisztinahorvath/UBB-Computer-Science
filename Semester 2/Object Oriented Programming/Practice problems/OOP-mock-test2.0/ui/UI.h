#pragma once
#include "Service.h"

class UI {
private:
    Service serv;

public:
    explicit UI(Service serv): serv(serv){}
    ~UI();
    void print_menu();
    void start();
    void add_ui();
    void show_all();
    void show_eff();
    void write_to_file_ui();

};
