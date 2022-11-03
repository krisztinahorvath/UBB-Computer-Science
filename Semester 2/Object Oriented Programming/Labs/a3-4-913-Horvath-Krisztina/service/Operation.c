#include "Operation.h"
#include "Country.h"
#include <stdlib.h>

Operation* createOperation(opType type, Country * c) {
    Operation* op = malloc(sizeof(Operation));
    op->type = type;

    Country * copyOfC = copy_country(c);
    op->c = copyOfC;

    op->population = 0;
    op->name[0] = "\0";

    return op;
}

void destroyOperation(Operation* o) {
    if (o == NULL)
        return;

    destroy_country(o->c);
    free(o);
}

opType getOpType(Operation* o) {
    if (o == NULL)
        return -1;
    return o->type;
}

Country* getOpObject(Operation* o) {
    if (o == NULL)
        return NULL;
    return o->c;
}