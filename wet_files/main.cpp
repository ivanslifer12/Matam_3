#include <iostream>

#include "MtmVec.h"
#include "Complex.h"
#include <vector>

#include <assert.h>
using namespace MtmMath;
using std::cout;
using std::endl;

void exceptionsTest() {
    try {
        MtmVec<float> v(0,5);
        assert(false);
    }
    catch (MtmExceptions::IllegalInitialization& e){
        cout<< e.what() <<endl;
    }

/*
    try {
        MtmMat<int> m1(Dimensions(10,100000000000),5);
        assert(false);
    }
    catch (MtmExceptions::OutOfMemory& e){
        cout<< e.what() <<endl;
    }
*/

/*    try {
        MtmVec<int> v1(3,5);
        MtmMat<int> m1(Dimensions(3,3),5);
        MtmMat<int> m3=m1+v1;
        assert(false);
    }
    catch (MtmExceptions::DimensionMismatch& e){
        cout<< e.what() <<endl;
    }*/
/*    try {
        MtmMat<int> m1(Dimensions(3,3),5);
        m1.reshape(Dimensions(2,3));
        assert(false);
    }
    catch (MtmExceptions::ChangeMatFail& e){
        cout<< e.what() <<endl;
    }*/

/*    try {
        MtmMat<int> m1(Dimensions(3,3),5);
        m1[4][3]=5;
        assert(false);
    }
    catch (MtmExceptions::AccessIllegalElement& e){
        cout<< e.what() <<endl;
    }*/
}

void constructors() {
    MtmVec<int> v1(5,3);
    //MtmMat<int> m1(Dimensions(3,3),0);
    //MtmMatSq<int> m2(3,1);
    //MtmMatTriag<int> m3(3,1,true);
}

void dataTypes() {
    MtmVec<int> v1(5,3);
    MtmVec<double > v2(5,3);
    MtmVec<float> v3(5,3);
    MtmVec<Complex> v4(5,Complex(3,4));
}

void FuncExample() {
    class maxAbsolute {
        int currMax;
    public:
        maxAbsolute() : currMax(0) {}
        void operator()(int x) {
            int absX = x>(-x) ? x : -x;
            if (currMax<absX) {currMax=absX;}
        }
        int operator*() { return  currMax;}
    };
    MtmVec<int> v(5,0);
    v[1]=3;v[2]=-7;v[3]=-1;v[4]=2;
    //[5,3,-7,-1,2]
/*    MtmMat<int> m(Dimensions(2,3),0);
    m[0][1]=1;m[1][0]=2;
    m[0][1]=3;m[1][1]=2;
    m[0][2]=5;m[1][2]=-6;*/
    maxAbsolute f;
    assert (v.vecFunc(f)==7);
    //MtmVec<int> res(m.matFunc(f));
    assert(res[0]==2 and res[1]==3 and res[2]==6);
}

/*
void iterators() {
    MtmMatSq<int> m(2,0);
    m[1][0]=1;m[1][1]=2;

    int res_it[]={0,1,0,2};
    int res_nz_it[]={1,2};
    int i=0;
    for (MtmMatSq<int>::iterator it=m.begin();it!=m.end();++it) {
        assert (res_it[i]==(*it));
        ++i;
    }

    i=0;
    for (MtmMatSq<int>::nonzero_iterator it=m.nzbegin();it!=m.nzend();++it) {
        assert (res_nz_it[i]==(*it));
        ++i;
    }
}
*/

void warmUp(){
    exceptionsTest();
    //iterators();
    constructors();
    dataTypes();
    FuncExample();
    cout<<"warmUp Done! \n";
}

void vector_test(){
    MtmVec<int> v(5,1);
    try {
        v.resize(Dimensions(1, 5), 2);
        assert(false);
    }
    catch (MtmExceptions::ChangeMatFail& e){
        cout<< e.what() <<endl;
    }
    MtmVec<int> v1(5,2);
    MtmVec<int> res=v1-v;
    res.resize(Dimensions(8,1),0);
    res.resize(Dimensions(10,1),1);
    for (int i = 0; i < 5; ++i) {
        assert(res[i]==1);
    }
    int i=0;
    for(MtmVec<int>::nonzero_iterator nz_it=res.nzbegin();nz_it!=res.nzend();++nz_it,i++){
        assert(*nz_it==1);
    }
    assert(i==7);
    try {
        MtmVec<int> v10(1,0);
        MtmVec<int> v11(1,0);
        v11.transpose();
        v10+v11;
        assert(false);
    }
    catch (MtmExceptions::DimensionMismatch& e){
        cout<< e.what() <<endl;
    }
    MtmVec<int> v2(4,2);
    MtmVec<int> v3(6,4);
    v2.resize(Dimensions(7,1),4);
    v3.transpose();
    v3.resize(Dimensions(1,7),4);
    for (int j = 0; j < 6; ++j) {
        v2[j]=v3[j];
    }
    try {
        v2+v3;
        assert(false);
    }
    catch (MtmExceptions::DimensionMismatch& e){
        cout<< e.what() <<endl;
    }
    MtmVec<int>::iterator it1=v2.begin();
    int k = 0;
    for (MtmVec<int>::iterator it2=v3.begin(); it2!=v3.end(); ++it1,++it2,++k) {
        assert(*it1==*it2);
        v3=1+v3;
        assert(v3[0]==5);
        v3=v3-1;
        assert(v3[0]==4);
        v3=v3*(-1);
        assert(v3[0]==-4);
        v3=(-1)*v3;
        assert(v3[0]==4);
        v3=1-v3;
        assert(v3[0]==-3);
        v3=v3-1;
        assert(v3[0]==-4);
        v3=-v3;
    }
    assert(k==7);
    v3.resize(Dimensions(1,10),0);
    v3.resize(Dimensions(1,20),4);
    v3.resize(Dimensions(1,22),0);
    k=0;
    for (MtmVec<int>::nonzero_iterator it2=v3.nzbegin(); it2!=v3.nzend(); ++it2,++k) {
        assert(*it2==4);
    }
    assert(k==17);
    cout<<"vector test done!\n";
}

int main() {
    warmUp();
    //triangle_test();
    //vector_test();
    cout<<"tests done!\n";
    return 0;

}

