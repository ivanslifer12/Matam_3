#ifndef EX3_MTMVEC_H
#define EX3_MTMVEC_H

#include <vector>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "Complex.h"

using std::size_t;

namespace MtmMath {
    template <typename T>
    class MtmVec {
        Dimensions dime;
        vector<T> value;
    public:
        /*
         * Vector constructor, m is the number of elements in it and val is the initial value for the matrix elements
         */
        MtmVec(size_t m, const T& val=T());
        MtmVec();
        MtmVec(const MtmVec<T>& vector) = default;
        MtmVec<T>& operator=(const MtmVec<T>& vector) = default;

        T& operator[](int index);
        const T& operator[](int index) const;

        MtmVec<T> operator-() const;
        ~MtmVec() = default;




        /*
         * Function that get function object f and uses it's () operator on each element in the vectors.
         * It outputs the function object's * operator after iterating on all the vector's elements
         */
        template <typename Func>
        T vecFunc(Func& f) const;

        /*
         * Resizes a vector to dimension dim, new elements gets the value val.
         * Notice vector cannot transpose through this method.
         */
        void resize(Dimensions dim, const T& val=T());

        /*
         * Performs transpose operation on matrix
         */
        void transpose();
    };

    MtmVec<T> operator+(const MtmVec<T>& vec1, const MtmVec<T>& vec2);
    MtmVec<T> operator-(const MtmVec<T>& vec1, const MtmVec<T>& vec2);
    MtmVec<T> operator*(const MtmVec<T>& vec1, const MtmVec<T>& vec2);




    MtmVec::MtmVec(size_t m, const T& val=T()) : dime(m, 1), value(m, val) {}
    MtmVec::MtmVec() : dime(0, 1), value() {}
    /*MtmVec::MtmVec(const MtmVec<T>& vector) {
        dime = vector.dime;
        value = vector.value;
    }*/


    T& operator[](int index) {
        if (index < 0 || index >= value.size()) {
            throw MtmExceptions::AccessIllegalElement;
        }
        return value[x];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= value.size()) {
            throw MtmExceptions::AccessIllegalElement;
        }
        return value[x];
    }

    MtmVec<T> MtmVec::operator-() const {
        MtmVec<T> negative = MtmVec(*this);
        for (size_t i = 0; i < value.size; i++){
            negative[i] = -(*this)[i];
        }
        return negative;
    }





    T MtmVec::vecFunc(Func& f) const{
        size_t length = value.size();
        T ret_value;
        for (size_t i = 0; i < length; i++) {
            f((*this)[i]);
        }
        return *f;
    }




    MtmVec<T> operator+(const MtmVec<T>& vec1, const MtmVec<T>& vec2) {
        if (vec1.dime != vec2.dime){
            throw MtmExceptions::DimensionMismatch;
        }
        MtmVec<T> result = MtmVec(vec1.value.size(), 0);
        for (int i =0; i < vec1.value.size(); i++){
            result[i] = vec1[i] + vec2[i];
        }
        return result;
    }

    MtmVec<T> operator-(const MtmVec<T>& vec1, const MtmVec<T>& vec2){
        if (vec1.dime != vec2.dime){
            throw MtmExceptions::DimensionMismatch;
        }
        MtmVec<T> result = MtmVec(vec1.value.size(), 0);
        for (int i =0; i < vec1.value.size(); i++){
            result[i] = vec1[i] - vec2[i];
        }
        return result;
    }

    //for vector multi
    MtmVec<T> operator*(const MtmVec<T>& vec1, const MtmVec<T>& vec2) {
        if (vec1.dime.getRow() == vec2.dime.getCol() &&
                            vec1.dime.getCol() == vec2.dime.getRow() ){
            T result = 0;
            for (int i =0; i < vec1.value.size(); i++){
                result += vec1[i] * vec2[i];
            }
            return result;
        }
        throw MtmExceptions::DimensionMismatch;
    }

}

#endif //EX3_MTMVEC_H
