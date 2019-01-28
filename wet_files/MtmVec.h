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
        std::vector<T> value;
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

        Dimensions getDimension() const ;
        size_t getLength() const;
    };
    template <typename T>
    MtmVec<T> operator+(const MtmVec<T>& vec1, const MtmVec<T>& vec2);
    template <typename T>
    MtmVec<T> operator-(const MtmVec<T>& vec1, const MtmVec<T>& vec2);

    template <typename T>
    MtmVec<T> operator+(const MtmVec<T>& vec, const T& scalar);
    template <typename T>
    MtmVec<T> operator+(const T& scalar, const MtmVec<T>& vec);
    template <typename T>
    MtmVec<T> operator-(const MtmVec<T>& vec, const T& scalar);
    template <typename T>
    MtmVec<T> operator-(const T& scalar, const MtmVec<T>& vec);
    template <typename T>
    MtmVec<T> operator*(const MtmVec<T>& vec, const T& scalar);
    template <typename T>
    MtmVec<T> operator*(const T& scalar, const MtmVec<T>& vec);




    template <typename T>
    MtmVec<T>::MtmVec(size_t m, const T& val) : dime(m, 1), value(m, val) {}
    template <typename T>
    MtmVec<T>::MtmVec() : dime(0, 1), value() {}
    /*MtmVec::MtmVec(const MtmVec<T>& vector) {
        dime = vector.dime;
        value = vector.value;
    }*/

    template <typename T>
    T& MtmVec<T>::operator[](int index) {
        if (index < 0 || (size_t)index >= value.size()) {
            throw MtmExceptions::AccessIllegalElement();
        }
        return value[index];
    }

    template <typename T>
    const T& MtmVec<T>::operator[](int index) const {
        if (index < 0 || (size_t)index >= value.size()) {
            throw MtmExceptions::AccessIllegalElement();
        }
        return value[index];
    }

    template <typename T>
    MtmVec<T> MtmVec<T>::operator-() const {
        MtmVec<T> negative = MtmVec(*this);
        for (size_t i = 0; i < value.size; i++){
            negative[i] = -(*this)[i];
        }
        return negative;
    }





    template <typename T>
    template <typename Func>
    T MtmVec<T>::vecFunc(Func& f) const{
        size_t length = value.size();
        T ret_value;
        for (size_t i = 0; i < length; i++) {
            f((*this)[i]);
        }
        return *f;
    }


    //vector and vector

    template <typename T>
    MtmVec<T> operator+(const MtmVec<T>& vec1, const MtmVec<T>& vec2) {
        if (vec1.getDimension() != vec2.getDimension()){
            throw MtmExceptions::DimensionMismatch();
        }
        MtmVec<T> result = MtmVec<T>(vec1.value.size(), 0);
        for (int i =0; i < vec1.value.size(); i++){
            result[i] = vec1[i] + vec2[i];
        }
        return result;
    }

    template <typename T>
    MtmVec<T> operator-(const MtmVec<T>& vec1, const MtmVec<T>& vec2){
        if (vec1.getDimension() != vec2.getDimension()){
            throw MtmExceptions::DimensionMismatch();
        }
        MtmVec<T> result = MtmVec<T>(vec1.getLength(), 0);
        for (size_t i =0; i < vec1.getLength(); i++){
            result[i] = vec1[i] - vec2[i];
        }
        return result;
    }

    //vector and scalar
    template <typename T>
    MtmVec<T> operator+(const MtmVec<T>& vec, const T& scalar) {
        MtmVec<T> result = MtmVec<T>(vec.value.size(), 0);
        for (int i = 0; i < vec.value.size(); i++){
            vec[i] += scalar;
        }
        return result;
    }

    template <typename T>
    MtmVec<T> operator+(const T& scalar, const MtmVec<T>& vec) {
        return vec + scalar;
    }

    template <typename T>
    MtmVec<T> operator-(const MtmVec<T>& vec, const T& scalar) {
        return vec + (-scalar);
    }

    template <typename T>
    MtmVec<T> operator-(const T& scalar, const MtmVec<T>& vec) {
        return (-vec) + scalar;
    }

    template <typename T>
    MtmVec<T> operator*(const MtmVec<T>& vec, const T& scalar) {
        MtmVec<T> result = MtmVec<T>(vec);
        for (size_t i = 0; i < vec.getLength(); i++){
            result[i] *= scalar;
        }
        return result;
    }

    template <typename T>
    MtmVec<T> operator*(const T& scalar, const MtmVec<T>& vec) {
        return vec * scalar;
    }

    template <typename T>
    Dimensions MtmVec<T>::getDimension() const {
        return Dimensions(this->dime);
    }

    template <typename T>
    size_t MtmVec<T>::getLength() const {
        return this->value.size();
    }

    template <typename T>
    void MtmVec<T>::transpose() {
        dime.transpose();
    }


    /*MtmMat<T> operator*(const MtmVec<T>& vec1, const MtmVec<T>& vec2) {
        if (vec1.dime.getRow() == vec2.dime.getCol() &&
                            vec1.dime.getCol() == vec2.dime.getRow() ){
            MtmMat<T> result = 0;
            for (int i =0; i < vec1.value.size(); i++){
                result += vec1[i] * vec2[i];
            }
            return result;
        }
        throw MtmExceptions::DimensionMismatch;
    } */

    //vector and scalar


}

#endif //EX3_MTMVEC_H
