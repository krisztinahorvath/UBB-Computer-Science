#include <assert.h>
#include "Matrix.h"
#include "MatrixIterator.h"
#include <exception>

using namespace std;

void testAll() { 
	Matrix m(4, 4);

	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);


    /// iterator tests
    Matrix m1 {10,10 };

    /// (0, 0, 0)
    /// (0, 1, 1)
    /// (0, 2, 2)

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            m1.modify(i, j, j);

    for (int i = 0; i < 10; i++)
    {
        MatrixIterator it = m1.iterator(i);

        assert(it.valid() == true);

        for (int next = 0; next < 9; next++) /// 0, 1, 2, 3 ... 9
        {
            assert(it.valid() == true);
            assert(it.getCurrent() == next);
            it.next();
        }
        assert(it.getCurrent() == 9); /// last elem in the matrix

        for (int prev = 0; prev < 9; prev++)  /// 9 8 7 6 ... the values of m1[i,j]
        {
            assert(it.valid() == true);
            assert(it.getCurrent() == 9-prev);
            it.previous();
        }
        assert(it.getCurrent() == 0); /// back to the first elem

        try{
            it.previous(); /// we are at the first elem, there is no previous elem
            assert(false);
        }
        catch(exception&)
        {
            assert(true);
        }
    }
}