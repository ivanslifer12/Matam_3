#ifndef EX3_MTMVEC_H
#define EX3_MTMVEC_H

#include <vector>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "Complex.h"

using namespace std;

namespace MtmMath {


    template <typename T>
    class MtmVec {
        Dimensions dime;
        std::vector<T> value;
        int  index;
        bool is_upper;

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

    public:

        class iterator {
        protected:
            MtmVec<T>* vec;
            int index;
            bool is_valid;


        public:

            explicit iterator(MtmVec<T>& mtmVec, bool isBeginning);

            ~iterator() = default;

            virtual iterator& operator++();


            T& operator*(); // unary operator gives access to the index

            bool operator==(const iterator& it) const;

            bool operator!=(const iterator& it) const; //for pointing reference

            bool isValid() {
                return this->is_valid;
            }

        };


        class nonzero_iterator : public iterator {
        public:
            explicit nonzero_iterator(MtmVec<T>& mtmVec, bool isBeginning);

            ~nonzero_iterator() = default;

            nonzero_iterator& operator++()
            {
                do {
                    ++(this->index);
                } while((unsigned int)this->index < this->vec->data.size() &&
                        this->vec->data[this->index] == 0);
                if((unsigned int)this->index >= this->vec->data.size()) {
                    this->is_valid = false;
                }
                return *this;
            }

        };







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






#endif //EX3_MTMVEC_H
