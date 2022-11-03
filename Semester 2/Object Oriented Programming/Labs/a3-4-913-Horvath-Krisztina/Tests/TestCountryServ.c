#include "TestCountryServ.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void test_create_service()
{
    CountryRepo* repo = create_repo();
    Service* serv = create_service(repo);

    add_country_srv(serv, "Romania", "Europe", 19000000);
    add_country_srv(serv, "Hungary", "Europe", 7000000);
    add_country_srv(serv, "Peru", "America", 8000000);
    add_country_srv(serv, "Argentina", "America", 15000000);
    add_country_srv(serv, "Algeria", "Africa", 1100010);


    destroy_service(serv);
}

void test_add_country_srv()
{
    CountryRepo* repo = create_repo();
    Service* serv = create_service(repo);

    add_country_srv(serv, "Romania", "Europe", 19000000);
    add_country_srv(serv, "Hungary", "Europe", 7000000);
    add_country_srv(serv, "Peru", "America", 8000000);
    add_country_srv(serv, "Argentina", "America", 15000000);
    add_country_srv(serv, "Algeria", "Africa", 1100010);

    assert(get_repo_length(repo) == 5);
    Country* c1 = get_country_on_pos(repo, 0);
    assert(strcmp(get_name(c1), "Romania") == 0);
    assert(strcmp(get_continent(c1), "Europe") == 0);
    assert(get_population(c1) == 19000000);

    Country* c2 = get_country_on_pos(repo, 4);
    assert(strcmp(get_name(c2), "Algeria") == 0);
    assert(strcmp(get_continent(c2), "Africa") == 0);
    assert(get_population(c2) == 1100010);

    assert(add_country_srv(serv, "Romania", "Europe", 19000000) == -1);


    destroy_service(serv);
}

void test_delete_country_srv()
{
    CountryRepo* repo = create_repo();
    Service* serv = create_service(repo);

    add_country_srv(serv, "Romania", "Europe", 19000000);
    add_country_srv(serv, "Hungary", "Europe", 7000000);
    add_country_srv(serv, "Peru", "America", 8000000);
    add_country_srv(serv, "Argentina", "America", 15000000);
    add_country_srv(serv, "Algeria", "Africa", 1100010);

    assert(delete_country_srv(serv, "Romania") == 1);
    assert(delete_country_srv(serv, "Romania") == 0);
    assert(delete_country_srv(serv, "Jamaica" ) == 0);
    assert(delete_country_srv(serv, "Algeria") == 1);

    assert(get_repo_length(repo) == 3);

    destroy_service(serv);
}

void test_update_no_migration_srv()
{
    CountryRepo* repo = create_repo();
    Service* serv = create_service(repo);


    Country* c1 = create_country("Romania", "Europe", 10000);
    assert(update_no_migration_srv(serv, "Romania", 1) == 0);

    add_country_srv(serv, "Romania", "Europe", 19000000);
    add_country_srv(serv, "Hungary", "Europe", 7000000);

    assert(update_no_migration_srv(serv, "Romania", 1) == 1);

    assert(get_population(find_by_name(repo, "Romania")) == 1);

    assert(update_no_migration_srv(serv, "Jamaica", 1) == 0);

    assert(update_no_migration_srv(serv, "Hungary", 2) == 1);
    assert(get_population(find_by_name(repo, "Hungary")) == 2);

    destroy_service(serv);
}

void test_update_with_migration_srv()
{
    CountryRepo* repo = create_repo();
    Service* serv = create_service(repo);

    destroy_service(serv);
}

void test_display_countries_containing_given_string_srv()
{
    CountryRepo* repo = create_repo();
    Service* serv = create_service(repo);

    destroy_service(serv);
}

void test_sort_ascending_by_population()
{
    CountryRepo* repo = create_repo();
    Service* serv = create_service(repo);

    destroy_service(serv);
}

void test_sort_descending_by_population()
{
    CountryRepo* repo = create_repo();
    Service* serv = create_service(repo);

    destroy_service(serv);
}

void test_display_countries_by_population_srv()
{
    CountryRepo* repo = create_repo();
    Service* serv = create_service(repo);

    destroy_service(serv);
}

void test_display_countries_on_given_continent_srv()
{
    CountryRepo* repo = create_repo();
    Service* serv = create_service(repo);

    destroy_service(serv);
}

void run_tests_country_service()
{
    test_create_service();
    test_add_country_srv();
    test_delete_country_srv();
    test_update_no_migration_srv();
    test_update_with_migration_srv();
    test_display_countries_by_population_srv();
    test_display_countries_containing_given_string_srv();
    test_sort_ascending_by_population();
    test_sort_descending_by_population();
    test_display_countries_by_population_srv();
    test_display_countries_on_given_continent_srv();
    printf("Service tests passed");
}