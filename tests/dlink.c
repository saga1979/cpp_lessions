#include <stdlib.h>

#include "dlink.h"

struct _LiteLink
{
	void *data;
	struct _LiteLink *next;
	struct _LiteLink *pre;
};

static void dlink_free_node(LiteLink* node)
{
	free(node);
}


LiteLink* dlink_new()
{
	LiteLink *node = calloc(1, sizeof(LiteLink));
	return node;
}


void dlink_free(LiteLink* header, DEL_FUN data_del_fun)
{
	LiteLink* node = header;
	while (node != 0)
	{
		if (data_del_fun)
		{
			data_del_fun(node->data);
		}
		header = header->next;
		free(node);
		node = header;
	}
}
LiteLink*	dlink_remove_data(LiteLink* list, void* data)
{
	LiteLink* tmp = list;
	while (tmp)
	{
		if (tmp->data == data)
		{

		}
	}
	return 0;
}
LiteLink* dlink_remove_node(LiteLink* header, LiteLink* node)
{
	if (node == 0 || header == 0)
	{
		return header ;
	}
	//链表头
	if (node->pre == 0 /*|| node == header*/)
	{
		if (node->next)
		{
			node->next->pre = 0;
		}
		header =  node->next;
	}
	//非表头
	else
	{
		node->pre->next = node->next;
		if (node->next)
		{
			node->next->pre = node->pre;
		}
	}

	return header;
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
LiteLink* dlink_insert_data(LiteLink *header, int pos, void *data)
{

	if (header && header->data == 0)
	{
		header->data = data;
		return header;
	}

	LiteLink *new_node = calloc(1, sizeof(LiteLink));
	new_node->data = data;

	//header为空，需要创建一个节点作为链表头，相当于创建链表
	if (header == 0)
	{
		return new_node;
	}

	int len = 0;
	LiteLink *cur_node = header;
	while (cur_node->next && len++ < pos)
	{
		cur_node = cur_node->next;
	}
	//插入节点
	if (pos == 0)
	{
		new_node->next = header;
		header->pre = new_node;
	}
	else
	{
		new_node->pre = cur_node->pre;
		if (cur_node->pre)
		{
			cur_node->pre->next = new_node;
		}
		new_node->next = cur_node;
		cur_node->pre = new_node;
	}

	return new_node;
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
LiteLink* dlink_append_data(LiteLink* node, void*data)
{
	//找到最后一个节点
	while (node->next != 0)
	{
		node = node->next;
	}
	//如果最后节点已经录入了数据，生成一个新节点
	if (node->data != 0)
	{
		LiteLink *new_node = dlink_new();
		new_node->pre = node;
		node->next = new_node;

		//指向“最后一个节点”
		node = node->next;
		//node = new_node;
	}
	//将数据“挂载”到节点
	node->data = data;

	return node;
}

LiteLink * dlink_next(LiteLink * node, int n)
{
	while (n-- > 0 && node)
	{
		node = node->next;
	}
	return node;
}

void * dlink_data(LiteLink * node)
{
	return node->data;
}
