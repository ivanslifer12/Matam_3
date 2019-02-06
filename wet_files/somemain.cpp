#include <iostream>
#include "Auxilaries.h"
#include "MtmVec.h"
#include "MtmMat.h"
#include <algorithm>
#include <vector>
#include <functional>

int op_increase(int* i) { (*i)--; }

int main() {
    auto d = Dimensions(1, 5);

    auto x = MtmMat<int>(d, 1);
    x = x+-x;
    x.print();
    //auto v = std::vector<std::vector<int>>(5,std::vector<int>(5,1));
    ////https://stackoverflow.com/questions/641864/returning-a-pointer-to-a-vector-element-in-c
    //for (auto i = v.begin(); i != v.end(); ++i) {
    //    for (auto j = (*i).begin(); j != (*i).end(); ++j) {
    //        op_increase(&(*j));
    //        cout << *j << " ";
    //    }
    //    cout << "\n";
    //}



    auto h = 1;
}