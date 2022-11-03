//
// Created by krisz on 5/4/2022.
//

#include "UI.h"
#include <iostream>

void UI::print_menu() {
    std::cout << "\nMenu";
    std::cout << "\n\t1 - add client";
    std::cout << "\n\t2 - remove client";
    std::cout << "\n\t3 - show all";
    std::cout << "\n\t4 - add dwelling";
    std::cout << "\n5 - write";
    std::cout << "\nOption: ";

    
}

UI::~UI() {

}

void UI::start() {
    std::string cmd;
    while(true){
        print_menu();
        std::cin>>cmd;
        if(cmd == "exit")
            break;
        else if(cmd == "1"){
            add_client();
            continue;
        }
        else if(cmd == "2"){
            remove_client();
            continue;
        }
        else if(cmd == "3"){
            show_all();
            continue;
        }
        else if(cmd == "4"){
            add_dwelling();
            continue;
        }
        else if(cmd == "5"){
            write_to_file();
            continue;
        }
    }

}

void UI::add_client() {
    std::cout << "\nName: ";
    std::string name;
    std::cin>>name;

    std::cout<<"\nIncome: ";
    double income;
    std::cin>>income;

    std::cout << "\nClient type: person/company";
    std::string type;
    std::cin>>type;
    if(type == "person"){
        Client* c;
        auto p = new Person(name, income);
        c = p;
        serv.add_client(c);
    }
    else{
        std::cout << "\nMoney from inv: ";
        double money;
        std::cin>>money;

        Client* c;
        auto comp = new Company(name, income, money);
        c = comp;
        serv.add_client(c);
    }

}

void UI::remove_client() {
    std::cout << "\nName: ";
    std::string name;
    std::cin>>name;
    serv.remove_client(name);

}

void UI::show_all() {
    std::cout << "\nClients: \n";
    for(auto c: serv.get_clients())
        std::cout << c->to_string() << "\n";

    std::cout << "\n Dwellings \n";

    for(auto d :serv.get_dwellings())
        std::cout << d.to_string();
}

void UI::add_dwelling() {
    std::cout <<"\n Price: ";
    double price;
    std::cin>>price;
    std::cout << "\nIs profit: yes/no";
    std::string prof;
    std::cin >> prof;
    bool profit;
    if(prof == "yes")
        profit = true;
    else profit = false;

    Dwelling a = serv.add_dwelling(price, profit);

    std::vector<Client *> intr = serv.get_interested_clients(a);
    for(auto d :intr)
        std::cout << d->to_string() << "\n";
}

void UI::write_to_file() {
    std::string file = R"(C:\Facultate\OOP\tests\t2-913-Horvath-Krisztina-1\dir)";
    serv.write_to_file(file);

}
