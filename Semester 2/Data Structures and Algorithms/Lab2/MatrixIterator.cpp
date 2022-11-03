#include "MatrixIterator.h"
#include <exception>

MatrixIterator::MatrixIterator(const Matrix &c, int line) : c{c}, line{line}{
    if (line < 0 || line >= c.nrLines() || col < 0 || col >= c.nrColumns())
        throw std::exception();
}
/// Theta(1)

void MatrixIterator::first() {
    this->col = 0;
}
/// Theta(1)

void MatrixIterator::next() {
    this->col++;

    if (valid() == false)
        throw std::exception();

}
/// Theta(1)

void MatrixIterator::previous() {
    this->col--;

    if (valid() == false)
        throw std::exception();
}
/// Theta(1)

bool MatrixIterator::valid() const {
    if (this->line < 0 || this->line >= this->c.nrLines() || this->col < 0 || this->col >= this->c.nrColumns())
        return false;
    return true;
}
/// Theta(1)

TElem MatrixIterator::getCurrent() const {
    if (valid() == false)
        throw std::exception();
    return this->c.element(this->line, this->col);
}
/// Theta(1)