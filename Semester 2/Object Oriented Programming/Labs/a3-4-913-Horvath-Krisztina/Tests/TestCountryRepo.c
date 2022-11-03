
#include "TestCountryRepo.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void test_create_repo()
{
    /// tested get_repo_length()
    /// tested test_find_by_name()
    /// tested test_get_country_on_pos()
    CountryRepo* repo = create_repo();

    assert(repo->countries->capacity == 10);
    assert(get_repo_length(repo) == 0);

    Service* serv = create_service(repo);
    add_country_srv(serv, "Romania", "Europe", 19000000);
    add_country_srv(serv, "Hungary", "Europe", 7000000);
    assert(get_repo_length(repo) == 2);
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

    Country* c3 = get_country_on_pos(repo, 6);
    assert(c3 == NULL);

    Country* c4 = find_by_name(repo, "Romania");
    assert(strcmp(get_name(c4), "Romania") == 0);
    assert(strcmp(get_continent(c4), "Europe") == 0);
    assert(get_population(c4) == 19000000);


    Country* c5 = find_by_name(repo, "jamaica");
    assert(c5 == NULL);

    destroy_repo(repo);
}

void test_add_country()
{
    CountryRepo* repo = create_repo();
    Country* c1 = create_country("Romania", "Europe", 19000000);
    assert(add_country(repo, c1) == 0);

    Country* c2 = create_country("Romania", "Europe", 19000000);
    assert(add_country(NULL, c2) == -1);

    assert(add_country(NULL, NULL ) == -1);
    assert(add_country(repo, NULL) == -1);

    Country* c3 =  create_country("Romania", "Europe", 19000000);
    assert(add_country(repo, c3) == -1);

    destroy_repo(repo);

}

void test_delete_country()
{
    CountryRepo* repo = create_repo();
    Country* c1 = create_country("Romania", "Europe", 19000000);
    add_country(repo, c1);
    Country* c2 = create_country("Hungary", "Europe", 7000000);
    add_country(repo, c2);
    assert(delete_country(repo, "Hungary") == 1);
    assert(delete_country(repo, NULL) == 0);
    assert(delete_country(repo, "Jamaica") == 0);

    assert(delete_country(repo, "Romania") == 1);
    assert(delete_country(repo, "Romania") == 0);

    destroy_repo(repo);
}

void test_update_no_migration()
{
    CountryRepo* repo = create_repo();

    Country* c1 = create_country("Romania", "Europe", 19000000);
    add_country(repo, c1);
    Country* c2 = create_country("Hungary", "Europe", 7000000);
    add_country(repo, c2);

    assert(update_no_migration(repo, "Romania", 1) == 1);
    assert(get_population(c1) == 1);

    assert(update_no_migration(repo, "Jamaica", 1) == 0);

    assert(update_no_migration(repo, "Hungary", 2) == 1);
    assert(get_population(c2) == 2);

    destroy_repo(repo);

}

void test_update_with_migration()
{
    CountryRepo* repo = create_repo();

    Country* c1 = create_country("Romania", "Europe", 2);
    add_country(repo, c1);
    Country* c2 = create_country("Hungary", "Europe", 1);
    add_country(repo, c2);

    assert(update_with_migration(repo, "Romania", "Hungary", 1) == 1);

    assert(get_population(c1) == 1);
    assert(get_population(c2) == 2);

    assert(update_with_migration(repo, "Romania", "Hungary", 1) == 1);
    assert(get_population(c1) == 0);
    assert(get_population(c2) == 3);

}

void run_tests_country_repo()
{
    test_create_repo();
    test_add_country();
    test_delete_country();
//    test_update_no_migration();
//    test_update_with_migration();
    printf("Repo tests passed!\n");
}
