#include "Set.h"
#include "SetITerator.h"

Set::Set() {
    this->capacity = 1;
    this->length = 0;
    this->left = 0;
    this->right = 0;
    this->elements = new BElem[this->capacity];
}
/// Theta(1)

void Set::resize() {
    auto* resized_array = new BElem[this->capacity * 2];

    for(int i = 0; i < this->right - this->left + 1; i++)
        resized_array[i] = this->elements[i];

    this->capacity *= 2;

    for(int i = this->right-this->left + 1; i < this->capacity; i++)
        resized_array[i] = false;

    delete[] this->elements;
    this->elements = resized_array;
}
/// Theta(old_capacity*2)

bool Set::add(TElem elem){

    if(this->size() == 0){ /// the first elem added to the array
        this->length = 1;
        this->left = elem;
        this->right = elem;
        this->elements[0] = true;
        return true;
    }
    if(search(elem))  /// can't add it twice
        return false;

    if(this->capacity == this->right - this->left)
        resize();

    if(elem >= this->left && elem <= this->right){    /// if something was added to the array
        this->elements[elem - this->left] = true;
        this->length++;
        return true;
    }
    else if(elem < this->left){
        /// create array to the left, aka move old elems to the right
        int pos = this->right - this->left;
        while(this->left > elem)
        {
            /// move the entire array with a position to the right

            for(int i = pos; i >= 0; i--)
                this->elements[i+1] = this->elements[i];

            this->elements[0] = false;
            this->left--;
            pos++;

            if(this->capacity == this->right - this->left)
                resize();
        }

        this->elements[0] = true;
        this->left = elem; /// only the left part of the interval changes
        this->length++;
        return true;
    }
    else if(elem > this->right){
        /// create more space to the left
        int pos = this->right - this->left;
        while(this->right < elem){
            this->elements[++pos] = false;
            this->right++;

            if(this->capacity == this->right - this->left)
                resize();
        }

        this->elements[pos] = true; /// elem will be the last elem of the array
        this->length++;

        return true;
    }

    return false;
}
/// BC: Theta(1) - for the first elem
/// WC: O(n^n) - n being the (left-nr) nr < left, when the number doesn't belong to the [left, right] interval and we have to move elems to the right so that we have space for the elems to the left
/// O(n^n)

bool Set::remove(TElem elem) {
    if(!search(elem))  /// if the elem does not exist
        return false;

    int pos = elem - this->left;
    this->elements[pos] = false;
    this->length--;

    return true;
}
/// Theta(1)

bool Set::search(TElem elem) const {
    if(elem >= this->left && elem <= this->right)
        if(this->elements[elem - this->left] == true)
            return true;
    return false;
}
/// Theta(1)

int Set::size() const {
    return this->length;
}
/// Theta(1)

bool Set::isEmpty() const {
    if(this->length == 0)
        return true;
    return false;
}
/// Theta(1)

SetIterator Set::iterator() const {
    return SetIterator(*this);
}
/// Theta(1)

Set::~Set() {
    delete[] this->elements;
}
/// Theta(1)