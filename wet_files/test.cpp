//
// Created by Abed Kadry on 19-Jan-19.
//

#include <iostream>

#include "Complex.h"
using namespace MtmMath;

int main() {
    Complex wahad = Complex(2, 3);
    Complex thnen = Complex(4, 5);
    Complex thlath = wahad + thnen;
    cout << "6+8i? " << thlath << endl;
    cout << "-7-2i? " << wahd * thnen << endl;
}