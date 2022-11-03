#ifndef A3_4_POPULATION_H
#define A3_4_POPULATION_H

typedef struct
{
    char* name;
    char* continent;
    double population;
} Country;

/**
 * Creates a country given the name, continent and population.
 * name - string, name of the country
 * continent - string, continent from where the country belongs
 * return: an object of type country*/
Country* create_country(char* name, char* continent, double population);

/**
 * Destroys a given country, deallocating the memory occupied by it.
 * c - pointer to a country*/
void destroy_country(Country* c);

/**
 * Gets the name of a country.
 * c - pointer to a country
 * return: the name of country c */
char* get_name(Country* c);

/**
 * Gets the continent of a country.
 * c - pointer to a country
 * return: the continent of a country c*/
char* get_continent(Country* c);

/**
 * Gets the population of a country.
 * c - pointer to a country
 * return: the population of a country c*/
double get_population(Country* c);

/**
 * Stores in a displayable string the result of formatting nicely a countries attributes.
 * c - pointer to a country
 * str[] - string, where we store the result*/
void to_string(Country* c, char str[]);

/**
 * Creates a copy of a country c
 * c - pointer to a country
 * return: a copy of c*/
Country* copy_country(Country* c);

#endif //A3_4_POPULATION_H
