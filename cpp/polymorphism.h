#pragma once
#include <iostream>
using namespace std;

class Person
{
public:
	virtual ~Person()
	{
		cout << "person destructed" << endl;
	}
	virtual const char* get_info() const = 0;
};

class Chinese : public Person
{
public:
	~Chinese()
	{
		cout << "chinese destructed" << endl;
	}
	const char* get_info() const;
};
class Japanese :public Person
{
public:
	const char* get_info() const;
};
class XXX :public Person
{
public:
	const char* get_info() const
	{
		return "xxx";
	}
};

const char* Chinese::get_info() const
{
	return  "hello chinese";
}

const char* Japanese::get_info() const
{
	return  "hello ja";
}

void print(const Person* p)
{
	const char* info = p->get_info();

	cout << info << endl;
}

int main()
{
	Person *p = new Chinese;
	print(p);
	delete p;
	return 0;
}