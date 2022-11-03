#pragma once
#include "SortedIndexedList.h"


//DO NOT CHANGE THIS PART
class ListIterator{
    friend class SortedIndexedList;
private:
    const SortedIndexedList& list;
    ListIterator(const SortedIndexedList& list);

    /// InOrder iterator
    Node* stack; /// stack of size equal to the number of nodes in the tree
    int stackSize;
    TComp currentValue;

public:
    void first();
    void next();
    bool valid() const;
    TComp getCurrent() const;

    //destructor
    ~ListIterator() { delete[] stack; }
};

