#include "lite_queque.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#ifdef _DEBUG
static const int ALLOC_STEP = 2;
#else
static const int ALLOC_STEP = 100;

#endif // DEBUG




void lite_queue_inqueue(LiteQueuePtr* ptr, const char data)
{
	assert(ptr != 0);
	//考虑空队列
	if (*ptr == 0)
	{
		*ptr = calloc(1, sizeof(LiteQueue));
	}
	//考虑队列内部数据空间不足时扩容
	if ((*ptr)->size + 1 > (*ptr)->capacity)
	{
		//给数据成员分配空间
		(*ptr)->data = realloc((*ptr)->data, (*ptr)->capacity + ALLOC_STEP);
		(*ptr)->capacity = (*ptr)->capacity + ALLOC_STEP;
	}
	//给队列内部数据按索引赋值(尾部)
   (*ptr)->data[(*ptr)->size] = data;
   (*ptr)->size += 1;

}
char lite_queue_dequeue(LiteQueuePtr* ptr)
{
	assert(ptr != 0 && (*ptr) != 0 && (*ptr)->size !=0);

	char ret = (*ptr)->data[0];

	char* pdata = malloc((*ptr)->capacity);
	memcpy(pdata, (*ptr)->data + 1, (*ptr)->size - 1);
	free((*ptr)->data);
	(*ptr)->data = pdata;

	//memmove((*ptr)->data, (*ptr)->data + 1, (*ptr)->size - 1);

	(*ptr)->size -= 1;

	return ret;
}

bool lite_queue_empty(LiteQueuePtr queue)
{
	assert(queue != 0);
	return queue->size == 0;
}

void lite_queue_foreach(LiteQueuePtr queue, LITE_FUNC func)
{
	assert(queue);
	for (int i = 0; i < queue->size; i++)
	{
		func(queue->data[i]);
	}
}