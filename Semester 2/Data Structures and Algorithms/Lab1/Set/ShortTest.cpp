#include "ShortTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"
#include <iostream>

void testAll() { 
	Set s;
	assert(s.isEmpty() == true);
	assert(s.size() == 0);
    /// added tests for previous
    SetIterator it_prev = s.iterator();
	assert(s.add(5)==true);
	assert(s.add(1)==true);    /// previous = 5
	it_prev.first(); /// it = 0
    it_prev.next();/// it = 1
    it_prev.next(); /// it = 2
    it_prev.previous(); /// it = 1
    assert(it_prev.getCurrent() == 5);
    it_prev.next(); /// it = 2
    /// tests for previous
	assert(s.add(10)==true);  /// it = 3
	it_prev.next();

	assert(s.add(7)==true);
	assert(s.add(1)==false);
	assert(s.add(10)==false);
    assert(s.add(-3)==true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);

	SetIterator it = s.iterator();
	it.first();
	int sum = 0;
	while (it.valid()) {
		TElem e = it.getCurrent();
		sum += e;
		it.next();
	}
	assert(sum == 19);

}

