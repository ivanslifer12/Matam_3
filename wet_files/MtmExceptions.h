#ifndef EX3_MTMEXCEPTIONS_H
#define EX3_MTMEXCEPTIONS_H

#include <exception>
#include <string>
#include <iostream>
#include "Auxilaries.h"

namespace MtmMath {
    namespace MtmExceptions {
        class MtmExceptions : public std::exception {
        public:
            ~MtmExceptions() throw() override = default;
        };

        /*
         * Exception for illegal initialization of an object, needs to output
         * "MtmError: Illegal initialization values" in what() class function
         */
        class IllegalInitialization : public MtmExceptions {
        public:
            const char* what() const noexcept override {
                return "MtmError: Illegal initialization values";
            }
        };

        /*
         * Exception for Memory allocation failure for an object, needs to output
         * "MtmError: Out of memory" in what() class function
         */
        class OutOfMemory : public MtmExceptions {
        public:
            const char* what() const noexcept override {
                return "MtmError: Out of memory";
            }
        };

        /*
         * Exception for dimension mismatch during a mathematical function, needs to output
         * "MtmError: Dimension mismatch: (<mat 1 row>,<mat 1 col>) (<mat 2 row>,<mat 2 col>)"
         * in what() class function
         */
        class DimensionMismatch : public MtmExceptions {
            Dimensions mat1, mat2;
            std::string msg;
        public:
            DimensionMismatch(const Dimensions& dim1, const Dimensions& dim2) :
                    mat1(dim1), mat2(dim2),
                    msg(std::string("MtmError: Dimension mismatch: ") +
                        mat1.to_string() + std::string(" ") + mat2.to_string()) {}
            ~DimensionMismatch() override = default;
            const char* what() const noexcept override {
                return msg.c_str();
            }
        };

        /*
         * Exception for error for changing matrix/vector shape in reshape and resize, needs to output
         * "MtmError: Change matrix shape failed from: (<mat row>,<mat col>) (<new mat row>,<new mat col>)"
         * in what() class function
         */
        class ChangeMatFail : public MtmExceptions {
            Dimensions old_mat, new_mat;
            std::string msg;
        public:
            ChangeMatFail(const Dimensions& old_dim, const Dimensions& new_dim):
                    old_mat(old_dim), new_mat(new_dim),
                    msg(std::string("MtmError: Change matrix shape failed from ") +
                        old_mat.to_string() + std::string(" to ") +
                        new_mat.to_string()) { }

            ~ChangeMatFail() override = default;
            const char* what() const noexcept override {
                return msg.c_str();
            }
        };

        /*
         * Exception for accessing an illegal element in matrix or vector, needs to output
         * "MtmError: Attempt access to illegal element" in what() class function
         */
        class AccessIllegalElement : public MtmExceptions {
        public:
            const char* what() const noexcept {
                return "MtmError: Attempt access to illegal element";
            }
        };
    }
}


#endif //EX3_MTMEXCEPTIONS_H