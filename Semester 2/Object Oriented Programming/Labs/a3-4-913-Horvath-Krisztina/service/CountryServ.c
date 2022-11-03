#include "CountryServ.h"
#include "Operation.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Service* create_service(CountryRepo* r)
{
    Service* s = malloc(sizeof(Service));
    if(s == NULL)
        return NULL;
    s->repo = r;
    s->undo_stack = createDynamicArray(10, &destroyOperation);
    s->redo_stack = createDynamicArray(10, &destroyOperation);

    return s;
}

void destroy_service(Service* s)
{
    if(s == NULL)
        return;

    /// destroy the repo inside the service
    destroy_repo(s->repo);

    destroy(s->undo_stack); /// destroy from DynamicArray.c
    destroy(s->redo_stack);

    /// destroy the actual service
    free(s);

}

int add_country_srv(Service* s, char* name, char* continent, double population)
{
    Country* c = create_country(name, continent, population);
    int res = add_country(s->repo, c);

    if(res == 0) /// the country was added
    {
        Operation* op = createOperation(ADD, c);
        if(op == NULL)
            return -1;
        add(s->undo_stack, op);
    }
    s->redo_stack->size = 0;
    return res;
}

int delete_country_srv(Service* s, char* name)
{
    /// create the operation before deleting the planet (memory of planet will be freed)
    /// OR save a copy of the planet before deleting it

    Country* c = find_by_name(s->repo, name);
    Operation* op = createOperation(DELETE, c);
    if(op == NULL)
        return -1;

    add(s->undo_stack, op);

    s->redo_stack->size = 0;

    return delete_country(s->repo, name);
}

int update_no_migration_srv(Service* s, char* name, double new_population)
{
    Country* c = find_by_name(s->repo, name);
    Operation* op = createOperation(UPDATE_NO_MIGRATION, c);
    if(op == NULL)
        return -1;

    op->population = get_population(c);

    add(s->undo_stack, op);

    s->redo_stack->size = 0;

    return update_no_migration(s->repo, name, new_population);
}

int update_with_migration_srv(Service* s, char* country1, char* country2, double population_leaving)
{
    Country* c = find_by_name(s->repo, country1);
    Operation* op = createOperation(UPDATE_MIGRATION, c);

    if(op == NULL)
        return -1;

    add(s->undo_stack, op);
    op->population = population_leaving;
    strcpy(op->name, country2);

    s->redo_stack->size = 0;

    return update_with_migration(s->repo, country1, country2, population_leaving);
}

/**
 * Transforms a string of letters to lower case letters.
 * string - pointer to a string
 * return: the lowercase string
 * */
char* to_lower(char* string)
{
    char* lower = malloc(sizeof(char) * strlen(string) + 1);
    strcpy(lower, string);
    for(int i = 0; i < strlen(string); i++)
        if(lower[i] >= 'A' && lower[i] <= 'Z')
            lower[i] = lower[i] - 'A' + 'a';
    return lower; ///todo deallocate
}

/**
 * Verifies if a string(name) contains another string(string). The verification is case insensitive.
 * name - the string we are looking in
 * string - the string we are trying to find
 * return: 0 - string not found
 *         1 - string found*/
int name_contains_given_string(char name[], char string[])
{
    if(strstr(name, string) != NULL)   /// took out to_lower
        return 1;
    return 0;
}

/**
 * Creates a deep copy of an array of type DynamicArray
 * */
DynamicArray* deep_copy(DynamicArray* v)
{
    DynamicArray* copy = createDynamicArray(v->capacity, (DestroyElementFunctionType) &destroy);
    for(int i = 0; i < v->size; i++)
        copy->elems[i] = copy_country(v->elems[i]);

    copy->size = v->size;
    return copy;
}

DynamicArray* display_countries_containing_given_string_srv(Service* s, char string[])
{
    DynamicArray* v = createDynamicArray(2, &destroy);
    int n = get_repo_length(s->repo);
    int count = 0;
    for(int i = 0; i < n; i++){
        char name[50];

        Country* c = get_country_on_pos(s->repo, i);
        strcpy(name, get_name(c));

        if(name_contains_given_string(name, string) == 1)
            v->elems[count++] = c;
    }
    v->size = count;
    return v;
}

DynamicArray* lab3_activity(Service* s)
{
    Country* aux = malloc(sizeof(Country));
    DynamicArray* v = malloc(sizeof(DynamicArray));
    v = deep_copy((DynamicArray *) s->repo->countries);

    int n = v->size;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            char name1[50], name2[50];
            strcpy(name1,  get_name(v->elems[i]));
            strcpy(name2, get_name(v->elems[j]));
            if(strcmp(name1, name2) > 0)
            {
                aux = copy_country(v->elems[i]);
                v->elems[i] = copy_country(v->elems[j]);
                v->elems[j] = aux;
            }
        }
    }


//    destroy_country(aux);
    return v;
}

CountryRepo* get_repo(Service* s)
{
    return s->repo;
}

/**
 * Checks if the continent of country c is the same with a given continent.
 * c - Country*, a country
 * continent[] - string, a continent
 * return: 1 - if the continent of c is the same with continent[]
 *         0 - otherwise*/
int check_continent(Country* c, char continent[])
{
    if(strcmp(get_continent(c), continent) == 0)
        return 1;
    return 0;
}

void sort_ascending_by_population(DynamicArray* v)
{
    Country* aux = malloc(sizeof(Country));
    int n = v->size;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(get_population(v->elems[i]) > get_population(v->elems[j]))
            {
                aux = copy_country(v->elems[i]);
                v->elems[i] = copy_country(v->elems[j]);
                v->elems[j] = aux;
            }
        }
    }
}

void sort_descending_by_population(DynamicArray* v)
{
    Country* aux = malloc(sizeof(Country));
    int n = v->size;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(get_population(v->elems[i]) < get_population(v->elems[j]))
            {
                aux = copy_country(v->elems[i]);
                v->elems[i] = copy_country(v->elems[j]);
                v->elems[j] = aux;
            }
        }
    }
}

DynamicArray* display_countries_by_population_srv(Service* s, double population)
{
    DynamicArray* v = createDynamicArray(10, (DestroyElementFunctionType) &destroy);
    int n = get_repo_length(s->repo);
    int count = 0;
    for(int i = 0; i < n; i++){
        Country* c = get_country_on_pos(s->repo, i);
        if(get_population(c) > population)
            v->elems[count++] = c;
        destroy_country(c);
    }
    v->size = count;
    return v;
}

DynamicArray* display_countries_on_given_continent_srv(Service* s, char continent[], double population)
{
    DynamicArray* v = createDynamicArray(10, (DestroyElementFunctionType) &destroy);
    int n = get_repo_length(s->repo);
    int count = 0;
    for(int i = 0; i < n; i++){
        Country* c = get_country_on_pos(s->repo, i);
        if(check_continent(c, continent) == 1 && get_population(c) > population)
            v->elems[count++] = c;
    }
    v->size = count;
    return v;
}

DynamicArray* display_by_nr_letters(Service* s, int nr)
{
    DynamicArray* v = createDynamicArray(10, (DestroyElementFunctionType) &destroy);
    int n = get_repo_length(s->repo);
    int count = 0;
    for(int i = 0; i < n; i++){
        Country* c = get_country_on_pos(s->repo, i);
        if(strlen(get_name(c)) == nr)
            v->elems[count++] = c;
    }
    v->size = count;

    return v;
}

int undo(Service* s)
{
    if (s == NULL)
        return -1; /// error

    int stackSize = get_length(s->undo_stack);
    if (stackSize == 0)
        return 1; /// no more undo's
    Operation* op = get(s->undo_stack, stackSize - 1);
    if (op == NULL)
        return -1;
    Country * c = getOpObject(op);
    if (c == NULL)
        return -1;

    if (getOpType(op) == ADD)
        delete_country(s->repo, get_name(c));
    else if (getOpType(op) == DELETE)
        /// must have a copy, because c will be destroyed when deleting
        /// the operation from the stack
        add_country(s->repo, copy_country(c));
    else if(getOpType(op) == UPDATE_NO_MIGRATION)
        update_no_migration(s->repo, get_name(c), op->population);
    else if(getOpType(op) == UPDATE_MIGRATION)
        update_with_migration(s->repo,op->name, get_name(c), op->population);

    /// remove the operation from "the stack"
    /// should be added to the redo stack
    add(s->redo_stack, op);

    delete(s->undo_stack, stackSize - 1);

    return 0;
}

int redo(Service* s)
{
    if (s == NULL)
        return -1; /// error

    int stackSize = get_length(s->redo_stack);
    if (stackSize == 0)
        return 1; /// no more redo's
    Operation* op = get(s->redo_stack, stackSize - 1);
    if (op == NULL)
        return -1;
    Country * c = getOpObject(op);
    if (c == NULL)
        return -1;

    if (getOpType(op) == ADD)
        add_country(s->repo, copy_country(c));
    else if (getOpType(op) == DELETE)
        /// must have a copy, because c will be destroyed when deleting
        /// the operation from the stack
        delete_country(s->repo, get_name(c));
    else if(getOpType(op) == UPDATE_NO_MIGRATION)
        update_no_migration(s->repo, get_name(c), op->population);
    else if(getOpType(op) == UPDATE_MIGRATION)
        update_with_migration(s->repo,op->name, get_name(c), op->population);

    /// remove the operation from "the stack"
    /// should be added to the redo stack
    add(s->undo_stack, op);

    delete(s->redo_stack, stackSize - 1);


    return 0;
}