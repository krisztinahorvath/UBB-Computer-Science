#pragma once

#include "Matrix.h"

class MatrixIterator {
private:

    const Matrix& c;
    int line;
    int col = 0;


public:
    MatrixIterator(const Matrix& c, int line);

    void first();

    void next();

    void previous();

    bool valid() const;

    TElem getCurrent() const;

};

