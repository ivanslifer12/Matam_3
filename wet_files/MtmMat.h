#ifndef EX3_MTMMAT_H
#define EX3_MTMMAT_H

#include <vector>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "MtmVec.h"

#define V2D(rowsize, colsize, type, name) vector<vector<(type)>>name((rowsize),vector<(type)>(colsize));

using std::size_t;

namespace MtmMath {

    template<typename T>
    class MtmMat {

    protected:
        std::vector<vector<T>> matrix;
        Dimensions dime;


    public:

        /*
         * Matrix constructor, dim_t is the dimension of the matrix and val is the initial value for the matrix elements
         * Algorithm : create the col by the number of cols -> fill each call with data -> glow all the cols to the
         * matrix
         */

        MtmMat(Dimensions dim_t, const T &val = T()) { //TODO no compleate
            vector<T> temp = MtmVec<T>(dim_t.getRow(), 0);
            for (int i = 0; i < dim_t.getCol(); ++i) {


            }
        };


        /*
         * Function that get function object f and uses it's () operator on each element in the matrix columns.
         * It outputs a vector in the size of the matrix columns where each element is the final output
         * by the function object's * operator
         */
        MtmMat mtmCopy(const MtmMat &m);

        MtmMat operator=(const MtmMat &m);

        ~MtmMat();


        template<typename Func>
        MtmVec<T> matFunc(Func &f) const;


        /*
         * resizes a matrix to dimension dim, new elements gets the value val.
         */

        /*
         * reshapes matrix so linear elements value are the same without changing num of elements.
         */
        virtual void reshape(Dimensions newDim);

        /*
         * Performs transpose operation on matrix
         */
        virtual void transpose();

    };

    


}

#endif //EX3_MTMMAT_H
