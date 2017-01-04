#pragma once


#include <iostream>
#include <cstdint>
#include "object_model_pub.h"
using namespace std;

struct Person
{
    virtual void print()
    {
        cout << "Person::print()" << endl;
    }
    virtual void print2()
    {
        cout << "Person::print2()" << endl;
    }
};

typedef void(*FUNC)();
int main()
{
    Person p;
    FUNC func = (FUNC) *((PTR_TYPE*)*((PTR_TYPE*)&p + 0) + 0);
    func();
    func = (FUNC) *( (PTR_TYPE*)(*(PTR_TYPE*)&p + 0) + 1);
    func();
    cout  << (PTR_TYPE*) *(PTR_TYPE*) ((PTR_TYPE*)(*(PTR_TYPE*)&p + 0) + 2 )<< endl;
    return 0;
}


//#include <iostream>
//using namespace std;
//
//class Class {
//    virtual void f() { cout << "Class::f" << endl; }
//    virtual void g() { cout << "Class::g" << endl; }
//};
//
//int main() {
//    Class objClass;
//
//    cout << "Address of virtual point64_ter " << (int64_t*)(&objClass + 0) << endl;
//    cout << "Value at virtual point64_ter i.e. Address of virtual table "
//        << (int64_t*)*(int64_t*)(&objClass + 0) << endl;
//
//    cout << endl << "Information about VTable" << endl << endl;
//    cout << "Value at 1st entry of VTable "
//        << (int64_t*)*((int64_t*)*(int64_t*)(&objClass + 0) + 0) << endl;
//    cout << "Value at 2nd entry of VTable "
//        << (int64_t*)*((int64_t*)*(int64_t*)(&objClass + 0) + 1) << endl;
//    cout << "Value at 3rd entry of VTable "
//        << (int64_t*)*((int64_t*)*(int64_t*)(&objClass + 0) + 2) << endl;
//    cout << "Value at 4th entry of VTable "
//        << (int64_t*)*((int64_t*)*(int64_t*)(&objClass + 0) + 3) << endl;
//
//    return 0;
//}