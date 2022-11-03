#include "CountryRepo.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

CountryRepo* create_repo()
{
    CountryRepo* v = malloc(sizeof(CountryRepo));
    if(v == NULL)
        return NULL;
    v->countries = createDynamicArray(CAPACITY, (DestroyElementFunctionType) &destroy_country);

    return v;
}

void destroy_repo(CountryRepo* v)
{
    if(v == NULL)
        return;

    destroy(v->countries);
    free(v);
}

int get_repo_length(CountryRepo* v)
{
    if (v == NULL)
        return -1;

    return get_length(v->countries);
}

Country* get_country_on_pos(CountryRepo* v, int pos)
{
    if (v == NULL)
        return NULL;
    return get(v->countries, pos);
}

Country* find_by_name(CountryRepo* repo, char* name) {
    if (repo == NULL || name == NULL) {
        return NULL;
    }

    for (int i = 0; i < get_length(repo->countries); i++) {
        Country* c = get(repo->countries, i);
        if (strcmp(get_name(c), name) == 0) {
            return c;
        }
    }

    return NULL;
}

int add_country(CountryRepo* v, Country* c)
{
    if(v == NULL || c == NULL)
        return -1;

    Country* a = find_by_name(v, get_name(c));
    if(a != NULL)
        return -1;
    destroy_country(a); /// todo memory leak???

    add(v->countries, c);
    return 0;
}

int delete_country(CountryRepo* repo, char* name)
{
    if(repo == NULL || name == NULL)
        return 0;

    Country* c = find_by_name(repo, name);
    for (int i = 0; i < get_length(repo->countries); i++) {
        if (get(repo->countries, i) == c) {
            delete(repo->countries, i);
            return 1;
        }
    }
    return 0;
}

int update_no_migration(CountryRepo* repo, char* name, double new_population)
{
    if(repo == NULL || name == NULL)
        return 0;

    Country* c = find_by_name(repo, name);
    for (int i = 0; i < get_length(repo->countries); i++) {
        if (get(repo->countries, i) == c) {

            /// delete the old version of the country
            delete(repo->countries, i);

            /// add the new version of the country
            Country* updated_c = create_country(name, get_continent(c), new_population);  /// todo possible leak here
            add(repo->countries, updated_c);
            free(updated_c);

            return 1;
        }
    }
    free(c);
    return 0;
}

int update_with_migration(CountryRepo* repo, char* country1, char* country2, double population_leaving)
{
    if(repo == NULL || country1 == NULL || country2 == NULL)
        return 0;

    Country* c1 = find_by_name(repo, country1);
    Country* c2 = find_by_name(repo, country2);
    int both_updated = 0;

    for (int i = 0; i < get_length(repo->countries); i++) {
        if (get(repo->countries, i) == c1) {
            int c = update_no_migration(repo, country1, get_population(c1) - population_leaving);
            both_updated++;
            break;
        }
    }

    for (int i = 0; i < get_length(repo->countries); i++){
        if (get(repo->countries, i) == c2) {
            int c = update_no_migration(repo, country2, get_population(c2) + population_leaving);
            both_updated++;
            break;
        }
    }
    free(c1);
    free(c2);
    free(country1);
    free(country2);
    if(both_updated == 2)
        return 1;

    return 0;
}
