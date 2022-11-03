#include <iostream>
#include "UI.h"

void add_serv(Service& serv){
    HospitalDepartment* h;
    auto n = new NeonatalUnit("Recuperare", 15, 8, 10, 8.7);
    h = n;
    serv.add_department(h);

    n = new NeonatalUnit("Bucuresti", 32, 89, 100, 8.4);
    h = n;
    serv.add_department(h);

    auto s = new Surgery("Stanca", 29, 106);
    h = s;
    serv.add_department(h);
}
int main()
{
    Service serv;
    add_serv(serv);
    UI ui{serv};
    ui.start();
    return 0;
}