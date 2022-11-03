#include "UI.h"
#include <string>
#include <iostream>

void UI::start() {
    while(true){
        std::string cmd;
        std::getline(std::cin, cmd);
        if(cmd == "add"){
            add_bill_ui();
            continue;
        }
        if(cmd == "remove"){
//            remove_bill_ui();
            continue;
        }
        if(cmd == "list"){
            list_all_ui();
            continue;
        }
        if(cmd == "exit")
            break;
    }

}

void UI::add_bill_ui() {
    std::string serial, company, date, sum, isPaid;
    std::cout<< "serial nr: ";
    std::getline(std::cin, serial);

    std::cout<< "company: ";
    std::getline(std::cin, company);

    std::cout<< "date: ";
    std::getline(std::cin, date);

    std::cout<< "serial nr: ";
    std::getline(std::cin, sum);

    std::cout<< "paid: y/n ";
    std::getline(std::cin, isPaid);

    bool paid;
    if(isPaid == "y")
        paid = true;
    else paid = false;

    if(this->serv.add_bill_serv(serial, company, date, stoi(sum), paid) == 1)
        std::cout <<"added\n";

}

void UI::list_all_ui() {
    DynamicVector<Bill> b = this->serv.get_all_bills();
    Bill aux;
    for(int i = 0; i < b.get_size(); i++){
        aux = b.get_elem(i);
        bool paid = aux.get_isPaid();
        std::string p;
        if(paid == true)
            p = "true";
        else p = "false";
        std::cout << aux.get_serial_number() << ";" << aux.get_company() << ";" << aux.get_due_date() <<";" << aux.get_sum() << "; " << p <<"\n";
    }


}

