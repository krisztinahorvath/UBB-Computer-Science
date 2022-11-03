#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;

struct Pair{
    TElem elem;
    int freq;
};

struct HashTable{
    int nr_elems; /// nr of elems in the hash table
    int m;  /// capacity
    Pair* elements;
};

class BagIterator; 
class Bag {

private:
    HashTable table;

	//DO NOT CHANGE THIS PART
	friend class BagIterator;

private:
    int hash(TElem e, int i);
    void resize();
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurrence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appears is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;


    //removes completely all elements that appear multiple times in the Bag (all their occurrences areremoved)
    //returns the number of removed elements
    int removeElementsWithMultipleOccurrences();


	//destructor
	~Bag();
};