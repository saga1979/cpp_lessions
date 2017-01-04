#ifndef __virtual_func_table_h__
#define __virtual_func_table_h__
#include <iostream>
#include <cstdint>
#include <string>
using namespace std;

class Person
{
protected:
	string _name;
public:
	virtual void print()
	{
		cout << "person" << endl;
	}
	virtual void name() const
	{
		cout << "person name" << endl;
	}
};

class Father :  public Person
{
public:
	virtual void print()
	{
		cout << "father" << endl;
	}
};

class Monther :  public Person
{
public:
	virtual void print()
	{
		cout << "monther" << endl;
	}
};

class Child :  public Father,  public Monther
{
public:

};

typedef void(*FUNC)();
int main()
{	

	Child p;
	FUNC func = (FUNC) *(int64_t*)*(int64_t*)&p;
	func();

	func = (FUNC) *(int64_t*)* ((int64_t*)&p +1);
	func();
	return 0;
}




//#include <windows.h>
//#include <iostream>
//using namespace std;
//
//class Base1 {
//public:
//	virtual void f() { }
//};
//
//class Base2 {
//public:
//	virtual void f() { }
//};
//
//class Base3 {
//public:
//	virtual void f() { }
//};
//
//class Drive : public Base1, public Base2, public Base3 {
//};
//
//#define _ATL_PACKING 1
//
//#define offsetofclass(base, derived) \
//	((int64_t)(static_cast<base*>((derived*)_ATL_PACKING))-_ATL_PACKING)
//
//int main() {
//	cout << offsetofclass(Base1, Drive) << endl;
//	cout << offsetofclass(Base2, Drive) << endl;
//	cout << offsetofclass(Base3, Drive) << endl;
//	return 0;
//}


#endif
