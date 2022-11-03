//#include "DynamicVector.h"
//
//
////template <typename T>
////DynamicVector<T>::DynamicVector(int capacity):size{0}, capacity{capacity}
////{
////    this->elems = new T[this->capacity];
////}
//
//template <typename T>
//void DynamicVector<T>::resize() {
//    T* new_vector = new T[this->capacity*2];
//    for(int i = 0; i < this->size; i++)
//        new_vector[i] = this->elems[i];
//
//    this->capacity*=2;
//    delete[] this->elems;
//    this->elems = new_vector;
//}
//
//template <typename T>
//DynamicVector<T>::DynamicVector(const DynamicVector& v)
//{
//    this->size = v.size;
//    this->capacity = v.capacity;
//    this->elems = new T[this->capacity];
//    for(int i = 0; i < this->size; i++)
//        this->elems[i] = v.elems[i];
//}
//
//template <typename T>
//DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector& v)
//{
//    if( this == &v)
//        return *this;
//
//    this->capacity = v.capacity;
//    this->size = v.size();
//
//    delete[] this->elems;
//    this->elems = new T[this->capacity];
//    for(int i = 0; i < this->size; i++)
//        this->elems[i] = v.elems[i];
//
//    return *this;
//}
//
//template <typename T>
//DynamicVector<T>::~DynamicVector() {
//    delete[] this->elems;
//}
//
//template <typename T>
//void DynamicVector<T>::add(const T &elem) {
//    /// can't add a movie twice
////    for(int i = 0; i < this->size; i++)
////        if(this->elems[i].get_title() == elem.get_title())
////            break;
//    if(this->size == this->capacity)
//        resize();
//    this->elems[this->size++] = elem;
//}
//
//template <typename T>
//void DynamicVector<T>::remove(const int pos) {
//    int index = 0;
//    T* new_vector = new T[this->capacity];
//    for(int i = 0; i < this->size; i++){
//        if(index == pos)
//            index++;
//        new_vector[i] == this->elems[index];
//        index++;
//    }
//    delete[] this->elems;
//    this->elems = new_vector;
//    this->size--;
//
//}
//
//template <typename T>
//void DynamicVector<T>::update(const int pos, const T elem) {
//    this->elems[pos] = elem;
//}
//
//template <typename T>
//T DynamicVector<T>::get_elem(const int pos) const {
//    return this->elems[pos];
//}
//
//
//
//
//
