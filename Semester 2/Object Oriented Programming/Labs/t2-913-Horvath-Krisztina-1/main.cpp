#include <iostream>
#include "UI.h"

void add_main(RealEstateAgency& serv){
    Client* c;
    auto p = new Person("Ana", 2000);
    c = p;
    serv.add_client(c);

    p = new Person("Maria", 5000);
    c = p;
    serv.add_client(c);

    auto comp = new Company("NTT", 10000, 15000);
    c = comp;
    serv.add_client(c);

    comp = new Company("Google", 10000, 15000);
    c = comp;
    serv.add_client(c);

//    auto d = new Dwelling(1500, true);
    serv.add_dwelling(1500, true);
}

int main()
{
    RealEstateAgency serv;
    add_main(serv);

    UI ui{serv};
    ui.start();
    return 0;
}