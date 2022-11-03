//
// Created by krisz on 5/4/2022.
//

#include "UI.h"
#include <iostream>

UI::~UI() {

}

void UI::print_menu() {
    std::cout <<"\nMenu";
    std::cout << "\n\t1 - add";
    std::cout << "\n\t2 - show all";
    std::cout << "\nOption: ";

}

void UI::start() {
    std::string cmd;
    while(true)
    {
        print_menu();
        std::cin>>cmd;
        if(cmd == "exit")
            break;
        if(cmd == "1"){
            add_ui();
            continue;
        }
        else if(cmd == "2"){
            show_all();
            continue;
        }
    }

}

void UI::add_ui() {
    std::cout << "\nid: ";
    std::string id;
    std::cin>>id;

    std::cout << "\nweight: ";
    double weight;
    std::cin>>weight;

    std::cout << "\nType of appliance: refrigerator/ dishwasher: ";
    std::string type;
    std::cin>>type;

    if(type == "refrigerator"){
        std::cout << "\nel class: ";
        std::string el_class;
        std::cin>>el_class;

        std::cout << "\n has freezer yes/no: ";
        std::string freezer;
        bool frez;
        std::cin>>freezer;
        if(freezer == "yes")
            frez = true;
        else
            frez = false;

        Appliance* a;
        auto r = new Refrigerator(id, weight, el_class, frez);
        a = r;
        this->serv.add_appliance(a);
    }
    else{
        std::cout << "\nCycle lenght: ";
        double cycle;
        std::cin>>cycle;

        std::cout << "\ncons el for one hours: ";
        double el_one_hour;
        std::cin>>el_one_hour;

        Appliance* a;
        auto d = new DishWasher(id, weight, cycle, el_one_hour);
        a = d;
        this->serv.add_appliance(a);
    }

}

void UI::show_all() {
    std::vector<Appliance *> appl = this->serv.get_all_appliances();
    for(auto a: appl)
        std::cout << a->toString();

}
