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
//must rewrite this
template <typename T>

 MtmMath<T>::MtmMath(Dimensions dim_t, const T& val=T())
{
    if (dim_t.getCol() <= 0 || dim_t.getRow() <= 0)
    {
        m == NULL;
        rows = 0;
        cols = 0;
        return;
    }
    m = new T*[dim_t.getRow()];
    for(int i = 0; i < dim_t.getRow(); i++)
    {
        m[i] = new T [dim_t.getCol()];
    }
    for(int i = 0; i < dim_t.getRow(); i++)
    {
        for(int j = 0; j < dim_t.getCol(); j++)
        {
            m[i][j] = val;
        }
    }
    rows = dim_t.getRow();
    cols = dim_t.getCol();

}



















