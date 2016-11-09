#include <stdlib.h>

#include "dlink.h"

struct _LinkNode
{
	void* data;
	struct _LinkNode *next;
	struct _LinkNode *pre;
};

typedef struct _LinkNode LinkNode;

LinkNode* link_node_new()
{
	LinkNode* p = (LinkNode*)calloc(1, sizeof(LinkNode));

	return p;
}

void link_node_free(LinkNode* node)
{
	free(node);
}

struct _LiteList
{
	struct _LinkNode *front;
	struct _LinkNode *end;
	int size;
	LIST_DATA_FUN del_fun;
};

static void dlink_free_node(LiteList* node)
{
	free(node);
}


LiteList* dlist_new()
{
	LiteList *node = calloc(1, sizeof(LiteList));
	return node;
}


void dlist_free(LiteList* list)
{
	while (list->front != 0)
	{
		if (list->del_fun)
		{
			list->del_fun(list->front->data);
		}
		LinkNode* node = list->front;
		list->front = list->front->next;
		free(node);		
	}

	list->size = 0;
	free(list);
}

void	dlist_data_free_fun(LiteList* list, LIST_DATA_FUN fun)
{
	list->del_fun = fun;
}
LiteList*	dlist_remove(LiteList* list, void* data)
{
	LinkNode* node = list->front;
	while (node)
	{
		if (!(node->data == data))
		{
			node = node->next;
			continue;
		}
		if (list->del_fun)
		{
			list->del_fun(data);
		}
		
		if (node->pre)
			node->pre->next = node->next;
		else
			list->front = node->next; //更新表头
		if (node->next)
			node->next->pre = node->pre;
		else
			list->end = node->pre;//更新表尾

		free(node);
		list->size--;

		break;
	}
	return list;
}

/**
* 在给定链表的指定位置插入用户提供的数据
*
* @author Administrator (2016/9/14)
*
* @param header 链表头
* @param pos
*  			要插入的位置（以0为索引开始）,如果大于链表总长度，就在最后面插入
* @param data 要插入的数据
*
* @return struct Node*  插入的链表节点
*/
LiteList* dlist_insert_before(LiteList *list, int pos, void *data)
{
	if (pos < 0 || !list->front || list->size -1 < pos)
	{
		return dlist_append(list, data);
	}
	list->size++;
	LinkNode* pNode = link_node_new();
	pNode->data = data;

	int len = 0;
	LinkNode *cur_node = list->front;
	while (cur_node && len++ < pos)
	{
		cur_node = cur_node->next;
	}
	//插入节点
	if (pos == 0)
	{
		pNode->next = list->front;
		list->front->pre = pNode;	
		list->front = pNode;
	}
	else 
	{
		pNode->pre = cur_node->pre;
		if (cur_node->pre)
		{
			cur_node->pre->next = pNode;
		}
		pNode->next = cur_node;
		cur_node->pre = pNode;
	}
	
	return list;
}
LiteList * dlist_insert_after(LiteList *list, int pos, void * data)
{
	return dlist_insert_before(list, pos+1, data);
}
/**
* 向链表追加数据
*
* @author Administrator (2016/9/18)
*
* @param node  链表中已经存在的节点
* @param data  用户数据
*
* @return Node* 数据挂载点的指针
*/
LiteList* dlist_append(LiteList* list, void*data)
{
	list->size++;
	LinkNode* pNode = link_node_new();
	pNode->data = data;
	if (list->front == 0)
		list->front = pNode;
	if (list->end == 0)
	{
		list->end = pNode;
		return list;
	}
	pNode->pre = list->end;
	list->end->next = pNode;
	list->end = pNode;
	return list;
}

void * dlist_data(LiteList * list, int pos)
{
	LinkNode* pNode = list->front;
	while (pNode && pos-- > 0)
	{
		pNode = pNode->next;
	}
	return pNode?pNode->data:0;
}

int	dlist_size(LiteList* list)
{
	return list->size;
}

void	dlist_foreach(LiteList* list, LIST_DATA_FUN fun)
{
	if (!fun || !list) return;
	LinkNode* pNode = list->front;
	while (pNode)
	{
		if (fun(pNode->data) != 0)
		{
			break;
		}
		pNode = pNode->next;
	}
}
