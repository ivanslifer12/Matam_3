#ifndef EX3_MTMVEC_H
#define EX3_MTMVEC_H

#include <vector>
#include <ostream>
#include <iostream>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "Complex.h"

#define MAX(a, b) (a>b ? a : b)
#define MIN(a, b) (a>b ? b : a)

using namespace std;
using std::size_t;

using namespace MtmMath;

namespace MtmMath {

    template<typename T>
    class MtmVec {
        Dimensions dime;
        std::vector<T> inner_stdvector;
        //needed? bool is_upper;
    protected:
        bool transposed = false;
    public:
        class nonzero_iterator;

        class iterator;

        /*
         * Vector constructor, m is the number of elements in it and val is the initial inner_stdvector for the matrix elements
        */
        explicit MtmVec(size_t m, const T &val = T());

        MtmVec();

        MtmVec(const MtmVec<T> &vector) = default;

        explicit MtmVec(std::vector<T> vec) : inner_stdvector(vec), dime(Dimensions((size_t)vec.size(), (size_t)1)) {}

        MtmVec<T> &operator=(const MtmVec<T> &vector) = default;

        T &operator[](int index);

        const T &operator[](int index) const;

        MtmVec<T> operator-() const;

        MtmVec<T> operator+(const MtmVec<T> &right);

        MtmVec<T> operator-(const MtmVec<T> &right);

        MtmVec<T> operator*(const MtmVec<T> &right);

        MtmVec<T> operator+(const T &right);

        MtmVec<T> operator-(const T &right);

        MtmVec<T> operator*(const T &right);

        /*
         * Function that get function object f and uses it's () operator on each element in the vectors.
         * It outputs the function object's * operator after iterating on all the vector's elements
         */
        template<typename Func>
        T vecFunc(Func &f) const;

        /*
         * Resizes a vector to dimension dim, new elements gets the inner_stdvector val.
         * Notice vector cannot transpose through this method.
         */
        void resize(Dimensions newDim, const T &val = T());

        /*
         * Performs transpose operation on matrix
         */
        void transpose();

        Dimensions getDimension() const;

        size_t getLength() const;

        iterator begin() {
            return iterator(*this);
        }

        iterator end() {
            return iterator((size_t) this->inner_stdvector.size() - 1);
        }

        nonzero_iterator nzbegin() {
            return nonzero_iterator(*this);
        }

        /*
         * Get the size of this vector.
         */
        size_t GetTotalLength();

        const size_t GetTotalLength() const;

        nonzero_iterator nzend() {
            size_t len = 0;
            size_t totalsize = (size_t) this->inner_stdvector.size();
            for (size_t j = 0; j < totalsize; ++j) {
                if (this->inner_stdvector[j] != 0)
                    len++;
            }

            return nonzero_iterator(len - 1);
        }

        ~MtmVec() = default;

        class iterator {
        private:
            bool is_end;
            bool isFirst = true;
        protected:
            MtmVec<T> *vec;
            size_t index;
            bool is_valid;
        public:
            explicit iterator(MtmVec<T> &mtmVec);

            explicit iterator(size_t i);

            ~iterator() = default;

            virtual iterator &operator++() {
                if (!this->is_valid)
                    return *this;

                if (isFirst)
                    isFirst = false;
                else
                    this->index++;
                if ((size_t) this->index >= (size_t) this->vec->getLength())
                    this->is_valid = false;

                return *this;
            }

            bool isValid() {
                return this->is_valid;
            }

            // unary operator gives access to the index
            virtual T &operator*() {
                return this->vec->inner_stdvector[this->index];
            }

            bool operator==(const iterator &rhs) const;

            bool operator!=(const iterator &rhs) const;

        };

        class nonzero_iterator : public iterator {
        private:
            size_t real_index = 0;
            bool isFirst = true;
        public:
            explicit nonzero_iterator(MtmVec<T> &mtmVec);

            explicit nonzero_iterator(size_t i);

            ~nonzero_iterator() = default;

            // unary operator gives access to the index
            T &operator*() {
                return this->vec->inner_stdvector[this->real_index];
            }

            nonzero_iterator &operator++() {
                if (!this->is_valid)
                    return *this;

                _next:
                if (isFirst)
                    isFirst = false;
                else {
                    this->index++;
                    this->real_index++;
                }

                if ((size_t) this->real_index >= (size_t) this->vec->getLength()) {
                    this->is_valid = false;
                    return *this;
                }

                if ((*(this->vec))[this->real_index] == T()) {
                    this->index--;
                    goto _next;
                }

                return *this;
            }
        };
    };

    template<typename T>
    MtmVec<T> operator+(const MtmVec<T> &vec1, const MtmVec<T> &vec2);

    template<typename T>
    MtmVec<T> operator-(const MtmVec<T> &vec1, const MtmVec<T> &vec2);

    template<typename T>
    MtmVec<T> operator+(const MtmVec<T> &vec, const T &scalar);

    template<typename T>
    MtmVec<T> operator+(const T &scalar, const MtmVec<T> &vec);

    template<typename T>
    MtmVec<T> operator-(const MtmVec<T> &vec, const T &scalar);

    template<typename T>
    MtmVec<T> operator-(const T &scalar, const MtmVec<T> &vec);

    template<typename T>
    MtmVec<T> operator*(const MtmVec<T> &vec, const T &scalar);

    template<typename T>
    MtmVec<T> operator*(const T &scalar, const MtmVec<T> &vec);

    //template<typename T>
    //MtmVec<T> operator*(const T &scalar, const MtmVec<T> &inner_matrix);


    template<typename T>
    MtmVec<T>::MtmVec(size_t m, const T &val) : dime(m, (size_t) 1) {
        try {
            if (m <= 0)
                throw MtmExceptions::IllegalInitialization();
            auto vec = std::vector<T>(m);
            for (size_t i = 0; i < (size_t) vec.size(); i++)
                vec[i] = val;
            this->inner_stdvector = vec;
        } catch (std::bad_alloc &) {
            throw MtmExceptions::OutOfMemory();
        }
    }

    template<typename T>
    MtmVec<T>::MtmVec() : dime(0, 1), inner_stdvector() {}

/*MtmVec::MtmVec(const MtmVec<T>& vector) {
    dim = vector.dim;
    inner_stdvector = vector.inner_stdvector;
}*/

    template<typename T>
    T &MtmVec<T>::operator[](int index) {
        if (index < 0 || (size_t) index >= (size_t) this->inner_stdvector.size()) {
            throw MtmExceptions::AccessIllegalElement();
        }

        return this->inner_stdvector[index];
    }

    template<typename T>
    const T &MtmVec<T>::operator[](int index) const {
        if (index < 0 || (size_t) index >= this->inner_stdvector.size()) {
            throw MtmExceptions::AccessIllegalElement();
        }

        return this->inner_stdvector[index];
    }

    template<class T>
    template<class Func>
    T MtmVec<T>::vecFunc(Func &f) const {
        f = Func();
        for (int i = 0; i < this->getLength(); i++)
            f((*this)[i]);

        return *f;
    }

    template<typename T>
    MtmVec<T> operator+(const MtmVec<T> &vec1, const MtmVec<T> &vec2) {
        if (vec1.getDimension() != vec2.getDimension() || vec2.transposed != vec1.transposed)
            throw MtmExceptions::DimensionMismatch();
        MtmVec<T> result = MtmVec<T>(vec1);
        for (size_t i = 0; i < vec1.getLength(); i++)
            result[i] = vec1[i] + vec2[i];

        return result;
    }

    template<typename T>
    MtmVec<T> operator-(const MtmVec<T> &vec1, const MtmVec<T> &vec2) {
        if (vec1.getDimension() != vec2.getDimension() || vec2.transposed != vec1.transposed)
            throw MtmExceptions::DimensionMismatch();

        MtmVec<T> result = MtmVec<T>(vec1);
        for (size_t i = 0; i < vec1.getLength(); i++)
            result[i] = vec1[i] - vec2[i];

        return result;
    }

//vector operators

    template<typename T>
    MtmVec<T> MtmVec<T>::operator-() const {
        MtmVec<T> ret = MtmVec(*this);
        for (size_t i = 0; i < ret.getLength(); i++)
            ret[i] = -(ret[i]);

        return ret;
    }

    template<typename T>
    MtmVec<T> operator+(const MtmVec<T> &vec, const T &scalar) {
        MtmVec<T> result = MtmVec<T>(vec);
        for (size_t i = 0; i < vec.getLength(); i++) {
            result[i] = vec[i] + scalar;
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
    MtmVec<T> MtmVec<T>::operator-(const MtmVec<T> &right) {
        return (*this) + (-right);
    }

    template<typename T>
    MtmVec<T> operator*(const MtmVec<T> &vec, T &scalar) {
        MtmVec<T> result = MtmVec<T>(vec);
        for (size_t i = 0; i < vec.getLength(); i++)
            result[i] = result[i] * scalar;

        return result;
    }

    template<typename T>
    MtmVec<T> MtmVec<T>::operator*(const T &right) {
        MtmVec<T> vec = MtmVec<T>(*this);
        for (size_t i = 0; i < vec.getLength(); i++)
            vec[i] = vec[i] * right;

        return vec;
    }

    template<typename T>
    MtmVec<T> MtmVec<T>::operator-(const T &right) {
        MtmVec<T> vec = MtmVec<T>(*this);
        for (size_t i = 0; i < vec.getLength(); i++)
            vec[i] = vec[i] - right;

        return vec;
    }

    template<typename T>
    MtmVec<T> MtmVec<T>::operator+(const MtmVec<T> &right) {
        if (this->getDimension() != right.getDimension() || this->transposed != right.transposed)
            throw MtmExceptions::DimensionMismatch();

        MtmVec<T> result = MtmVec<T>(*this);
        for (size_t i = 0; i < this->getLength(); i++)
            result[i] = result[i] + right[i];

        return result;
    }

    template<typename T>
    MtmVec<T> MtmVec<T>::operator+(const T &right) {
        MtmVec<T> vec = MtmVec<T>(*this);
        for (size_t i = 0; i < vec.getLength(); i++)
            vec[i] = vec[i] + right;

        return vec;
    }

    template<typename T>
    MtmVec<T> operator*(const T &scalar, const MtmVec<T> &vec) {
        MtmVec<T> v = MtmVec<T>(vec);
        for (size_t i = 0; i < v.getLength(); i++)
            v[i] = v[i] * scalar;

        return v;
    }

    template<typename T>
    Dimensions MtmVec<T>::getDimension() const {
        return Dimensions(this->dime);
    }

    template<typename T>
    size_t MtmVec<T>::getLength() const {
        return this->inner_stdvector.size();
    }

    template<typename T>
    void MtmVec<T>::transpose() {
        dime.transpose();
        transposed = !transposed;
    }


    template<typename T>
    void MtmVec<T>::resize(Dimensions newDim, const T &val) {
        if ((transposed ? newDim.getRow() : newDim.getCol()) != 1)
            throw MtmMath::MtmExceptions::ChangeMatFail();

        auto old = this->dime;
        auto _new = this->dime = Dimensions(newDim);

        if (MAX(old.getRow(), old.getCol()) == MAX(_new.getRow(), _new.getCol()))
            return;

        this->inner_stdvector.resize(MAX(_new.getRow(), _new.getCol()), val);
    }

    template<typename T>
    MtmVec<T> MtmVec<T>::operator*(const MtmVec<T> &right) {
        if (this->getDimension() != right.getDimension())
            throw MtmExceptions::DimensionMismatch();

        MtmVec<T> result = MtmVec<T>(*this);
        for (size_t i = 0; i < this->getLength(); i++)
            result[i] = result[i] * right[i];

        return result;
    }

    template<typename T>
    size_t MtmVec<T>::GetTotalLength() {
        return this->inner_stdvector.size();
    }

    template<typename T>
    const size_t MtmVec<T>::GetTotalLength() const {
        return this->inner_stdvector.size();
    }

//iterator
    template<typename T>
    MtmVec<T>::iterator::iterator(MtmVec<T> &mtmVec) :  is_end(false),
                                                        vec(&mtmVec), index(0), is_valid(true) {

    }

    template<typename T>
    bool MtmVec<T>::iterator::operator==(const MtmVec::iterator &rhs) const {
        return index == rhs.index;
    }

    template<typename T>
    bool MtmVec<T>::iterator::operator!=(const MtmVec::iterator &rhs) const {
        return !(rhs == *this);
    }

    template<typename T>
    MtmVec<T>::iterator::iterator(size_t i) : is_end(true), vec(), index(i), is_valid(false) {}

//nonzeroiterator
    template<typename T>
    MtmVec<T>::nonzero_iterator::nonzero_iterator(MtmVec<T> &mtmVec) : iterator(mtmVec) {}

    template<typename T>
    MtmVec<T>::nonzero_iterator::nonzero_iterator(size_t i) : iterator(i) {}
}

#endif //EX3_MTMVEC_H
