#include "DynamicArray.h"
#include <stdlib.h>
#include <assert.h>

DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionType destroyElemFct)
{
    DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
    // make sure that the space was allocated
    if (da == NULL)
        return NULL;
    da->capacity = capacity;
    da->size = 0;

    // allocate space for the elements
    da->elems = (TElem*)malloc(capacity * sizeof(TElem));
    if (da->elems == NULL)
        return NULL;

    // initialize the function pointer
    da->destroyElemFct = destroyElemFct;

    return da;
}

void destroy(DynamicArray* arr)
{
    if (arr == NULL)
        return;

    // deallocate each of the elements - if we decide that the dynamic array is responsible with this
    for (int i = 0; i < arr->size; i++)
        arr->destroyElemFct(arr->elems[i]);

    // free the space allocated for the elements
    free(arr->elems);
    arr->elems = NULL;

    // free the space allocated for the dynamic array
    free(arr);
    arr = NULL;
}

/// Resizes the array, allocating more space.
/// If more space cannot be allocated, returns -1, else it returns 0.
int resize(DynamicArray* arr)
{
    if (arr == NULL)
        return -1;

    arr->capacity *= 2;

    // version 2 - allocate new memory, copy everything and deallocate the old memory
    TElem* aux = (TElem*)malloc(arr->capacity * sizeof(TElem));
    if (aux == NULL)
        return -1;
    for (int i = 0; i < arr->size; i++)
        aux[i] = arr->elems[i];
    free(arr->elems);
    arr->elems = aux;

    return 0;
}

void add(DynamicArray* arr, TElem t)
{
    if (arr == NULL)
        return;
    if (arr->elems == NULL)
        return;

    // resize the array, if necessary
    if (arr->size == arr->capacity)
        resize(arr);
    arr->elems[arr->size++] = t;
}

void delete(DynamicArray* arr, int pos)
{
    if (arr == NULL || pos < 0 || pos >= arr->size)
        return;

    arr->destroyElemFct(arr->elems[pos]);

    // !!! Do this only if we delete any element but the last
    if (pos != arr->size - 1)
        arr->elems[pos] = arr->elems[arr->size - 1];
    arr->size--;

}

int get_length(DynamicArray* arr)
{
    if (arr == NULL)
        return -1;

    return arr->size;
}

TElem get(DynamicArray* arr, int pos)
{
    if (arr == NULL || pos < 0)
        return NULL;
    return arr->elems[pos];
}

// ------------------------------------------------------------------------------------------------------------