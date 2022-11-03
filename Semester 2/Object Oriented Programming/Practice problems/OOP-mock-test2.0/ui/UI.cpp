//
// Created by krisz on 5/3/2022.
//

#include "UI.h"
#include <iostream>

void UI::print_menu() {
    std::cout << "\n\nMenu:";
    std::cout << "\n\t1 - add";
    std::cout << "\n\t2 - show all";
    std::cout << "\n\t3 - show all efficient";
    std::cout << "\n\t4 - save all to file";
    std::cout << "\nOption: ";
}

void UI::start() {
    std::string cmd;
    while(true){
        print_menu();
        std::getline(std::cin, cmd);
        if(cmd == "exit")
            break;
        else if(cmd == "1"){
            add_ui();
            continue;
        }
        else if(cmd == "2"){
            show_all();
            continue;
        }
        else if(cmd == "3"){
            show_eff();
            continue;
        }
        else if(cmd == "4"){
            write_to_file_ui();
            continue;
        }
    }

}

void UI::add_ui() {
    std::cout <<"\nHospital name: ";
    std::string name;
    std::getline(std::cin, name);

    std::cout << "\nNr of doctors: ";
    std::string nr_doc;
    std::getline(std::cin, nr_doc);

    std::cout << "\nType of unit: neonatal/surgery: ";
    std::string type;
    std::getline(std::cin, type);
    if(type == "neonatal") {
        std::string nr_mothers;
        std::cout << "\nNr of moms: ";
        std::getline(std::cin, nr_mothers);

        std::cout << "\nNo of newborns: ";
        std::string nr_newborn;
        std::getline(std::cin, nr_newborn);

        std::cout << "\nAvg grade:";
        double avg_grade;
        std::cin >> avg_grade;

        HospitalDepartment* h;
        auto n = new NeonatalUnit(name, stoi(nr_doc), stoi(nr_mothers), stoi(nr_newborn), avg_grade);
        h = n; /// todo here something doesn't quite work
        this->serv.add_department(h);
    }
    else if(type == "surgery"){
        std::cout << "\nNr of patients: ";
        std::string nr_pat;
        std::getline(std::cin, nr_pat);

        HospitalDepartment* h;
        auto n = new Surgery(name, stoi(nr_doc), stoi(nr_pat));
        h = n;
        this->serv.add_department(h);
    }

}

void UI::show_all() {
    std::vector<HospitalDepartment *> hosp = this->serv.get_all_departments();
    for(auto h: hosp)
        std::cout << h->toString();

}

UI::~UI() {

}

void UI::show_eff() {
    std::vector<HospitalDepartment *> hosp = this->serv.get_all_efficient_departments();
    for(auto h: hosp)
        std::cout << h->toString();

}

void UI::write_to_file_ui() {
    std::string file_name = R"(C:\Facultate\OOP\tests\OOP-mock-test2.0\departments)";
    this->serv.write_to_file(file_name);
}
