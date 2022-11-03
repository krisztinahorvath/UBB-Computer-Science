# DSA-lab4

Implement in C++ the given container (ADT) using a given representation and a hashtable with a 
given collision resolution (separate chaining, coalesced chaining, open addressing) as a data structure. 
You are not allowed to use any container or data structure from STL or from any other library.
Do not implement a separate class for the hashtable (or dynamic array, or anything), implement 
the container directly!
The hashtable has to be dynamic: no matter what collision resolution has to be used, set a 
threshold for α and resize and rehash the table when the actual load factor is higher than α.



15. ADT Bag – using a hashtable with open addressing (quadratic probing) in which (unique 
element, frequency) pairs are stored. In the constructor of the iterator create an array of 
(element, frequency) pairs, sorted by the element and use that array for iterating.
