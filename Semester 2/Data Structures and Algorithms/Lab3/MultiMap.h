#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;


class MultiMap
{
	friend class MultiMapIterator;

private: /// todo elems aren't consecutive => (0, 2) ; empty_pos; (0,7); empty_pos; (10, 90)
    struct DLLANode
    {
        TElem info; /// pair<TKey, TValue>
        int next;
        int prev;

        DLLANode();
    };

    struct DLLA
    {
        DLLANode *nodes;
        int capacity;
        int head;
        int tail;
        int first_empty;
        int size; /// the number of elems we have in the DLLA
        int pos_nr; /// the number of positions in the array so far(empty + non empty)

        DLLA();

        DLLANode& operator[](int pos) const;
    };

	DLLA data;

public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

    void empty();

	//descturctor
	~MultiMap();
};

