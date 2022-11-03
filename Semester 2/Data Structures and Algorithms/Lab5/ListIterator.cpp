#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list)
{
    this->currentValue = NULL_TCOMP;
    this->stackSize = 0;
    this->stack = new Node[list.numberOfValues];
    int current = list.root;
    while (current != -1)
    {
        this->stack[stackSize++] = list.tree[current];
        current = list.tree[current].leftPos;
    }
    if (this->stackSize)
        this->currentValue = stack[stackSize-1].element;
}
/// O(n) , n - length of tree

void ListIterator::first(){
    this->currentValue = NULL_TCOMP;
    this->stackSize = 0;
    int current = list.root;
    while (current != -1)
    {
        this->stack[stackSize++] = list.tree[current];
        current = list.tree[current].leftPos;
    }
    if (this->stackSize)
        this->currentValue = stack[stackSize - 1].element;
}
/// O(n) , n - length of tree

void ListIterator::next(){
    if (!valid())
        throw exception();
    this->stackSize--;
    Node node = this->stack[stackSize];  /// pop
    if (node.rightPos != -1)
    {
        int current = node.rightPos;
        while (current != -1)
        {
            this->stack[stackSize++] = list.tree[current];
            current = list.tree[current].leftPos;
        }
    }
    if (this->stackSize)
        this->currentValue = stack[stackSize - 1].element;
    else
        this->currentValue = NULL_TCOMP;
}
/// O(n)

bool ListIterator::valid() const{
    return this->currentValue != NULL_TCOMP;
}
/// Theta(1)

TComp ListIterator::getCurrent() const{

    return this->currentValue;
}
/// Theta(1)