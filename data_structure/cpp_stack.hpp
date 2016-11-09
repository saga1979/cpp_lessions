#include <cstdlib>
#include <iostream>
#include <cassert>
#include <climits>

using namespace std;

struct StackNode {   /* self-referential structure */
	int data;
	StackNode *nextPtr;
};
class Stack
{
	StackNode* m_pTopNode;
	int m_size;
public:
	enum {
		INVALID_DATA = INT_MIN,
	};
	Stack();
	void push(int data);//������ջ
	int  top();//��ȡ����
	void pop();//��ջ
	int size() { return m_size; }//ջ��С
	bool empty() { return m_size == 0; }//ջ�Ƿ�Ϊ��
};
Stack::Stack()
{
	m_pTopNode = 0;
	m_size = 0;
}
void Stack::push(int data)
{
	if (m_pTopNode == 0)
	{
		m_pTopNode = (StackNode*)calloc(1, sizeof(StackNode));
	}
	else
	{
		StackNode* pNode = (StackNode*)calloc(1, sizeof(StackNode));
		pNode->nextPtr = m_pTopNode;
		m_pTopNode = pNode;
	}
	m_pTopNode->data = data;
	m_size++;
}
int Stack::top()
{
	if (m_pTopNode)
		return m_pTopNode->data;
	return Stack::INVALID_DATA;//�ٶ���ʾ��������
}

void Stack::pop()
{
	if (!m_pTopNode)
	{
		return;
	}
	StackNode* t = m_pTopNode;
	m_pTopNode = m_pTopNode->nextPtr;
	free(t);
	m_size--;

}

int main()
{
	Stack s;
	cout << "Stack empty: " << s.empty() << endl;
	for (int i = 0; i < 10; i++)
	{
		s.push(i);
		cout << "stack top: " << s.top() << endl;
	}
	cout << "after push 10 into stack, stack size: " << s.size() << endl;

	while (!s.empty())
	{
		cout << "stack top: " << s.top() << endl;
		s.pop();
	}

	return 0;
}
