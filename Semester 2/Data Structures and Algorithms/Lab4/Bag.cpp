#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	table.nr_elems = 0;
    table.m = 8;
    table.elements = new Pair[table.m];
    for(int i = 0; i < table.m; i++){
        table.elements[i].elem = NULL_TELEM;
        table.elements[i].freq = 0;
    }
}
/// Theta(capacity)

void Bag::add(TElem elem) {
	bool found = false;
    for(int i = 0; i < table.m; i++){
        if(table.elements[i].elem == elem){
            table.elements[i].freq++;
            table.nr_elems++;
            found = true;
            break;
        }
    }
    if(!found){
        /// we hash positions, increasing the 'i' parameter until an empty pos is found
        int i = 0;
        int pos = hash(elem, 0);
        while(i < table.m && table.elements[pos].elem != -111111){
            i++;
            pos = hash(elem, i);
        }

        if(i == table.m)
        {
            int old_nr = table.nr_elems;
            this->resize();
            this->add(elem);
            table.nr_elems = old_nr + 1;
        }
        else{
            table.elements[pos].elem = elem;
            table.elements[pos].freq = 1;
            table.nr_elems++; /// todo ???
        }
    }
}
/// BC Theta(1)
/// WC

bool Bag::remove(TElem elem) {
	for(int i = 0; i < table.m; i++)
        if(table.elements[i].elem == elem){
            table.elements[i].freq--;
            if(table.elements[i].freq == 0){
                table.elements[i].elem = NULL_TELEM;
                table.elements[i].freq = NULL_TELEM;
            }
            table.nr_elems--;
            return true;
        }
	return false; 
}
/// BC Theta(1)
/// WC O(m)


bool Bag::search(TElem elem) const {
     for(int i = 0; i < table.m; i++)
         if(table.elements[i].elem == elem)
             return true;
	return false; 
}
/// BC Theta(1)
/// WC O(m)

int Bag::nrOccurrences(TElem elem) const {
	for(int i = 0; i < table.m; i++)
        if(table.elements[i].elem == elem)
            return table.elements[i].freq;
	return 0; 
}
/// BC Theta(1)
/// WC O(m)

int Bag::size() const {
	return table.nr_elems;
}
/// Theta(1)

bool Bag::isEmpty() const {
	if(table.nr_elems == 0)
        return true;
    return false;
}
/// Theta(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
/// Theta(1)

Bag::~Bag() {
//	delete[] table.elements;
}
/// Theta(1)

void Bag::resize() {
    Pair* copy = new Pair[table.m];

    for(int i = 0; i < table.nr_elems; i++)
        copy[i] = table.elements[i];

    table.m *= 2;
    delete[] table.elements;

    table.elements = new Pair[table.m];
    table.nr_elems = 0;
    for(int i = 0; i < table.m; i++){
        table.elements[i].elem = NULL_TELEM;
        table.elements[i].freq = 0;
    }

    /// for this add, resize won't be needed, so it doesn't become recursive
    /// we add each element in the new array because position needs rehashing for the add operation
    for(int i = 0; i < table.m; i++)
        if(copy[i].elem != -111111)
            this->add(copy[i].elem);

}
/// BC Theta(1)
/// WC O(m)

int Bag::hash(TElem e, int i) {
    if(e < 0)
        e = -e;

    //// to be sure of obtaining permutations, c1=c2=0.5, m starts as a power of 2
    return (int(e % table.m + 0.5*i + 0.5*i*i) % table.m);
}
/// Theta(1)

int Bag::removeElementsWithMultipleOccurrences() {
    int count = 0;
    for(int i = 0; i < table.m; i++)
        if(table.elements[i].elem != -111111 && table.elements[i].freq > 1){
            this->remove(table.elements[i].elem);
            count++;
        }
    return count;
}
/// Theta(1)
/// O(m)

