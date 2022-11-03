#include "Matrix.h"
#include "MatrixIterator.h"
#include <exception>
#include <iostream>

using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->lines = nrLines;
    this->columns = nrCols;
    this->list = nullptr;
}
/// Theta(1)

int Matrix::nrLines() const {
	return this->lines;
}
/// Theta(1)

int Matrix::nrColumns() const {
	return this->columns;
}
/// Theta(1)

TElem Matrix::element(int i, int j) const {
	if(i < 0 || i >= this->lines || j < 0 || j >= this->columns)
        throw exception();

    Node* node = search_node(this->list, i, j);

    if(node == nullptr)
        return NULL_TELEM;

    return node->value;
}
/// BC Theta(1)
/// WC O(n)
/// O(n)

TElem Matrix::modify(int i, int j, TElem e) {
	if(i < 0 || i >= this->lines || j < 0 || j >= this->columns)
        throw exception();

    Node* node = search_node(this->list, i, j);
    if(node == nullptr){
        insert_node(&list, i, j, e);
        return NULL_TELEM;
    }

    TElem old_value = node->value;
    node->value = e;
    return old_value;
}
/// BC Theta(1)
/// WC O(n)
/// O(n)

Matrix::~Matrix() {
    delete_node(this->list);
}
/// O(n)

Node *Matrix::search_node(Node * node, int i, int j) const {
    /// binary search
    if(node == nullptr)
        return nullptr;

    else
    if (node->line == i && node->column == j)
        return node;
    else
    if (node->line < i)
        return search_node(node->right, i, j);
    else
    if (node->line == i && node->column < j)
        return search_node(node->right, i, j);
    else
        return search_node(node->left, i, j);

}
/// BC Theta(1)
/// WC O(n)
/// O(n)

Node *Matrix::init_node(int i, int j, TElem value) {
    Node* node = new Node;
    node->line = i;
    node->column = j;
    node->value = value;
    node->left = nullptr;
    node->right = nullptr;

    return node;
}
/// Theta(1)

void Matrix::delete_node(Node *node) {
    if(node == nullptr)
        return;
    if(node->left == nullptr && node->right == nullptr){
        delete node;
        return;
    }

    if(node->left != nullptr)
        delete_node(node->left);
    if(node->right != nullptr)
        delete_node(node->right);

    delete node;

}
/// O(n)

Node *Matrix::insert_node(Node **node, int i, int j, TElem value) {
    if((*node) == nullptr)
        (*node) = init_node(i, j, value);
    else if((*node)->line < i)
        (*node)->right = insert_node(&(*node)->right, i, j, value);
    else if ((*node)->line == i && (*node)->column < j)
        (*node)->right = insert_node(&(*node)->right, i, j, value);
    else
        (*node)->left = insert_node(&(*node)->left, i, j, value);

    return (*node);
}
/// BC Theta(1)
/// WC O(n)
/// O(n)

MatrixIterator Matrix::iterator(int line) const{
    return MatrixIterator(*this, line);
}

/// Theta(1)


