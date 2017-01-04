#pragma once
/**
 * 空类实例
 */
#include <iostream>
using namespace std;

class Person
{};

int main()
{
	Person person;
	cout << "sizeof Person object:" << sizeof(person) << endl;
	return 0 ;
}
