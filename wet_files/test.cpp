//
// Created by Abed Kadry on 19-Jan-19.
//
#include <iostream>

#include <iostream>

#include "Complex.h"
using namespace MtmMath;
using namespace std;

int main() {
    Complex wahad = Complex(2, 3);
    Complex thnen = Complex(4, 5);
    thnen = -thnen;
    Complex thlath = wahad + thnen;
    cout << "6+8i? " << thlath.Re() << "+i" << thlath.Im() << endl;
    cout << "-7+22i? " << (wahad * thnen).Re() << "+i" << (wahad * thnen).Im() << endl;
    return 0;
}