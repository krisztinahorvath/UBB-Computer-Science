#include <iostream>
#include "UI.h"
void add_main(Service& serv){
    Appliance* a;
    auto r = new Refrigerator("9", 67.3, "A+", true);
    a = r;
    serv.add_appliance(a);
    r = new Refrigerator("2", 90, "A", false);
    a = r;
    serv.add_appliance(a);

    auto d = new DishWasher("0", 18, 2.3, 15);
    a = d;
    serv.add_appliance(a);

}

int main()
{
    Service serv;
    add_main(serv);

    UI ui{serv};
    ui.start();
    return 0;

}