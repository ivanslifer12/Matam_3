#ifndef EX3_AUXILARIES_H
#define EX3_AUXILARIES_H

#include <string>
#include <iostream>

using std::size_t;

namespace MtmMath {
    class Dimensions {
        size_t row, col;
    public:
        explicit Dimensions(size_t row_t, size_t col_t) : row(row_t), col(col_t) {}

        explicit Dimensions(int row_t, int col_t) : row((size_t) row_t), col((size_t) col_t) {}

        //copy constructor
        Dimensions(const Dimensions &dim) = default;

        Dimensions() = default;

        ~Dimensions() = default;

        bool operator==(const Dimensions &rhs) const {
            return row == rhs.row &&
                   col == rhs.col;
        }

        bool operator!=(const Dimensions &rhs) const {
            return !(rhs == *this);
        }

        std::string to_string() const {
            return "(" + std::to_string(row) + "," + std::to_string(col) + ")";
        }

        void transpose() {
            size_t prev_row = row;
            row = col;
            col = prev_row;
        }

        size_t getRow() const {
            return row;
        }

        size_t getCol() const {
            return col;
        }
    };

}

#endif //EX3_AUXILARIES_H
