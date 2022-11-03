#pragma once
#include "CountryRepo.h"

typedef struct
{
    CountryRepo* repo;
    DynamicArray* undo_stack;
    DynamicArray* redo_stack;
} Service;

/**
 * Creates an object if type service.
 * r - pointer, repository
 * return: a dynamic array of a service*/
Service* create_service(CountryRepo* r);

/**
 * Deallocates the space occupied by service.
 * s - pointer, service*/
void destroy_service(Service* s);

/**
 * Gets the repo of service s.
 * s - pointer, service
 * return: repo */
CountryRepo* get_repo(Service* s);

/**
 * Adds a country to the repository of countries.
 * s - pointer to the service
 * name - string, name of the country
 * continent - string, the continent from where the country is
 * population - double, the countries population
 * return: 1 - if the country was added successfully
 *         0 - otherwise, if it already exists*/
int add_country_srv(Service* s, char* name, char* continent, double population);

/**
 * Deletes a country from the repository of countries.
 * s - pointer to the service
 * name - string, name of the country(unique)
 * return: 1 - if the country was deleted successfully
 *         0 - otherwise, if it doesn't exist*/
int delete_country_srv(Service* s, char* name);

/**
 * Updates a country's population
 * s - service
 * name - the name of the country
 * new_population - the new number that replaces the old one
 * return: -1 - if update unsuccessful
 *          1 - otherwise*/
int update_no_migration_srv(Service* s, char* name, double new_population);

/**
 * Updates two countries' populations by migration
 * s - service
 * country1 - string, the name of the country from where the migration is made
 * country2 - string, the name of the country to where the migration is made
 * population_leaving - double, the number of people leaving from country1 to country2
 * return: 1 - if update successful
 *         0 - otherwise*/
int update_with_migration_srv(Service* s, char* country1, char* country2, double population_leaving);

/**
 * Stores in a dynamic array the countries that contain a given string
 * s - pointer, service
 * string[] - char, the given string
 * return: dynamic array of countries with the above mentioned property.*/
DynamicArray* display_countries_containing_given_string_srv(Service* s, char string[]);

/**   lab3 activity
 * Returns a dynamic array of counties sorted ascending by name
 * s - service
 * */
DynamicArray* lab3_activity(Service* s);

/**
 * Sorts ascending a dynamic array by the number of population of the countries
 * v - dynamic array*/
void sort_ascending_by_population(DynamicArray* v);

/**
 * Sorts descending a dynamic array by the number of population of the countries
 * v - dynamic array*/
void sort_descending_by_population(DynamicArray* v);

/**
 * Stores in a dynamic array the countries that have a greater population than a given one.
 * s - pointer, service
 * population - double, the given population
 * return: the dynamic array with the countries with the above property.*/
DynamicArray* display_countries_by_population_srv(Service* s, double population);

/**
 * Stores in a dynamic array the countries the are on a given continent and have greater population than a given
 * population.
 * s - pointer, service
 * continent[] - string, the given continent
 * population - double, the given population nr
 * return: the dynamic array with the countries with the above property.*/
DynamicArray* display_countries_on_given_continent_srv(Service* s, char continent[], double population);

DynamicArray* display_by_nr_letters(Service* s, int nr);

/**
 * Undo s the last performed operation.
 * s - pointer, service
 * Return : 0 - success
 *         -1 - error
 *          1 - no more undo's*/
int undo(Service* s);


/**
 * Redo s the last undo.
 * s - pointer, service
 * Return : 0 - success
 *         -1 - error
 *          1 - no more redo s*/
int redo(Service* s);


