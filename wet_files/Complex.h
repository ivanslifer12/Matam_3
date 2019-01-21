#ifndef EX3_COMPLEX_H
#define EX3_COMPLEX_H
namespace MtmMath {

    class Complex {
        double re,im;
    public:
        Complex(double r=0.0, double i=0.0);
        Complex& operator=(const Complex&) = default;

        Complex operator-() const;

        Complex& operator+=(const Complex& c);
        Complex& operator-=(const Complex& c);
        Complex& operator*=(const Complex& c);

        bool operator==(const Complex& c) const;
        bool operator!=(const Complex& c) const;

        double Re() const;
        double Im() const;

    };

    Complex operator+(const Complex& c1, const Complex& c2);
    Complex operator-(const Complex& c1, const Complex& c2);
    Complex operator*(const Complex& c1, const Complex& c2);


    Complex::Complex(double r, double i) {
        re = r;
        im = i;
    }

/*Complex& Complex::operator=(const MtmMath::Complex &c) {
    re = c.re;
    im = c.im;
    return *this;
}
*/
    Complex Complex::operator-() const {
        return Complex(-re, -im);
    }

    Complex& Complex::operator+=(const Complex &c) {
        re += c.re;
        im += c.im;
        return *this;
    }

    Complex& Complex::operator-=(const Complex &c) {
        return this->operator+=(-c);
    }

    Complex& Complex::operator*=(const Complex &c) {
        int original = re;
        re = re*(c.re) - im*(c.im);
        im = original*(c.im) + im*(c.re);
        return *this;
    }

    bool Complex::operator==(const Complex& c) const {
        return (re == c.re && im == c.im);
    }

    bool Complex::operator!=(const Complex& c) const {
        return !(this->operator==(c));
    }

    Complex operator+(const Complex& c1, const Complex& c2) {
        Complex c = c1;
        return c += c2;
    }

    Complex operator-(const Complex& c1, const Complex& c2) {
        Complex c = c1;
        return c -= c2;
    }

    Complex operator*(const Complex& c1, const Complex& c2) {
        Complex c = c1;
        return c.operator*=(c2);
    }

    double Complex::Re() const {
        return re;
    }

    double Complex::Im() const {
        return im;
    }

}

#endif //EX3_COMPLEX_H
