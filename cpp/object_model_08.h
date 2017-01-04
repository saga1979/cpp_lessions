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
struct Father :  virtual public  Person
{};
struct Monther : virtual  public Person
{};
struct Child : virtual public  Father, virtual public Monther
{};

typedef void(*FUNC)();

int main()
{
    Child child;
    cout << "Child object size:" << sizeof(child) << endl;

    /*PTR_TYPE* person_vptr = (PTR_TYPE*)*(PTR_TYPE*)&child;
    cout << "person vtable address:"
        << person_vptr << endl;

    PTR_TYPE* father_vptr 
        = (PTR_TYPE*)*(PTR_TYPE*)((PTR_TYPE)&child + sizeof(Person));
    cout << "Father vtable address:"
        << father_vptr << endl;;

    PTR_TYPE* mother_vptr = 
        (PTR_TYPE*)*(PTR_TYPE*)((PTR_TYPE)&child + sizeof(Father) + sizeof(Person) );
    cout << "Mother vtable address:"
        << mother_vptr << endl;*/
    return 0;
}