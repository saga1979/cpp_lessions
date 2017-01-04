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
    Father father;
    cout << "father object size:" << sizeof(Father) << endl;
    FUNC func = (FUNC) *(PTR_TYPE*)*(PTR_TYPE*)&father;
    func();//调用Father::print

    cout << endl << endl;
    Child child;    
    cout << "Child object size:" << sizeof(child) << endl;

    func = (FUNC) *(PTR_TYPE*)*(PTR_TYPE*)&child;
    func();//调用Father::print
    func = (FUNC) *(PTR_TYPE*)*(PTR_TYPE*)((PTR_TYPE)&child + sizeof(Father));
    func();//调用Mather::print
    return 0;
}
