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
	//����ͷ
	if (node->pre == 0 /*|| node == header*/)
	{
		if (node->next)
		{
			node->next->pre = 0;
		}
		header =  node->next;
	}
	//�Ǳ�ͷ
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
* �ڸ��������ָ��λ�ò����û��ṩ������
*
* @author Administrator (2016/9/14)
*
* @param header ����ͷ
* @param pos
*  			Ҫ�����λ�ã���0Ϊ������ʼ��,������������ܳ��ȣ�������������
* @param data Ҫ���������
*
* @return struct Node*  ���������ڵ�
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

	//headerΪ�գ���Ҫ����һ���ڵ���Ϊ����ͷ���൱�ڴ�������
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
	//����ڵ�
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
* ������׷������
*
* @author Administrator (2016/9/18)
*
* @param node  �������Ѿ����ڵĽڵ�
* @param data  �û�����
*
* @return Node* ���ݹ��ص��ָ��
*/
LiteLink* dlink_append_data(LiteLink* node, void*data)
{
	//�ҵ����һ���ڵ�
	while (node->next != 0)
	{
		node = node->next;
	}
	//������ڵ��Ѿ�¼�������ݣ�����һ���½ڵ�
	if (node->data != 0)
	{
		LiteLink *new_node = dlink_new();
		new_node->pre = node;
		node->next = new_node;

		//ָ�����һ���ڵ㡱
		node = node->next;
		//node = new_node;
	}
	//�����ݡ����ء����ڵ�
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
