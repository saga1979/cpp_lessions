#ifndef __LITE_QUEUE_h__
#define __LITE_QUEUE_h__

#include <stdbool.h>

typedef struct _LiteQueue
{
	char *data;
	int size;
	int capacity;
}LiteQueue, *LiteQueuePtr;

typedef void(*LITE_FUNC)(char);


void lite_queue_inqueue(LiteQueuePtr* ptr, const char data);
char lite_queue_dequeue(LiteQueuePtr* ptr);

void lite_queue_foreach(LiteQueuePtr, LITE_FUNC);

bool lite_queue_empty(LiteQueuePtr);



#endif
