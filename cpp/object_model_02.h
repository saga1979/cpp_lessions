#pragma once
/**
 * 数据成员和虚函数
 */
#include <iostream>
using namespace std;

struct Person
{
	char  first_char;
	int   earnings;
};

class Father : public Person
{
protected:
	int sth;
	virtual void fun() {}
};

int main()
{
	cout << "sizeof Person object:" << sizeof(Person) << endl;
	cout << "sizeof Father object:" << sizeof(Father) << endl;
	return 0;
}
