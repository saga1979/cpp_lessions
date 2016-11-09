#pragma once
#include <iostream>
using namespace std;
enum Type {
	CHINESE,
	JAPANESE,
	XXX,
};
class Person
{
	Type m_type;
public:
	Person(Type t) :m_type(t) {}
	void set_type(Type t)
	{
		m_type = t;
	}
	Type get_type() const
	{
		return m_type;
	}
};

void print(const Person* p)
{
	//.............
	switch (p->get_type())
	{
	case CHINESE:
		cout << "hello c" << endl;
		break;
	case JAPANESE:
		cout << "hello j" << endl;
		break;
	case XXX:
		cout << "hello xxx" << endl;
	default:
		break;
	}
	//..............
}

int main()
{
	Person p(JAPANESE);

	print(&p);
	return 0;
}
