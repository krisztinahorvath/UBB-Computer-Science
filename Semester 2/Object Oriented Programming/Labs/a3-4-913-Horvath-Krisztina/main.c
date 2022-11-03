#include "UI.h"
#include <stdio.h>
#include "Tests/RunTests.h"
/**
 * Adds 10 countries to the repository.
 * All data is valid.
 * */
void add_data(Service* serv)
{
    add_country_srv(serv, "Romania", "Europe", 19000000);
    add_country_srv(serv, "Hungary", "Europe", 7000000);
    add_country_srv(serv, "Peru", "America", 8000000);
    add_country_srv(serv, "Argentina", "America", 15000000);
    add_country_srv(serv, "Algeria", "Africa", 1100010);
    add_country_srv(serv, "Australia", "Australia", 10000000);
    add_country_srv(serv, "Bolivia", "America", 150000);
    add_country_srv(serv, "Japan", "Asia", 160000);
    add_country_srv(serv, "Monaco", "Europe", 160000);
    add_country_srv(serv, "Vatican", "Europe", 19000);
}

int main()
{
//    run_all_tests();


    CountryRepo* repo = create_repo();
    Service* serv = create_service(repo);

    add_data(serv); /// adds 10 countries to the repo

    UI* ui = create_ui(serv);

    start_ui(ui);
    destroy_ui(ui);

    return 0;
}
