#pragma once
/**
 * 数据成员的内存布局
 */
#include <iostream>
using namespace std;

struct Person
{
	char  first_char;
	int   earnings;
};

struct Father : public Person
{
	int sth;
};

int main()
{
	Father father;
	cout << "father object address:" << &father << endl;
	*(char*)&father = 'z';
	cout <<"father's first char:"<< father.first_char << endl;
	*(int*)((char*)&father + 4) = 1000000;
	cout << "father's earning:"<< father.earnings << endl;
	return 0;
}
