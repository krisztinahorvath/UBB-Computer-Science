#pragma once

#include "Country.h"

typedef enum {
    ADD,
    DELETE,
    UPDATE_NO_MIGRATION,
    UPDATE_MIGRATION
} opType;

typedef struct {
    opType type;
    Country* c;
    double population;  /// the number of people that migrate/the updated version of the population
    char name[50]; ///the name of the country to where the migration is made
} Operation;


/**
 * Creates a new operation, update, delete etc
 * type - opType, the type of the operation(ADD, DELETE etc)
 * c - country on which the operation was performed
 * return: a new operation*/
Operation* createOperation(opType type, Country* c);

/**
 * Destroys the operation
 * o - operation to be destroyed*/
void destroyOperation(Operation* o);

/**
 * Returns the type of the operation
 * o - operation*/
opType getOpType(Operation* o);

/**
 * Return the country on which the operation was performed
 * o - operation*/
Country* getOpObject(Operation* o);
