#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
    data[0].prev = -1;
    data[0].next = 0;
    for(int i = 1; i < data.capacity - 1; i++){
        data[i].next = i + 1;
        data[i].prev = i - 1;
    }
    data[data.capacity - 1].prev = data.capacity -2;
    data[data.capacity - 1].next = -1;
}


void MultiMap::add(TKey c, TValue v) {
    if(data.head == -1){ /// adding the first pair
        data.head = data.first_empty;
        data.tail = data.first_empty;
//        data.head = 0;
//        data.tail = 0;
        data.nodes[data.head].info.first = c;
        data.nodes[data.head].info.second = v;

        data.nodes[data.head].prev = -1;
        data.nodes[data.head].next = -1;

        data.first_empty++; /// only for the first elem
        data.size++;
        data.pos_nr++;
        return;
    }

    if(data.size == data.capacity){ /// resize
        DLLANode *new_list = new DLLANode[2*data.capacity];
        for(int i = 0; i < data.capacity; i++)
            new_list[i] = data.nodes[i];

        for(int i = data.capacity; i < data.capacity*2; i++){
            data[i].next = i + 1;
            data[i].prev = i - 1;
        }

        data.capacity *= 2;
        delete[] data.nodes;
        data.nodes = new_list;
    }
    int new_first_empty = data.nodes[data.first_empty].next;
    if(data.first_empty == data.pos_nr) { /// there is no empty pos in the array, we can add only to the end
        data.nodes[data.first_empty].next = -1;

        data.nodes[data.first_empty].info.first = c; /// setting the elem
        data.nodes[data.first_empty].info.second = v;
        /// prev is the same??


        int current = data.tail;

        data.tail = data.pos_nr; /// set the tail to the new elems pos

        int found_prev = 0;
        while(current != -1){
            if(data.nodes[current].info != NULL_TELEM){
                data.nodes[data.first_empty].prev = current;
                data.nodes[current].next = data.first_empty; /// setting the next of the elem that is prev to the elem just added
                found_prev = 1;
                break;
            }
            current = data.nodes[current].prev;
        }
        if(found_prev == 0)
            data.nodes[data.first_empty].prev = -1;

        data.pos_nr++;
        data.size++;
    }
    else{ /// if the empty pos is somewhere inside the array
        data.nodes[data.first_empty].info.first = c; /// setting the elem
        data.nodes[data.first_empty].info.second = v;

        /// finding next and prev for this elem
        int found_prev = 0;
        for(int current = data.first_empty -1; current >= 0; current--){
            if(data.nodes[current].info != NULL_TELEM){
                data.nodes[data.first_empty].prev = current;
                data.nodes[current].next = data.first_empty;
                found_prev = 1;
                break; /// todo??
            }
        }
        if(found_prev == 0)
            data.nodes[data.first_empty].prev = -1;

        data.first_empty = new_first_empty;

        data.size++;
    }

    /// finding the next empty pos

    int found_pos = 0;
    for(int i = 0; i < this->data.pos_nr; i++) /// finding the next empty position
        if(data.nodes[i].info == NULL_TELEM){
            data.first_empty = i;
            found_pos = 1;
            break;
        }

    if(found_pos == 0)
        data.first_empty = data.pos_nr;
}
/// O(n)


bool MultiMap::remove(TKey c, TValue v) {
    if(this->isEmpty())
        return false;

    int current = data.head;
    while(current != -1){
        if(data.nodes[current].info.first == c && data.nodes[current].info.second == v){
            if(current == data.tail){    /// if we delete the last elem
                data.tail = data.nodes[data.tail].prev;
                data.nodes[data.tail].prev = data.nodes[current].prev; /// set next and prev
                data.nodes[data.tail].next = -1; /// todo find the previous for this elem
            }
            else{
                if(current == data.head){ /// if we delete the first elem
                    data.head = data.nodes[current].next;
                    data.nodes[data.head].prev = -1;
                }
                else{
                    int prev_pos = data.nodes[current].prev;
                    int next_pos = data.nodes[current].next;
                    data.nodes[prev_pos].next = next_pos;
                    data.nodes[next_pos].prev = prev_pos;
                }
            }
            data.nodes[current].prev = -1;
            data.nodes[current].next = data.first_empty; /// todo???

            data.first_empty = current;

            data.size--;

            if(data.size == 0)
                data.head = -1;

            data.nodes[current].info = NULL_TELEM; /// todo???
            return true;
        }
        current = data.nodes[current].next;
    }
    return false;
}
/// Theta(1)
/// O(size)

vector<TValue> MultiMap::search(TKey c) const {
    std::vector<TValue> v;

    int current = data.head;
    while(current != -1 && current <= data.tail){
        if(data.nodes[current].info.first == c)
            v.push_back(data.nodes[current].info.second);
        current++;
    }
    return v;
}


int MultiMap::size() const {
    return this->data.size;
}
/// Theta(1)

bool MultiMap::isEmpty() const {
    if(data.head == -1)
        return true;
    return false;
}
/// Theta(1)

MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}
/// Theta(1)

MultiMap::~MultiMap() = default;
/// Theta(1)


void MultiMap::empty() {
    MultiMapIterator it = iterator();
    it.first();
    while(it.valid() && this->size()!=0){
        TElem node = it.getCurrent();
        remove(node.first, node.second);
    }
}
/// O(n)


MultiMap::DLLANode &MultiMap::DLLA::operator[](int pos) const {
    return this->nodes[pos];
}
/// Theta(1)


MultiMap::DLLA::DLLA() {
    this->capacity = 10;
    this->size = 0;
    this->nodes = new DLLANode[this->capacity];
    this->first_empty = 0;
    this->pos_nr = 0;
    this->head = -1;
    this->tail = -1;
}
/// Theta(1)


MultiMap::DLLANode::DLLANode(): info{NULL_TELEM}, prev{-1}, next{-1}{} /// todo was prev 0, next 0
/// Theta(1)