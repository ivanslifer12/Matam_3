#include <vector>
#include "MtmMat.h"
#include <iostream>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "MtmVec.h"
#include "MtmExceptions.h"
#include "Complex.h"

using std::size_t;

using namespace MtmMath;
//must rewrite this

template<typename T>
MtmMat<T>::MtmMat(Dimensions dim_t, const T &val) {
    try {
        if (dim_t.getCol() <= 0 || dim_t.getRow() <= 0) {
            throw MtmExceptions::IllegalInitialization();
        }

        matrix = new T *[dim_t.getRow()];


        for (int i = 0; i < dim_t.getRow(); i ++) {
            matrix[i] = new T[dim_t.getCol()];
        }
        for (int i = 0; i < dim_t.getRow(); i ++) {
            for (int j = 0; j < dim_t.getCol(); j ++) {
                matrix[i][j] = val;
            }
        }
        row_dim = dim_t.getRow();
        column_dim = dim_t.getCol();
    }
    catch (std::bad_alloc &e) {
        cerr << e.what(); throw;

    }




















