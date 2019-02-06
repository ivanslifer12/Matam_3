#ifndef EX3_MTMMAT_H
#define EX3_MTMMAT_H

#include <vector>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "MtmVec.h"
#include <type_traits>

#define V2D(rowsize, colsize, type, name) vector<vector<(type)>>name((rowsize),vector<(type)>(colsize));

using std::size_t;

namespace MtmMath {

    template<typename T>
    class MtmMat {

    protected:
        std::vector<std::vector<T>> matrix;
        Dimensions dim;

    public:
        class iterator;

        class nonzero_iterator;

        /*
         * Matrix constructor, dim_t is the dimension of the matrix and val is the initial inner_stdvector for the matrix elements
         * Algorithm : create the col by the number of cols -> fill each call with data -> glow all the cols to the
         * matrix
         */

        explicit MtmMat(Dimensions dim_t, const T &val = T()) {
            //todo check if dim is valid
            dim = dim_t;

            matrix = std::vector<std::vector<T>>();
            this->reshape(dim, val); //todo with ampersand or not
        };

        MtmMat() = default;

        MtmMat(const MtmMat<T> &vector) = default;

        virtual ~MtmMat() = default;

        virtual MtmMat<T> &operator=(const MtmMat<T> &vector) = default;

        class MtmMatAccessor {
            int row;
            const MtmMat<T> *mat;
        public:
            explicit MtmMatAccessor(const MtmMat<T> *mat, size_t row) : row(row), mat(&mat)  {}

            MtmMatAccessor(MtmMatAccessor &copy) = default;

            ~MtmMatAccessor() = default;

            T &operator[](const size_t column) {
                return mat->matrix[row][column];
            }

            const T &operator[](const size_t column) const {
                return mat->matrix[row][column];
            }
        };

        MtmMatAccessor& operator[](const size_t row) const {
            auto x = MtmMatAccessor(this, row);
            return x;
        }


        T at(size_t row, size_t column) {
            if (row >= matrix.size() || column >= matrix[row].size())
                throw MtmExceptions::AccessIllegalElement();
            return matrix[row][column];
        }

        /*
         * Function that get function object f and uses it's () operator on each element in the matrix columns.
         * It outputs a vector in the size of the matrix columns where each element is the final output
         * by the function object's * operator
         */
        template<typename Func>
        MtmVec<T> matFunc(Func &f) const {
            MtmVec<T> out = MtmVec<T>(this->dim.getRow());
            for (int i = 0; i < this->dim.getRow(); ++i) {
                for (int j = 0; j < this->dim.getCol(); ++j) {
                    f(this->at(i, j));
                }
                out[i] = *f;
            }
            return out;
        }

        virtual void print() {
            for (int i = 0; i < this->dim.getRow(); ++i) {
                for (int j = 0; j < this->dim.getCol(); ++j) {
                    cout << this->at(i, j) << " ";
                }
                cout << "\n";
            }
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
            this->dim = newDim;
            matrix.resize(newDim.getRow(), std::vector<T>());
            for (int i = 0; i < matrix.size(); i++) {
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

            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < matrix[i].size(); j++) {
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
            return iterator((size_t) this->matrix.size() - 1);
        }

        nonzero_iterator nzbegin() {
            return nonzero_iterator(*this);
        }

        nonzero_iterator nzend() {
            size_t len = 0;
            size_t totalsize = (size_t) this->value.size();
            for (size_t j = 0; j < totalsize; ++j) { //todo second for, for matrix
                if (this->value[j] != 0)
                    len++;
            }

            return nonzero_iterator();
        }

        class iterator {
        private:
            bool is_end;
            bool isFirst = true;
        protected:
            MtmMat<T> *inner_matrix;
            size_t index;
            bool is_valid;
        public:
            explicit iterator(MtmMat<T> &mtmVec);

            explicit iterator(size_t i);

            ~iterator() = default;

            virtual iterator &operator++() {
                if (!this->is_valid)
                    return *this;

                if (isFirst)
                    isFirst = false;
                else
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
                return this->inner_matrix[row][column];
            }

            bool operator==(const iterator &rhs) const;

            bool operator!=(const iterator &rhs) const;

        };

        class nonzero_iterator : public iterator {
        private:
            size_t real_index = 0;
            bool isFirst = true;
        public:
            explicit nonzero_iterator(MtmMat<T> &mtmVec);

            explicit nonzero_iterator(size_t i);

            ~nonzero_iterator() = default;

            // unary operator gives access to the index
            T &operator*() {
                auto row = real_index / this->inner_matrix->dim.getCol();
                auto column = real_index % this->inner_matrix->dim.getCol();
                return this->inner_matrix[row][column];
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

                if ((size_t) this->real_index >= (size_t) this->inner_matrix->GetTotalLength()) {
                    this->is_valid = false;
                    return *this;
                }

                if ((*(this->inner_matrix))[this->real_index] == T()) {
                    this->index--;
                    goto _next;
                }

                return *this;
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

//iterator
    template<typename T>
    MtmMat<T>::iterator::iterator(MtmMat<T> &mtmVec) :  is_end(false), inner_matrix(&mtmVec), index(0), is_valid(true) {

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
    MtmMat<T>::iterator::iterator(size_t i) : is_end(true), inner_matrix(), index(i), is_valid(false) {}

//nonzeroiterator
    template<typename T>
    MtmMat<T>::nonzero_iterator::nonzero_iterator(MtmMat<T> &mtmVec) : iterator(mtmVec) {}

    template<typename T>
    MtmMat<T>::nonzero_iterator::nonzero_iterator(size_t i) : iterator(i) {}
}

#endif //EX3_MTMMAT_H
