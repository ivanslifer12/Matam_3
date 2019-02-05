#ifndef EX3_MTMVEC_H
#define EX3_MTMVEC_H

#include <vector>
#include <ostream>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "Complex.h"

#define MAX(a, b) (a>b ? a : b)

using namespace std;
using std::size_t;

using namespace MtmMath;

namespace MtmMath {

    template<typename T>
    class MtmVec {
        Dimensions dime;
        std::vector<T> value;
        //needed? bool is_upper;

    public:
        class nonzero_iterator;

        class iterator;

        /*
         * Vector constructor, m is the number of elements in it and val is the initial value for the matrix elements
        */
        explicit MtmVec(size_t m, const T &val = T());

        MtmVec();

        MtmVec(const MtmVec<T> &vector) = default;

        MtmVec<T> &operator=(const MtmVec<T> &vector) = default;

        T &operator[](int index);

        const T &operator[](int index) const;

        MtmVec<T> operator-() const;

        MtmVec<T> operator*(const MtmVec<T> &right);

        /*
         * Function that get function object f and uses it's () operator on each element in the vectors.
         * It outputs the function object's * operator after iterating on all the vector's elements
         */
        template<typename Func>
        T vecFunc(Func &f) const;

        /*
         * Resizes a vector to dimension dim, new elements gets the value val.
         * Notice vector cannot transpose through this method.
         */
        void resize(Dimensions dim, const T &val = T());

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
            return iterator(this->value.size());
        }

        nonzero_iterator nzbegin() {
            return nonzero_iterator(*this);
        }

        int distance(iterator first, iterator last);

        nonzero_iterator nzend() {
            size_t len = 0;
            for (size_t j = 0; j < (size_t) this->value.size(); ++j) {
                if (this->value[len] != 0)
                    len++;
            }

            return nonzero_iterator(len);
        }



        ~MtmVec() = default;

        class iterator {
        private:
            size_t maxSize;
            bool is_end;
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

                this->index++;
                if ((size_t) this->index >= (size_t) this->vec->getLength())
                    this->is_valid = false;

                return *this;
            }

            bool isValid() {
                return this->is_valid;
            }

            T &operator*(); // unary operator gives access to the index

            bool operator==(const iterator &rhs) const;

            bool operator!=(const iterator &rhs) const;

        };


        class nonzero_iterator : public iterator {
        public:
            explicit nonzero_iterator(MtmVec<T> &mtmVec);

            explicit nonzero_iterator(size_t i);

            ~nonzero_iterator() = default;

            nonzero_iterator &operator++() {
                if (!this->is_valid)
                    return *this;

                _next:
                this->index++;

                if ((size_t) this->index >= (size_t) this->vec->getLength()) {
                    this->is_valid = false;
                    return *this;
                }

                if ((*(this->vec))[this->index] == T()) {
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
    MtmVec<T> operator*(const MtmVec<T> &vec, T &scalar);

    template<typename T>
    MtmVec<T> operator*(const T &scalar, const MtmVec<T> &vec);


    template<typename T>
    MtmVec<T>::MtmVec(size_t m, const T &val) : dime(m, 1) {
        this->value = std::vector<T>(m);
        for (auto i = this->value.begin(); i < this->value.end(); i++)
            this->value[i] = val;
    }

    template<typename T>
    MtmVec<T>::MtmVec() : dime(0, 1), value() {}

/*MtmVec::MtmVec(const MtmVec<T>& vector) {
    dime = vector.dime;
    value = vector.value;
}*/

    template<typename T>
    T &MtmVec<T>::operator[](int index) {
        if (index < 0 || (size_t) index >= (size_t) this->value.size()) {
            throw MtmExceptions::AccessIllegalElement();
        }

        return this->value[index];
    }

    template<typename T>
    const T &MtmVec<T>::operator[](int index) const {
        if (index < 0 || (size_t) index >= this->value.size()) {
            throw MtmExceptions::AccessIllegalElement();
        }

        return this->value[index];
    }

    template<class T>
    template<class Func>
    T MtmVec<T>::vecFunc(Func &f) const {
        for (int i = 0; i < this->getLength(); i++)
            f((*this)[i]);

        return *f;
    }

    template<typename T>
    MtmVec<T> operator+(const MtmVec<T> &vec1, const MtmVec<T> &vec2) {
        if (vec1.getDimension() != vec2.getDimension())
            throw MtmExceptions::DimensionMismatch();

        MtmVec<T> result = MtmVec<T>(vec1.value.size(), T());
        for (int i = 0; i < vec1.value.size(); i++)
            result[i] = vec1[i] + vec2[i];

        return result;
    }

    template<typename T>
    MtmVec<T> operator-(const MtmVec<T> &vec1, const MtmVec<T> &vec2) {
        if (vec1.getDimension() != vec2.getDimension())
            throw MtmExceptions::DimensionMismatch();

        MtmVec<T> result = MtmVec<T>(vec1.getLength(), T());
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
        MtmVec<T> result = MtmVec<T>(vec.value.size(), T());
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
    MtmVec<T> operator*(const MtmVec<T> &vec, T &scalar) {
        MtmVec<T> result = MtmVec<T>(vec);
        for (size_t i = 0; i < vec.getLength(); i++)
            result[i] *= scalar;

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
    void MtmVec<T>::resize(Dimensions dim, const T &val) {
        auto old = this->dime;
        auto _new = this->dime = Dimensions(dim);

        if (MAX(old.getRow(), old.getCol()) == MAX(_new.getRow(), _new.getCol()))
            return;

        this->value.resize(MAX(_new.getRow(), _new.getCol()), val);
    }

    template<typename T>
    MtmVec<T> MtmVec<T>::operator*(const MtmVec<T> &right) {
        if (this->getDimension() != right.getDimension())
            throw MtmExceptions::DimensionMismatch();

        MtmVec<T> result = MtmVec<T>(this->getLength(), T());
        for (size_t i = 0; i < this->getLength(); i++)
            result[i] = (*this)[i] * right[i];

        return result;
    }

    template<typename T>
    int MtmVec<T>::distance(MtmVec::iterator first, MtmVec::iterator last) {
        int size = 0;
        for (auto i = first.begin(); i < last.end(); i++) {
            size++;
        }
        return size;
    }

//iterator
    template<typename T>
    MtmVec<T>::iterator::iterator(MtmVec<T> &mtmVec) : vec(&mtmVec), index(0), is_valid(true), is_end(false) {}

    template<typename T>
    T &MtmVec<T>::iterator::operator*() {
        return this->vec[this->index];
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
    MtmVec<T>::iterator::iterator(size_t i) : is_end(true), maxSize(i), is_valid(false) {}

//nonzeroiterator
    template<typename T>
    MtmVec<T>::nonzero_iterator::nonzero_iterator(MtmVec<T> &mtmVec) : iterator(mtmVec) {}

    template<typename T>
    MtmVec<T>::nonzero_iterator::nonzero_iterator(size_t i) : iterator(i) {}
}

#endif //EX3_MTMVEC_H
