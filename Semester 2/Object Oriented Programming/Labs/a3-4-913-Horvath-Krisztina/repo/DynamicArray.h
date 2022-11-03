# pragma once
#define CAPACITY 10

typedef void* TElem;
typedef void (*DestroyElementFunctionType)(void*);

typedef struct
{
    TElem* elems;
    int size;			/// actual length of the array
    int capacity;		/// maximum capacity of the array
    DestroyElementFunctionType destroyElemFct; /// function pointer to the function responsible with deallocating the elements stored in the array
} DynamicArray;

/**
Creates a dynamic array of generic elements, with a given capacity.
capacity - Integer, maximum capacity for the dynamic array.
name - destroyElemFct Function pointer, of type DestroyElementFunctionType. The function that deals with deallocating the elements of the array.
return: A pointer the the created dynamic array.*/
DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionType destroyElemFct);

/**
Destroys the dynamic array.
name - arr The dynamic array to be destoyed.
return: A pointer the the created dynamic array.*/
void destroy(DynamicArray* arr);

/**Adds a generic to the dynamic array.
name - arr The dynamic array.
name - p The planet to be added.*/
void add(DynamicArray* arr, TElem t);

/// <summary>
/// Deletes an element from a given position in the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="pos">The position from which the element must be deleted. The position must be valid.</param>
void delete(DynamicArray* arr, int pos);

/// <summary>
/// Returns the length of the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
int get_length(DynamicArray* arr);

/// <summary>
/// Returns the element on a given position.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="pos">The position - must be a valid position.</param>
/// <returns>The element on the given position.</returns>
TElem get(DynamicArray* arr, int pos);