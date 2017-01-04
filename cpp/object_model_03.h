#pragma once
/**
 * 成员函数和虚函数
 */
#include <iostream>
using namespace std;

struct Person
{
	virtual void print()
	{
		cout << "Person::print()" << endl;
	}
};

struct PersonNoVirtual
{
	void print()
	{
		cout << "Person::print()" << endl;
	}
};

int main()
{
	cout << "sizeof Person :" << sizeof(Person) << endl;
	cout << "sizeof PersonNoVirtual :" << sizeof(PersonNoVirtual) << endl;
	return 0;
}
