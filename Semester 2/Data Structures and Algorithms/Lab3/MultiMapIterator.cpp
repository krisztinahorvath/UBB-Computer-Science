#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	pos = col.data.head;
}
/// Theta(1)

TElem MultiMapIterator::getCurrent() const{
	if(!this->valid())
        throw exception();
    return col.data.nodes[pos].info;
}
/// Theta(1)

bool MultiMapIterator::valid() const {
    if(pos != -1)
        return true;
    else
        return false;
}
/// Theta(1)

void MultiMapIterator::next() {
	if(!this->valid())
        throw exception();
    pos = col.data.nodes[pos].next;
}
/// Theta(1)

void MultiMapIterator::first() {
	pos = col.data.head;
}
/// Theta(1)

void MultiMapIterator::jumpForward(int k) {
    if(!this->valid() || k <= 0)
        throw exception();

    while(this->valid() && k != 0) {
        this->next();
        k--;
    }
}
/// Theta(1)
/// O(k)


