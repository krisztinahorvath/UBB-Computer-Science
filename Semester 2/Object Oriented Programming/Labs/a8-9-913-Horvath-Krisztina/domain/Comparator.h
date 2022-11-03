#pragma once
#include <vector>
#include "movie.h"

template <class TElem>
class Comparator {
public:
    virtual bool compare(TElem t1, TElem t2) = 0;
};

class CompareAscendingByYear: public Comparator <Movie>{
    bool compare(Movie t1, Movie t2) override;
};


class CompareDescendingByTitle: public Comparator <Movie>{
    bool compare(Movie t1, Movie t2) override;
};

void test_compare();

