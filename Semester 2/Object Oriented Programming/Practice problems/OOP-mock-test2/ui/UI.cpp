//
// Created by krisz on 5/3/2022.
//

#include "UI.h"
#include <iostream>

UI::UI() = default;

UI::~UI() {

}

void UI::start() {
    std::string cmd;
    while(true){
        print_menu();
        std::getline(std::cin, cmd);
        if(cmd == "exit")
            break;
        else if(cmd == "1"){
            add_building_ui();
            continue;
        }
        else if(cmd == "2"){
            show_all();
            continue;

        }
        else if(cmd == "3"){
            show_must_be_restored();
            continue;
        }
        else if(cmd == "4"){
            save_to_file();
            continue;
        }


    }

}

void UI::print_menu() {
    std::cout << "\nMenu:";
    std::cout << "\n\t1 - add";
    std::cout << "\n\t2 - show all buildings";
    std::cout << "\n\t3 - show must be restored";
    std::cout << "\n\t4 - save all to file";
    std::cout << "\nOption: ";

}

void UI::add_building_ui() {
    std::cout << "\n\nChoose type (block/ house): ";
    std::string type;
    std::getline(std::cin, type);

    std::cout << "\naddress: ";
    std::string address;
    std::getline(std::cin, address);

    std::cout << "\nyear: ";
    std::string year;
    std::getline(std::cin, year);

    if(type == "block"){
        std::cout << "\ntotal ap: ";
        std::string total;
        std::getline(std::cin, total);

        std::cout << "\noccupied ap: ";
        std::string oc;
        std::getline(std::cin, oc);

        Building* build;

        auto b = new Block(address, stoi(year), stoi(total), stoi(oc));
        build = b;
        this->serv.add_building_serv(build);
    }
    else if(type == "house"){
        std::cout << "\nis historical yes/no: ";
        std::string his;
        std::getline(std::cin, his);
        Building* b;
        if(his == "yes"){
            auto h = new House(address, stoi(year), true);
            b = h;
        }
        else {
            auto h = new House(address, stoi(year), false);
            b = h;
        }
        this->serv.add_building_serv(b);
    }
}

void UI::show_all() {
    std::vector<Building* > build = this->serv.get_all_buildings();
    for(auto b: build)
        std::cout << "\n" << b->toString();

}

void UI::show_must_be_restored() {
    std::cout <<"\nyear: ";
    std::string year;
    std::getline(std::cin, year);
    std::vector<Building * > build = this->serv.must_be_restored_year(stoi(year));
    for(auto b: build)
        std::cout << b->toString();
}

void UI::save_to_file() {
    std::vector<Building *> demol = this->serv.get_all_to_be_demolished();
    std::string file_name = R"(C:\Facultate\OOP\tests\OOP-mock-test2\demolished)";
    this->serv.write_to_file(file_name, demol);

    std::vector<Building *> rest = this->serv.get_all_to_be_restored();
    std::string file = R"(C:\Facultate\OOP\tests\OOP-mock-test2\restored)";
    this->serv.write_to_file(file, rest);

}
