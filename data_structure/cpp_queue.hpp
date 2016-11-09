#pragma once
#include <limits.h>
struct QueueNode {
	int data;
	QueueNode* next;
	QueueNode()
	{
		next = 0;
	}
};
class Queue
{
	QueueNode* m_front;
	QueueNode* m_back;
	int m_size;
public:
	enum {
		INVALID_DATA = INT_MIN,
	};
	Queue();
	void	push(int);
	int		front();
	int		back();
	void	pop();
	int		size();
};
