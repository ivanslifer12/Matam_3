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


template<typename T>
MtmVec<T>::MtmVec(size_t m, const T &val) {

}

template<typename T>
MtmVec<T>::MtmVec() : dime(0, 1), value() {}

/*MtmVec::MtmVec(const MtmVec<T>& vector) {
    dime = vector.dime;
    value = vector.value;
}*/

template<typename T>
T &MtmVec<T>::operator[](int index) {
    if (index < 0 || (size_t) index >= value.size()) {
        throw MtmExceptions::AccessIllegalElement();
    }
    return value[index];
}

template<typename T>
const T &MtmVec<T>::operator[](int index) const {
    if (index < 0 || (size_t) index >= value.size()) {
        throw MtmExceptions::AccessIllegalElement();
    }
    return value[index];
}

template<typename T>
MtmVec<T> MtmVec<T>::operator-() const {
    MtmVec<T> negative = MtmVec(*this);
    for (size_t i = 0; i < value.size; i++) {
        negative[i] = -(*this)[i];
    }
    return negative;
}


template<typename T>
template<typename Func>
T MtmVec<T>::vecFunc(Func &f) const {
    size_t length = value.size();
    T ret_value;
    for (size_t i = 0; i < length; i++) {
        f((*this)[i]);
    }
    return *f;
}


//vector and vector

template<typename T>
MtmVec<T> operator+(const MtmVec<T> &vec1, const MtmVec<T> &vec2) {
    if (vec1.getDimension() != vec2.getDimension()) {
        throw MtmExceptions::DimensionMismatch();
    }
    MtmVec<T> result = MtmVec<T>(vec1.value.size(), 0);
    for (int i = 0; i < vec1.value.size(); i++) {
        result[i] = vec1[i] + vec2[i];
    }
    return result;
}

template<typename T>
MtmVec<T> operator-(const MtmVec<T> &vec1, const MtmVec<T> &vec2) {
    if (vec1.getDimension() != vec2.getDimension()) {
        throw MtmExceptions::DimensionMismatch();
    }
    MtmVec<T> result = MtmVec<T>(vec1.getLength(), 0);
    for (size_t i = 0; i < vec1.getLength(); i++) {
        result[i] = vec1[i] - vec2[i];
    }
    return result;
}

//vector and scalar
template<typename T>
MtmVec<T> operator+(const MtmVec<T> &vec, const T &scalar) {
    MtmVec<T> result = MtmVec<T>(vec.value.size(), 0);
    for (int i = 0; i < vec.value.size(); i++) {
        vec[i] += scalar;
    }
    return result;
}

template<typename T>
MtmVec<T> operator+(const T &scalar, const MtmVec<T> &vec) {
    return vec + scalar;
}

template<typename T>
MtmVec<T> operator-(const MtmVec<T> &vec, const T &scalar) {
    return vec + (-scalar);
}

template<typename T>
MtmVec<T> operator-(const T &scalar, const MtmVec<T> &vec) {
    return (-vec) + scalar;
}

template<typename T>
MtmVec<T> operator*(const MtmVec<T> &vec, const T &scalar) {
    MtmVec<T> result = MtmVec<T>(vec);
    for (size_t i = 0; i < vec.getLength(); i++) {
        result[i] *= scalar;
    }
    return result;
}

template<typename T>
MtmVec<T> operator*(const T &scalar, const MtmVec<T> &vec) {
    return vec * scalar;
}

template<typename T>
Dimensions MtmVec<T>::getDimension() const {
    return Dimensions(this->dime);
}

template<typename T>
size_t MtmVec<T>::getLength() const {
    return this->value.size();
}

template<typename T>
void MtmVec<T>::transpose() {
    dime.transpose();
}

template<typename T>
MtmMat<T> operator*(const MtmVec<T> &vec1, const MtmVec<T> &vec2) {
    return 0;
}


//vector and scalar

//abed done till here


// the following templemples algorithm must be rewritten
template<typename T>
MtmVec<T>::iterator::iterator(MtmVec<T> &mtmVec, bool isBeginning) :
        vec(&mtmVec), index(0), is_valid(true) {

}


template<typename T>
T &MtmVec<T>::iterator::operator*() {
     return (T) nullptr;
}

template<typename T>
bool MtmVec<T>::iterator::operator==(const MtmVec::iterator &it) const {
    return false;
}

template<typename T>
bool MtmVec<T>::iterator::operator!=(const MtmVec::iterator &it) const {
    return false;
}


template<typename T>
MtmVec<T>::nonzero_iterator::nonzero_iterator(MtmVec<T> &mtmVec, bool isBeginning):
        iterator(mtmVec, isBeginning) {

}

