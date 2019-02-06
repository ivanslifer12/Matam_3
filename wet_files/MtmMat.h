#ifndef EX3_MTMMAT_H
#define EX3_MTMMAT_H

#include <vector>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "MtmVec.h"
#include <type_traits>

#define V2D(rowsize, colsize, type, name) vector<vector<(type)>>name((rowsize),vector<(type)>(colsize));

#include <bits/stdc++.h>

using namespace std;
using std::size_t;

namespace MtmMath {

    template<typename T>
    class MtmMat {

    protected:
        Dimensions dim;

    public:
        std::vector<std::vector<T>> matrix;

        class iterator;

        class nonzero_iterator;

        /*
         * Matrix constructor, dim_t is the dimension of the matrix and val is the initial inner_stdvector for the matrix elements
         * Algorithm : create the col by the number of cols -> fill each call with data -> glow all the cols to the
         * matrix
         */

        explicit MtmMat(Dimensions dim_t, const T &val = T()) {
            try {
                if (dim_t.getRow() == 0 || dim_t.getCol() == 0)
                    throw MtmExceptions::IllegalInitialization();

                dim = dim_t;

                matrix = std::vector<std::vector<T>>();
                this->dim = dim_t;
                matrix.resize(dim_t.getRow(), std::vector<T>());
                for (size_t i = 0; i < matrix.size(); i++) {
                    matrix[i].resize(dim_t.getCol(), val);
                }
            } catch (std::bad_alloc &) {
                throw MtmExceptions::OutOfMemory();
            }
        };

        MtmMat() = default;

        MtmMat(const MtmMat<T> &vector) = default;

        virtual ~MtmMat() = default;

        MtmMat<T> &operator=(const MtmMat<T> &vector) = default;

        class Proxy { //see: https://stackoverflow.com/a/48297585/1481186
            friend class MtmMat<T>;

            std::vector<T> &v;

            explicit Proxy(std::vector<T> &v) : v(v) {}

        public:
            T &operator[](const size_t c) const { return (v)[c]; }

            T &operator[](const size_t c) { return (v)[c]; }
        };

/*
        class MtmMatAccessor {
            const size_t row;
            MtmMat<T> *mat;

        public:
            MtmMatAccessor(MtmMat<T> *mat, const size_t row) : row(row), mat(mat) {}


            MtmMatAccessor(const MtmMatAccessor &acc) = default;

            ~MtmMatAccessor() = default;

            T &operator[](const size_t column) {
                if (column < 0 || ((column > 0) && (unsigned int) column >= this->mat->dim.getRow())) {
                    throw MtmExceptions::AccessIllegalElement();
                }
                //return (const_cast<T>(mat))[row][column];

                return mat->matrix[row][column];
            }

            T &operator[](const int column) {
                if (column < 0 || ((column > 0) && (unsigned int) column >= this->mat->dim.getRow())) {
                    throw MtmExceptions::AccessIllegalElement();
                }
                //return (const_cast<T>(mat))[row][column];

                return mat->matrix[row][column];
            }

            const T &operator[](const size_t column) const {
                return mat->matrix[row][column];
            }

        };*/

        virtual std::vector<T> &operator[](const size_t row) {
            if (row >= this->matrix.size())
                throw MtmExceptions::AccessIllegalElement();
            return this->matrix[row];
//            return Proxy(x);
        }


        virtual const std::vector<T> &operator[](const size_t row) const {
            if (row >= this->matrix.size())
                throw MtmExceptions::AccessIllegalElement();
            return this->matrix[row];
        }


        T &at(size_t row, size_t column) {
            if (row >= this->matrix.size() || column >= this->matrix[row].size())
                throw MtmExceptions::AccessIllegalElement();
            return this->matrix[row][column];
        }

        const T &at(const size_t row, const size_t column) const {
            if (row >= this->matrix.size() || column >= this->matrix[row].size())
                throw MtmExceptions::AccessIllegalElement();
            return this->matrix[row][column];
        }

        /*
         * Function that get function object f and uses it's () operator on each element in the matrix columns.
         * It outputs a vector in the size of the matrix columns where each element is the final output
         * by the function object's * operator
         */
        template<typename Func>
        MtmVec<T> matFunc(Func &f) {
            f = Func();
            MtmMat<T> transposed(*this);
            transposed.transpose();
            MtmVec<T> ret(dim.getCol());
            for (unsigned int i = 0; i < dim.getCol(); i++) {
                auto x = MtmVec<T>(transposed[i]);
                T col = x.vecFunc(f);
                ret[i] = col;
            }
            return ret;
        }

        /*
         * resizes matrix so linear elements inner_stdvector are the same without changing num of elements.
         */
        virtual void resize(Dimensions newDim, const T &val = T()) {
            reshape(newDim, val);
        }

        /*
         * reshapes matrix so linear elements inner_stdvector are the same without changing num of elements.
         */
        virtual void reshape(Dimensions newDim, const T &val = T()) {
            if (newDim.getCol() != newDim.getRow())
                throw MtmExceptions::ChangeMatFail(this->dim, newDim);
            this->dim = newDim;
            matrix.resize(newDim.getRow(), std::vector<T>());
            for (size_t i = 0; i < matrix.size(); i++) {
                matrix[i].resize(newDim.getCol(), val);
            }
        }

        /*
         * The number of items, if matrix is 2x3, then will return 6.
         */
        virtual size_t GetTotalLength() {
            return dim.getRow() * dim.getCol();
        }

        /*
         * Performs transpose operation on matrix
         */
        virtual void transpose() {
            if (matrix.size() == 0)
                return;

            vector<vector<T> > trans_vec(matrix[0].size(), vector<T>());

            for (size_t i = 0; i < matrix.size(); i++) {
                for (size_t j = 0; j < matrix[i].size(); j++) {
                    trans_vec[j].push_back(matrix[i][j]);
                }
            }

            matrix = trans_vec;    // <--- reassign here
        }

        virtual MtmMat<T> operator-();

        virtual MtmMat<T> operator+(const MtmMat<T> &right);

        virtual MtmMat<T> operator-(const MtmMat<T> &right);

        virtual MtmMat<T> operator*(const MtmMat<T> &right);

        virtual MtmMat<T> operator+(const MtmVec<T> &right);

        virtual MtmMat<T> operator-(const MtmVec<T> &right);

        virtual MtmMat<T> operator*(const MtmVec<T> &right);

        virtual MtmMat<T> operator+(const T &right);

        virtual MtmMat<T> operator-(const T &right);

        virtual MtmMat<T> operator*(const T &right);

        iterator begin() {
            return iterator(*this);
        }

        iterator end() {
            return iterator(this->GetTotalLength());
        }

        nonzero_iterator nzbegin() {
            return nonzero_iterator(*this);
        }

        nonzero_iterator nzend() {
            size_t len = 0;
            for (auto row = this->matrix.begin(); row != this->matrix.end(); ++row) {
                for (auto column = (*row).begin(); column != (*row).end(); ++column) {
                    if (*column != 0)
                        len++;
                }
            }

            return nonzero_iterator(len);
        }

        class iterator {
        private:
            bool is_end;
        protected:
            MtmMat<T> *inner_matrix = nullptr;
            size_t index;
            bool is_valid;
        public:
            explicit iterator(MtmMat<T> &mat);

            explicit iterator(size_t i);

            ~iterator() {
                if (inner_matrix != nullptr)
                    delete inner_matrix;
            };

            virtual iterator &operator++() {
                if (!this->is_valid)
                    return *this;


                this->index++;

                if ((size_t) this->index >= (size_t) this->inner_matrix->GetTotalLength())
                    this->is_valid = false;

                return *this;
            }

            bool isValid() {
                return this->is_valid;
            }

            // unary operator gives access to the index
            virtual T &operator*() {
                auto row = index / inner_matrix->dim.getCol();
                auto column = index % inner_matrix->dim.getCol();
                return this->inner_matrix->matrix[row][column];
            }

            bool operator==(const iterator &rhs) const;

            bool operator!=(const iterator &rhs) const;

        };

        class nonzero_iterator : public iterator {
        private:
            size_t real_index = 0;
        public:
            explicit nonzero_iterator(MtmMat<T> &mtmVec);

            explicit nonzero_iterator(size_t i);

            ~nonzero_iterator() = default;

            // unary operator gives access to the index
            T &operator*() {
                auto row = real_index / this->inner_matrix->dim.getCol();
                auto column = real_index % this->inner_matrix->dim.getCol();
                return this->inner_matrix->matrix[row][column];
            }

            nonzero_iterator &operator++() {
                if (!this->is_valid)
                    return *this;

                _next:

                this->index++;
                this->real_index++;

                if ((size_t) this->real_index >= (size_t) this->inner_matrix->GetTotalLength()) {
                    this->is_valid = false;
                    return *this;
                }

                if (*(*this) ==
                    T()) { //one * for getting this object, an other * for getting current value from overload.
                    this->index--;
                    goto _next;
                }

                return *this;
            }

            void skip_zeroes() {
                _next:

                this->index++;
                this->real_index++;

                if ((size_t) this->real_index >= (size_t) this->inner_matrix->GetTotalLength()) {
                    this->is_valid = false;
                    return;
                }

                if (*(*this) ==
                    T()) { //one * for getting this object, an other * for getting current value from overload.
                    this->index--;
                    goto _next;
                }
            }
        };
    };

    template<typename T>
    MtmMat<T> MtmMat<T>::operator-() {
        //https://stackoverflow.com/questions/641864/returning-a-pointer-to-a-vector-element-in-c
        auto ret = MtmMat<T>(*this);
        for (auto row = ret.matrix.begin(); row != ret.matrix.end(); ++row) {
            for (auto column = (*row).begin(); column != (*row).end(); ++column) {
                *column = -(*column);
            }
        }
        return ret;
    }

    template<typename T>
    MtmMat<T> MtmMat<T>::operator+(const MtmMat<T> &right) {
        //todo dim check
        auto ret = MtmMat<T>(*this);
        for (auto row = ret.matrix.begin(), row2 = right.matrix.begin(); row != ret.matrix.end(); ++row, ++row2) {
            for (auto column = (*row).begin(), column2 = (*row2).begin(); column != (*row).end(); ++column, ++column2) {
                *column = (*column) + (*column2);
            }
        }
        return ret;
    }

    template<typename T>
    MtmMat<T> MtmMat<T>::operator-(const MtmMat<T> &right) {
        //todo dim check
        auto ret = MtmMat<T>(*this);
        for (auto row = ret.matrix.begin(), row2 = right.matrix.begin(); row != ret.matrix.end(); ++row, ++row2) {
            for (auto column = (*row).begin(), column2 = (*row2).begin(); column != (*row).end(); ++column, ++column2) {
                *column = (*column) + (-(*column2));
            }
        }
        return ret;
    }

    template<typename T>
    MtmMat<T> MtmMat<T>::operator*(const MtmMat<T> &right) {
        //todo dim check
        auto ret = MtmMat<T>(*this);
        for (auto row = ret.matrix.begin(), row2 = right.matrix.begin(); row != ret.matrix.end(); ++row, ++row2) {
            for (auto column = (*row).begin(), column2 = (*row2).begin(); column != (*row).end(); ++column, ++column2) {
                *column = (*column) * (*column2);
            }
        }
        return ret;
    }

    template<typename T>
    MtmMat<T> MtmMat<T>::operator+(const T &right) {
        auto ret = MtmMat<T>(*this);
        for (auto row = ret.matrix.begin(); row != ret.matrix.end(); ++row) {
            for (auto column = (*row).begin(); column != (*row).end(); ++column) {
                *column = (*column) + right;
            }
        }
        return ret;
    }

    template<typename T>
    MtmMat<T> MtmMat<T>::operator-(const T &right) {
        auto ret = MtmMat<T>(*this);
        for (auto row = ret.matrix.begin(); row != ret.matrix.end(); ++row) {
            for (auto column = (*row).begin(); column != (*row).end(); ++column) {
                *column = (*column) - right;
            }
        }
        return ret;
    }

    template<typename T>
    MtmMat<T> MtmMat<T>::operator*(const T &right) {
        auto ret = MtmMat<T>(*this);
        for (auto row = ret.matrix.begin(); row != ret.matrix.end(); ++row) {
            for (auto column = (*row).begin(); column != (*row).end(); ++column) {
                *column = (*column) * right;
            }
        }
        return ret;
    }

    template<typename T>
    MtmMat<T> MtmMat<T>::operator+(const MtmVec<T> &right) {
        if (this->dim != right.getDimension()) {
            throw MtmExceptions::DimensionMismatch(this->dim, right.getDimension());
        }
        auto ret = MtmMat<T>(*this);
        for (size_t row = 0; row < ret.GetTotalLength(); ++row) {
            for (size_t column = 0; column < ret.dim.getCol(); ++column) {
                ret[row][column] += right[row]; //todo might
            }
        }
        return ret;
    }

    template<typename T>
    MtmMat<T> MtmMat<T>::operator-(const MtmVec<T> &right) {
        if (this->dim != right.getDimension()) {
            throw MtmExceptions::DimensionMismatch(this->dim, right.getDimension());
        }
        auto ret = MtmMat<T>(*this);
        for (size_t row = 0; row < ret.GetTotalLength(); ++row) {
            for (size_t column = 0; column < ret.dim.getCol(); ++column) {
                ret[row][column] -= right[row]; //todo might
            }
        }
        return ret;
    }

    template<typename T>
    MtmMat<T> MtmMat<T>::operator*(const MtmVec<T> &right) {
        if (this->dim != right.getDimension()) {
            throw MtmExceptions::DimensionMismatch(this->dim, right.getDimension());
        }
        auto ret = MtmMat<T>(*this);
        for (size_t row = 0; row < ret.GetTotalLength(); ++row) {
            for (size_t column = 0; column < ret.dim.getCol(); ++column) {
                ret[row][column] *= right[row]; //todo might
            }
        }
        return ret;
    }

    template<typename T>
    MtmMat<T> operator*(const T &scalar, const MtmMat<T> &vec) {
        return vec * scalar;
    }

    template<typename T>
    MtmMat<T> operator+(const T &scalar, const MtmMat<T> &vec) {
        return vec + scalar;
    }

    template<typename T>
    MtmMat<T> operator-(const T &scalar, const MtmMat<T> &vec) {
        return vec - scalar;
    }

    template<typename T>
    MtmMat<T> operator*(const MtmMat<T> &vec, const T &scalar) {
        auto ret = MtmMat<T>(vec);
        for (auto row = ret.matrix.begin(); row != ret.matrix.end(); ++row) {
            for (auto column = (*row).begin(); column != (*row).end(); ++column) {
                *column *= scalar;
            }
        }
        return ret;
    }

    template<typename T>
    MtmMat<T> operator+(const MtmMat<T> &vec, const T &scalar) {
        auto ret = MtmMat<T>(vec);
        for (auto row = ret.matrix.begin(); row != ret.matrix.end(); ++row) {
            for (auto column = (*row).begin(); column != (*row).end(); ++column) {
                *column += scalar;
            }
        }
        return ret;
    }

    template<typename T>
    MtmMat<T> operator-(const MtmMat<T> &vec, const T &scalar) {
        auto ret = MtmMat<T>(vec);
        for (auto row = ret.matrix.begin(); row != ret.matrix.end(); ++row) {
            for (auto column = (*row).begin(); column != (*row).end(); ++column) {
                *column -= scalar;
            }
        }
        return ret;
    }

//iterator
    template<typename T>
    MtmMat<T>::iterator::iterator(MtmMat<T> &mat) :  is_end(false), index(0), is_valid(true) {
        MtmMat<T> *x = new MtmMat<T>(mat);
        x->transpose();
        inner_matrix = x;
    }

    template<typename T>
    bool MtmMat<T>::iterator::operator==(const MtmMat::iterator &rhs) const {
        return index == rhs.index;
    }

    template<typename T>
    bool MtmMat<T>::iterator::operator!=(const MtmMat::iterator &rhs) const {
        return !(rhs == *this);
    }

    template<typename T>
    MtmMat<T>::iterator::iterator(size_t i) : is_end(true), inner_matrix(nullptr), index(i), is_valid(false) {}

//nonzeroiterator
    template<typename T>
    MtmMat<T>::nonzero_iterator::nonzero_iterator(MtmMat<T> &mtmVec) : iterator(mtmVec) {
        this->skip_zeroes();
    }

    template<typename T>
    MtmMat<T>::nonzero_iterator::nonzero_iterator(size_t i) : iterator(i) {}
}

#endif //EX3_MTMMAT_H
