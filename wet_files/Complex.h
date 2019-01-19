#ifndef EX3_COMPLEX_H
#define EX3_COMPLEX_H
namespace MtmMath {

    class Complex {
        double re,im;
    public:
        Complex(double r=0, double i=0);
        Complex operator=(const Complex& c) ;

        Complex operator-() const;

        Complex& operator+=(const Complex& c);
        Complex& operator-=(const Complex& c);
        Complex& operator*=(const Complex& c);

        bool operator==(const Complex& c) const;
        bool operator!=(const Complex& c) const;

    };




    Complex operator+(const Complex& c1, const Complex& c2);
    Complex operator-(const Complex& c1, const Complex& c2);
    Complex operator*(const Complex& c1, const Complex& c2);


}

#endif //EX3_COMPLEX_H
