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
        bool isUpper;
    public:

        MtmMatTriag(const Dimensions &dim_t, const T &val, bool isUpper) : MtmMatSq<T>(dim_t, val), isUpper(isUpper) {}

        MtmMatTriag(const size_t &size, const T &val, bool isUpper) : MtmMatSq<T>(Dimensions(size, size), val),
                                                                      isUpper(isUpper) {}

        MtmMatTriag(const size_t &size, const T &val) : MtmMatSq<T>(Dimensions(size, size), val),
                                                                      isUpper(false) {}

        MtmMatTriag() = default;

        explicit MtmMatTriag(const MtmMat<T> &vector, bool isUpper) : MtmMatSq<T>(vector), isUpper(isUpper) {}

        explicit MtmMatTriag(const MtmMatTriag<T> &vector) = default;

        explicit MtmMatTriag(const MtmMat<T> &vector) : MtmMatSq<T>(vector), isUpper(false) {}

        virtual ~MtmMatTriag() = default;

    };


}

#endif //EX3_MTMMATTRIAG_H
