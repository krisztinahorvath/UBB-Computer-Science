#pragma once

template <typename T> /// in this case TElem is a movie
class DynamicVector {
private:
    T* elems;
    int capacity{};
    int size{};

    /**
    * Resize function for the dynamic array from the DynamicVector class*/
    void resize();

public:
    /// constructor for a DynamicVector
    DynamicVector(int capacity = 10);

    /// copy constructor
    DynamicVector(const DynamicVector& v);


    DynamicVector& operator=(const DynamicVector& v);

    T& operator[](int index) { return this->elems[index]; }

    /// destructor
    ~DynamicVector();

    /// adds an elem to the dynamic array
    void add(const T& elem);

    /// removes the elem from position pos in the dynamic array
    void remove(const int pos);

    /// update elem on a given position
    void update(const int pos, const T elem);

    /// return elem from given position
    T get_elem(const int pos) const;

    int get_size() const{ return this->size; }

};

template <typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
    this->size = 0;
    this->capacity = capacity;
    this->elems = new T[this->capacity];
}

template <typename T>
void DynamicVector<T>::resize() {
    T* new_vector = new T[this->capacity*2];
    for(int i = 0; i < this->size; i++)
        new_vector[i] = this->elems[i];

    this->capacity*=2;
    delete[] this->elems;
    this->elems = new_vector;
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector& v)
{
    this->size = v.size;
    this->capacity = v.capacity;
    this->elems = new T[this->capacity];
    for(int i = 0; i < this->size; i++)
        this->elems[i] = v.elems[i];
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector& v)
{
    if( this == &v)
        return *this;

    this->capacity = v.capacity;
    this->size = v.size();

    delete[] this->elems;
    this->elems = new T[this->capacity];
    for(int i = 0; i < this->size; i++)
        this->elems[i] = v.elems[i];

    return *this;
}

template <typename T>
DynamicVector<T>&  operator+(DynamicVector<T>& v, const T elem)
{
    v.add(elem);
    return v;
}

template <typename T>
DynamicVector<T>&  operator+(const T elem, DynamicVector<T>& v)
{
    v.add(elem);
    return v;
}

template <typename T>
DynamicVector<T>::~DynamicVector() {
    delete[] this->elems;
}

template <typename T>
void DynamicVector<T>::add(const T &elem) {
    /// can't add a movie twice
    if(this->size == this->capacity)
        resize();
    this->elems[this->size++] = elem;
}

template <typename T>
void DynamicVector<T>::remove(const int pos) {
    for (int i=0; i < this->size; i++)
    {
        if (i == pos)
        {
            for(int j = i; j< this->size - 1; j++)
                this->elems[j] = this->elems[j+1];
            this->size--;
        }
    }
}

template <typename T>
void DynamicVector<T>::update(const int pos, const T elem) {
    this->elems[pos] = elem;
}

template <typename T>
T DynamicVector<T>::get_elem(const int pos) const {
    return this->elems[pos];
}




