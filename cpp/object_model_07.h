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
};
struct Father : public Person
{
    virtual void print()
    {
        cout << "Father::print()" << endl;
    }
};
struct Monther : public Person
{
    virtual void print()
    {
        cout << "Monther::print()" << endl;
    }
};
struct Child : public Father, public Monther
{
};

typedef void(*FUNC)();

int main()
{
    Child child;
    cout << "Child object size:" << sizeof(child) << endl;
    PTR_TYPE* father_vptr = (PTR_TYPE*)*(PTR_TYPE*)&child;
    cout << "Father vtable address:" 
        << father_vptr << endl;;

    PTR_TYPE* mother_vptr = (PTR_TYPE*)*(PTR_TYPE*)((PTR_TYPE)&child + sizeof(Father));
    cout << "Mother vtable address:" 
        <<  mother_vptr << endl;

    (*(FUNC)*father_vptr)();
    (*(FUNC)*mother_vptr)();
    return 0;
}