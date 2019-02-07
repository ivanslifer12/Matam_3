#ifndef EX3_MTMMATTRIAG_H
#define EX3_MTMMATTRIAG_H


#include <vector>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "MtmMatSq.h"

using std::size_t;

namespace MtmMath {


    template<typename T>
    class MtmMatTriag : public MtmMatSq<T> {
        bool isUpper = true;
    public:

        void isItTriag() {
            size_t upTest = 0, downTest = 0;
            for (size_t row = 0; row < this->dim.getRow(); ++row) {
                for (size_t col = 0; row > col; ++col) {
                    if (this->matrix[row][col] != 0) {
                        upTest = 1;
                        break;
                    }
                }

            }
            for (size_t row = 0; row < this->dim.getRow(); ++row) {
                for (size_t col = row+1; col<this->dim.getCol(); ++col) {
                    if (this->matrix[row][col] != 0) {
                        downTest = 1;
                        break;
                    }
                }
            }
            if(upTest||downTest){
                throw MtmExceptions::IllegalInitialization();
            }
        }


        MtmMatTriag(size_t m, const T &val = T(), bool isUpper_t = true) : MtmMatSq<T>(m, val) {
            for (size_t row = 0; row < this->dim.getRow(); ++row) {
                if (this->isUpper) {
                    for (size_t col = 0; col < row; ++col) {
                        this->operator[](col).operator[](row) = 0;

                    }
                } else {
                    for (size_t col = row + 1; col < this->dim.getCol(); ++col) {
                        this->operator[](col).operator[](row) = 0;
                    }
                }
            }

        }

        explicit MtmMatTriag(MtmMatTriag<T>
                             &matrix) = default;

        explicit MtmMatTriag(MtmMatSq<T>
                             &matrix) :
                MtmMatSq<T>(matrix) {
            this->isItTriag();
        }

        explicit MtmMatTriag(MtmMat<T>
                             &matrix) :
                MtmMatSq<T>(matrix) {
            this->isItTriag();
        }

        ~

        MtmMatTriag() = default;

        void transpose() {
            MtmMatTriag<T> tempMatrix = MtmMatTriag(this);
            for (size_t row = 0; row < this->dim.getRow(); ++row) {
                for (size_t col = 0; col < this->dim.getCol(); ++col) {

                    this->operator[](row).operator[](col) = tempMatrix[col][row];
                }

            }
            this->isUpper = !this->isUpper;
        }

        void resize(Dimensions dim, const T &val = T()) {
            Dimensions oldDim(this->dim);
            this->MtmMatSq<T>::resize(dim, val);
            if (dim.getRow() > oldDim.getRow()) {

                if (this->isUpper) {
                    for (size_t row = oldDim.getRow(); row < dim.getRow(); row++) {
                        for (size_t col = 0; col < row; col++) {
                            this->operator[](row).operator[](col) = T(0);
                        }

                    }
                } else {
                    for (size_t col = oldDim.getCol(); col < dim.getCol(); col++) {
                        for (size_t row = 0; col < row; row++) {
                            this->operator[](row).operator[](col) = T(0);

                        }
                    }
                }
            }
        }


    };
}


#endif //EX3_MTMMATTRIAG_H
