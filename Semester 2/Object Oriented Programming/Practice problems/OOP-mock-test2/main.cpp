#include <iostream>
#include "UI.h"

void add(Service& serv){
    Building* b;
    auto a = new Block("str rovine, nr100, ap33", 1980, 40, 20);
    b = a;
    serv.add_building_serv(b);
    a = new Block("str bucuresti, nr100, ap33", 1973, 14, 2);
    b = a;
    serv.add_building_serv(b);

    auto z = new House("str crinului, nr12A", 2001, false);
    b = z;
    serv.add_building_serv(b);

    z = new House("str crinului, nr12A", 1900, true);
    b = z;
    serv.add_building_serv(b);
}

int main()
{
    Service serv;

    add(serv);

    UI ui{serv};
    ui.start();
    return 0;
}