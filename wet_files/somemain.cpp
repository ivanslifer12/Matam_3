#include <iostream>
#include "Auxilaries.h"
#include "MtmVec.h"
#include "MtmMat.h"
#include <algorithm>
#include <vector>
#include <functional>

int main() {
    MtmMat<int> m(Dimensions(2,3),0);
    m[0][1]=1;
    m[1][1]=1;
    m[0][0]=1;
    m[1][0]=1;
    m[0][2]=1;
    m[1][2]=1;
    std::cout << m[0][1];
    return 0;
}