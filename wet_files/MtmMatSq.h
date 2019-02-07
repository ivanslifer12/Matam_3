#ifndef EX3_MTMMATREC_H
#define EX3_MTMMATREC_H

#include <vector>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "MtmMat.h"

using std::size_t;

namespace MtmMath {

    template<typename T>
    class MtmMatSq : public MtmMat<T> {
    public:
        MtmMatSq(const Dimensions &dim_t, const T &val) : MtmMat<T>(dim_t, val) {

            if (dim_t.getRow() != dim_t.getCol()) {
                throw MtmExceptions::IllegalInitialization();
            }
        }

        explicit MtmMatSq(const size_t size, const T &val) : MtmMat<T>(Dimensions(size, size), val) {


        }

        MtmMatSq() : MtmMat<T>() {}

        MtmMatSq(const MtmMatSq<T> &copy) : MtmMat<T>(copy){


        }

        //Normal copy CToR
        explicit  MtmMatSq(const MtmMat<T> &copy) : MtmMat<T>(copy) {
            if (this->dim.getRow() != this->dim.getCol()) {
                throw MtmExceptions::DimensionMismatch(this->dim.getRow(), this->dim.getCol());
            }

        }

        ~MtmMatSq() = default;


        virtual void resize(Dimensions dim_t, const T &val = T()) {
            if (dim_t.getCol() != dim_t.getRow()) {
                throw MtmExceptions::ChangeMatFail(this->dim, dim_t);
            }
            this->MtmMat<T>::resize(dim_t, val); // Inherit from MtmMat
        }

        void reshape(Dimensions dim_t) {
            throw MtmExceptions::ChangeMatFail(this->dim,dim_t); // According to FAQ must throw exception

        }


    };
}


#endif //EX3_MTMMATREC_H
