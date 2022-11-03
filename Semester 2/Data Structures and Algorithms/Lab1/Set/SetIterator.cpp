#include "SetIterator.h"
#include "Set.h"
#include <exception>
using namespace std;

SetIterator::SetIterator(const Set& m) : set(m)
{
    first();
}
/// Theta(1)

///first actual value from the set(first elem that's true)
void SetIterator::first() {
	this->index = 0;
    while(valid() && !this->set.elements[this->index])
        this->index++;
}
/// BC: Theta(1)  - first elem from the dynamic array belongs to the set
/// WC: Theta(total vector size) - no true elems in the dynamic array
/// Theta(total vector size)

void SetIterator::next() {
    /// the next nr from the set
    if (valid() == false)
        throw exception();
    else {
        this->index++;
        while(!this->set.elements[this->index] && valid())
            this->index++;
    }
}
/// BC: Theta(1)
/// WC: O(actual size of vector)
/// Total O(actual size of vector)

void SetIterator::previous(){
    this->index--;
    while(!this->set.elements[this->index] && valid())
        this->index--;
    if(!valid())
        throw exception();
}
/// BC:Theta(1)
/// WC O(actual size of vector)
/// Total O(actual size of vector)

TElem SetIterator::getCurrent()
{
    /// the nr from the set
	if(valid() == false)
        throw exception();
	else
        return this->index + this->set.left;
}
/// Theta(1)

bool SetIterator::valid() const {
	if(index >= 0 && this->index <= this->set.right - this->set.left)
        ///changed here from get_position()
        return true;
	return false;
}
/// Theta(1)



