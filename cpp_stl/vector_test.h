//#pragma once
//
//#include <string>
//#include <iostream>
//#include <list>
//#include <algorithm>
//using namespace std;
//
//class Object
//{
//	int m_data;
//public:
//	Object(int data = 0) :m_data(data)
//	{}
//	bool operator == (const Object& right)
//	{
//		return this->m_data == right.m_data;
//	}
//
//	int data() const { return m_data; }
//};
//
//bool remove_cond(const Object* po)
//{
//	return po->data() < 5;
//}
//
//struct FuncObject
//{
//	void operator() (const Object* po)
//	{
//		cout << po->data() << endl;
//	}
//};
//
//int main()
//{
//	list<Object*> os;
//	for (int i = 0; i < 10; i++)
//	{
//		os.push_back(new Object(i));
//	}
//	for (list<Object*>::iterator it = os.begin(); it != os.end();)
//	{
//		if (remove_cond(*it))
//		{
//			it = os.erase(it);
//		}
//		else
//		{
//			it++;
//		}
//	}
//	std::for_each(os.begin(), os.end(), FuncObject());
//}

#include <list>
#include <algorithm>
#include <iterator>
using namespace std;
int main() {
	int arr1[] = { 1, 3, 5, 7, 9 };    
	int arr2[] = { 2, 4, 6, 8, 10 };    
	list<int>  l1(arr1, arr1 + 5); // initialize l1 with arr1    
	list<int>  l2(arr2, arr2 + 5); // initialize l2 with arr2    
	copy(l1.begin(), l1.end(), back_inserter(l2));  // use back_inserter   
	// adds contents of l1 to the end of l2 = { 2, 4, 6, 8, 10, 1, 3, 5, 7, 9  }    
	copy(l1.begin(), l1.end(), front_inserter(l2));  // use front_inserter    
    // adds contents of l1 to the front of l2 = { 9, 7, 5, 3, 1, 2, 4, 6, 8, 10 }    
	copy(l1.begin(), l1.end(), inserter(l2, l2.begin()));   
	
	// adds contents of l1 at the ¡±old¡± beginning of l2 = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 }    
	return 0;
}

