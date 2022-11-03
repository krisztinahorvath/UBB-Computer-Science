#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class MatrixIterator;

struct Node {
   int line;
   int column;
   TElem value;
   Node* left;
   Node* right;
};

class Matrix {

private:
	int lines;
    int columns;

    Node* list; /// list of elems(pointer to the first elem)

    Node* init_node(int i, int j, TElem value);
    Node* insert_node(Node ** node, int i, int j, TElem value);
    Node* search_node(Node* node, int i, int j) const;
    void delete_node(Node* node);

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

    MatrixIterator iterator(int line) const;

    ~Matrix();

};
