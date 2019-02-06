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
        explicit MtmMatSq(const Dimensions &dim_t, const T &val) : MtmMat<T>(dim_t, val) {}

        explicit MtmMatSq(const size_t size, const T &val) : MtmMat<T>(Dimensions(size, size), val) {}

        MtmMatSq() = default;

        MtmMatSq(const MtmMatSq<T> &copy) = default;

        virtual ~MtmMatSq() = default;

        void lol() {
            MtmMat<int> g = MtmMat<int>(Dimensions(2, 2), 0);
            MtmMat<int> g2 = g;
        }


    };

}

#endif //EX3_MTMMATREC_H
