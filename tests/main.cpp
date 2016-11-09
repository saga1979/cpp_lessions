#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

template <typename T>
struct LinkNode
{
	T data;
	LinkNode *pre;
	LinkNode *next;
	LinkNode() :pre(0), next(0) {}
};

template<typename T>
LinkNode<T>* link_append(LinkNode<T>* node, T data)
{
	LinkNode<T>* new_node = new LinkNode<T>;
	new_node->data = data;
	node->next = new_node;
	new_node->pre = node;
	return 0;
}

struct Person
{
	string name;
	string age;
	string sex;
	Person() {}
	Person(const Person& right)
	{
		name = right.name;
		age = right.age;
		sex = right.sex;
		cout << "Person Object copy: " << (int)this << endl;
	}

};
template<typename T>
void test_fun(T obj)
{

}

int main()
{
	char** pp = (char**)calloc(30, sizeof(char*));

	for (int i = 0; i < 30; i++)
	{
		*(pp+i) = (char*)malloc(30);
	}

	for (int i = 0; i < 30; i++)
	{
		free(pp[i]);
	}

	free(pp);

	return 0;
}