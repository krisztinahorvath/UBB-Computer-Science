#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
    Pair* elems;

	BagIterator(const Bag& c);
    int pos;
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
