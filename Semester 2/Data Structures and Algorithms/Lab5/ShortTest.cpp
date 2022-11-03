#include <assert.h>

#include "ListIterator.h"
#include "SortedIndexedList.h"

using namespace std;

bool relation1(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedIndexedList list = SortedIndexedList(relation1);
	assert(list.size() == 0);
	assert(list.isEmpty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.isEmpty());
    ListIterator iterator = list.iterator();
    assert(iterator.valid());
    iterator.first();
    assert(iterator.getCurrent() == 1);
    iterator.next();
    assert(!iterator.valid());
    iterator.first();
    assert(iterator.valid());
    assert(list.search(1) == 0);
    assert(list.remove(0) == 1);
    assert(list.size() == 0);
    assert(list.isEmpty());

    SortedIndexedList l = SortedIndexedList(relation1);
    l.add(2);
    l.add(0);
    l.add(5);
    l.add(4);
    /// 0 2 4 5
    assert(l.size() == 4);

    l.removeBetween(1, 2);
    assert(l.size() == 3);
    assert(l.search(0) == false);
    assert(l.search(4) == true);

    try{
        l.removeBetween(2, 10);
    }
    catch(...)
    {

    }
}

