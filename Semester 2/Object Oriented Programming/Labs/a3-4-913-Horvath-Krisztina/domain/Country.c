#include "Country.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Country* create_country(char* name, char* continent, double population)
{
    Country* c = malloc(sizeof(Country));
    if(c == NULL)
        return NULL;

    c->name = malloc(sizeof(char) * strlen(name) + 1);
    if(c->name != NULL)
        strcpy(c->name, name);

    c->continent = malloc(sizeof(char) * strlen(continent) + 1);
    if(c->continent != NULL)
        strcpy(c->continent, continent);

    c->population = population;

    return c;
}

void destroy_country(Country* c)
{
    if (c == NULL)
        return;

    free(c->name);
    free(c->continent);

    free(c);
}

char* get_name(Country* c)
{
    if(c == NULL)
        return NULL;
    return c->name;
}

char* get_continent(Country* c)
{
    if(c == NULL)
        return NULL;
    return c->continent;
}

double get_population(Country* c)
{
    if(c == NULL)
        return -1;
    return c->population;
}

void to_string(Country* c, char str[])
{
    if(c == NULL)
        return;
    sprintf(str, "%s, %s, %.2lf\n",
            c->name, c->continent, c->population);
}

Country* copy_country(Country* c)
{
    if (c == NULL)
        return NULL;
    return create_country(c->name, c->continent, c->population);
}
