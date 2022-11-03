#include <iostream>
#include "Repository.h"
#include "Service.h"
#include "UI.h"

void add_stuff(Service& serv)
{
    serv.add_bill_serv((std::string &) "0A33455X", (std::string &) "Digi Sport", (std::string &) "15.04.2016", 75, "n");
    serv.add_bill_serv((std::string &) "EED36677", (std::string &) "E-On", (std::string &) "16.03.2016", 122, "y");
    serv.add_bill_serv((std::string &) "X990TTRR", (std::string &) "Orange", (std::string &) "18.04.2016", 46, "n");
    serv.add_bill_serv((std::string &) "1234RR55", (std::string &) "Vodafone", (std::string &) "20.04.2016", 23, "n");
    serv.add_bill_serv((std::string &) "TRE3ERR", (std::string &) "Tcmomm", (std::string &) "21.04.2016", 10, "t");
}

int main()
{
    Repository r = Repository();
    Service serv = Service(r);
    add_stuff(serv);

    UI ui_var = UI(serv);
    ui_var.start();
    return 0;
}