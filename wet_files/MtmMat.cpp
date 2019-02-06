#include <vector>
#include "MtmMat.h"
#include <iostream>
#include "MtmExceptions.h"
#include "Auxilaries.h"
#include "MtmVec.h"
#include "MtmExceptions.h"
#include "Complex.h"

using std::size_t;

using namespace MtmMath;


template<typename T>
T const &MtmMat<T>::MtmMatAccessor::operator[](string) const {
    return <#initializer#>;
}
