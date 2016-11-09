#ifndef __CPP_LIST_HPP__
#define __CPP_LIST_HPP__
#include <climits>
class list_node;
class list
{
	list_node *m_header;
	list_node *m_tail;
	int		m_size;
public:
	enum {
		INVALID_VALUE = INT_MIN,
	};
	list();
	void	insert(int pos, int data);
	void	push_back(int data);
	void	push_front(int data);
	void	remove(int data);
	int		value(int pos);
	int		back();
	int		front();
	int		size();
};

#endif


