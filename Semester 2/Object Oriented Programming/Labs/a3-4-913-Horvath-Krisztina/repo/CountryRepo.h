#pragma once
#include "Country.h"
#include "DynamicArray.h"

typedef struct
{
   DynamicArray* countries;
} CountryRepo;

/**
 * Creates the repository of a given capacity.
 * capacity - integer number, representing the maximum capacity of the repo.
 * */
CountryRepo* create_repo();

/**
 * Destroys the repo.
 * arr - the country repository, a dynamic array.
 * */
void destroy_repo(CountryRepo* arr);

/**
 * Adds a country to the country repository(dynamic array).
 *      arr - the dynamic array
 *      c - the country to be added*/
int add_country(CountryRepo* repo, Country* c);

/**
 * Deletes a country from the repository.
 *      arr - dynamic array storing all the countries
 *      c - the country to be deleted */
int delete_country(CountryRepo* repo, char* name);

/**
 * Gets the length of the repository
 * v - country repo
 * return: the length of the repo*/
int get_repo_length(CountryRepo* v);

/**
 * Finds a country by its unique name.
 * repo - country repository
 * name - pointer to a string, the name we are looking for
 * return: a pointer to the country
 *         NULL - if not found*/
Country* find_by_name(CountryRepo* repo, char* name);

/**
 * Gets a country by its position in the repo
 * v - repository
 * pos - integer, position in the repo
 * return: a pointer to the country
 *         NULL - if not found*/
Country* get_country_on_pos(CountryRepo* v, int pos);

/**
 * Updates the population of a country in the case that there is no migration between countries
 *      repo - dynamic array storing all the countries
 *      name - name of the country
 *      new_population - the new number of the population*/
int update_no_migration(CountryRepo* repo, char* name, double new_population);

/**
 * Updates the population of a country in the case that there is migration between two countries
 *      arr - dynamic array storing all the countries
 *      country1 - name of the country from where the migration is made
 *      country2 - name of the country to where the migration is made
 *      population_leaving - the nr of people leaving country1 and going to country2*/
int update_with_migration(CountryRepo* repo, char* country1, char* country2, double population_leaving);