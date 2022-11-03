#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
    elems = new Pair[bag.table.nr_elems];
    int k = 0;
    for(int i = 0; i < bag.table.m; i++)
        if(bag.table.elements[i].elem != -111111){
            elems[k].elem = bag.table.elements[i].elem;
            elems[k].freq = bag.table.elements[i].freq;
            k++;
        }


	for(int i = 0; i < bag.table.nr_elems - 1; i++)
        for(int j = i + 1; j < bag.table.nr_elems; j++)
            if(elems[i].elem > elems[j].elem)
            {
                Pair aux = elems[i];
                elems[i] = elems[j];
                elems[j] = aux;
            }

    pos = 0;
}
/// O(m) + O(n*n), n the nr of elems in the bag

void BagIterator::first() {
	pos = 0;
}
/// Theta(1)


void BagIterator::next() {
    if(valid())
	    pos++;
    else
        throw exception();
}
/// Theta(1)

bool BagIterator::valid() const {
	if(pos >= 0 && pos < bag.table.nr_elems)
        return true;
	return false;
}
/// Theta(1)

TElem BagIterator::getCurrent() const
{
    return elems[pos].elem;
}
/// Theta(1)