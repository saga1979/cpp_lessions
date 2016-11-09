#include "cpp_list.hpp"
class list_node
{
public:
	list_node():next(0), pre(0)
	{
		
	}
	list_node(int v) :list_node()
	{
		data = v;
	}
	int data;
	list_node* next;
	list_node* pre;
};
list::list():m_header(0), m_tail(0), m_size(0)
{
}
void list::insert(int pos, int data)
{
	if (pos > size())
	{
		return push_back(data);
	}

	if (pos <= 0)
	{
		return push_front(data);
	}

	list_node* tNode = m_header;
	while (pos-- > 0 && tNode)
	{
		tNode = tNode->next;
	}
	list_node* new_node = new list_node(data);
	new_node->next = tNode->next;
	new_node->pre = tNode;

	tNode->next->pre = new_node;
	tNode->next = new_node;
	
}



void list::push_back(int data)
{
	m_size++;
	if (m_tail == 0)
	{
		m_tail = new list_node;
		m_tail->data = data;
		m_header = m_tail;
		return;
	}

	m_tail->next = new list_node;
	m_tail->next->pre = m_tail;
	m_tail = m_tail->next;
	m_tail->data = data;
}

void list::push_front(int data)
{
	m_size++;
	if (m_header == 0)
	{
		m_header = new list_node;
		m_header->data = data;
		m_tail = m_header;
		return;
	}

	m_header->pre = new list_node(data);
	m_header->pre->next = m_header;
	m_header = m_header->pre;
}

void list::remove(int data)
{
	list_node* pNode = m_header;
	while (pNode)
	{
		if (pNode->data == data)
		{
			if(pNode->pre)
				pNode->pre->next = pNode->next;
			if(pNode->next)
				pNode->next->pre = pNode->pre;
			if (pNode == m_header)//只有一个节点
			{
				m_header = 0;
				m_tail = 0;
			}
			delete pNode;
			m_size--;
			break;
		}
		pNode = pNode->next;
	}
}

int list::value(int pos)
{
	list_node* pNode = m_header;
	while (pos-- > 0 && pNode)
	{
		pNode = pNode->next;
	}
	return 0;
}

int list::back()
{
	return m_tail != 0? m_tail->data: INVALID_VALUE;
}

int list::front()
{
	return m_header != 0?m_header->data : INVALID_VALUE;
}

int list::size()
{
	return m_size;
}
