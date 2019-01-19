//
// Created by Abed Kadry on 19-Jan-19.
//

#include "Complex.h"
using namespace MtmMath;


Complex::Complex(double r, double i) {
    re = r;
    im = i;
}

Complex::Operator=(const MtmMath::Complex &c) {
    re = c.re;
    im = c.im;
}

Complex Complex::operator-() const {
    return Complex(-re, -im);
}

Complex& Complex::operator+=(const MtmMath::Complex &c) {
    re += c.re;
    im += c.im;
    return *this;
}

Complex& Complex::operator-=(const MtmMath::Complex &c) {
    return this->operator+=(-c);
}

Complex& Complex::operator*=(const MtmMath::Complex &c) {
    re = re*(c.re) - im*(c.im);
    im = re*(c.im) + im*(c.re);
}

bool Complex::operator==(const Complex& c) const {
    return (re == c.re && im == c.im);
}

bool Complex::operator!=(const Complex& c) const {
    return !(this->operator==(c));
}

Complex operator+(const Complex& c1, const Complex& c2) {
    Complex c = c1;
    return c += b;
}

Complex operator-(const Complex& c1, const Complex& c2) {
    return (c1+(-c2));
}

Complex operator*(const Complex& c1, const Complex& c2) {
    Complex c = c1;
    return c.operator*=(c2);
}