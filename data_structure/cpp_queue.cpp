#include "cpp_queue.hpp"

Queue::Queue()
{
	m_front = 0;
	m_back = 0;
	m_size = 0;
}

void Queue::push(int data)
{
	QueueNode* pNode = new QueueNode;
	pNode->data = data;
	m_size++;
	if (m_size == 1)
	{
		m_front = pNode;
		m_back = pNode;
		return;
	}
	m_back->next = pNode;
	m_back = pNode;
}

int Queue::front()
{
	return m_front? m_front->data:Queue::INVALID_DATA;
}

int Queue::back()
{
	return m_back? m_back->data:Queue::INVALID_DATA;
}

void Queue::pop()
{
	if (m_size == 0)
		return;
	m_size--;
	QueueNode* pT = m_front;
	m_front = m_front->next;
	delete pT;
	if (m_size == 0)
		m_back = 0;
	
}

int Queue::size()
{
	return m_size;
}
