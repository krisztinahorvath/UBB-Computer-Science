#include "Country.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void test_create_country()
{
    Country* c = create_country("Romania", "Europe", 10000);
    assert(strcmp(get_name(c), "Romania") == 0);
    assert(strcmp(get_continent(c), "Europe") == 0);
    assert(get_population(c) == 10000);

    destroy_country(c);

    Country* c1 = create_country("Romania", "Europe", 10000);
    char string[100];
    to_string(c1, string);
    assert(strcmp(string, "Romania, Europe, 10000.00\n") == 0);

    Country* copy = copy_country(c);
    assert(strcmp(get_name(c1), get_name(copy)) == 0);
    assert(strcmp(get_continent(c1), get_continent(copy)) == 0);
    assert(get_population(c1) == get_population(copy));

    destroy_country(c1);
    destroy_country(copy);

}


void run_tests_domain()
{
    test_create_country();
    printf("Domain tests passed!\n");
}