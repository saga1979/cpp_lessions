#pragma once

#include "lite_queque.h"

#include <stdio.h>


void instructions(void);

void printElement(char data)
{
	printf("%c ", data);
}
int main()
{
	LiteQueuePtr pQueue = 0;
	
	char item;

	instructions();
	printf("? ");
	int choice;
	scanf("%d", &choice);

	while (choice != 4) 
	{

		switch (choice) 
		{

		case 1:
		{
			printf("Enter a character: ");
			scanf("\n%c", &item);
			lite_queue_inqueue(&pQueue, item);
		}
			break;
		case 2:
		{
			if (!lite_queue_empty(pQueue)) 
			{
				item = lite_queue_dequeue(&pQueue);
				printf("\'%c\' has been dequeued.\n", item);
			}

		}
			break;

		case 3:
		{
			printf("queue elements:\n");
			lite_queue_foreach(pQueue, printElement);
			printf("\n");
		}
		break;

		default:
			printf("Invalid choice.\n\n");
			instructions();
			break;
		}

		printf("? ");
		scanf("%d", &choice);
	}

	printf("End of run.\n");
	return 0;
}

void instructions(void)
{
	printf("Enter your choice:\n"
		"   1 to add an item to the queue\n"
		"   2 to remove an item from the queue\n"
		"   3 show all elements in the queue\n"
		"   4 to end\n");
}