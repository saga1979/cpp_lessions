
#include <stdio.h>
#include <stdlib.h>

#include "dlink.h"


typedef struct _Person Person;

struct _Person
{
	char *name;
	int account;
	int index;
	double balance;
};


Person* person_new()
{
	Person *person = (Person *)malloc(sizeof(Person));

	person->name = (char *)calloc(256, 1);

	return person;
}

void person_free(Person *person)
{
	free(person->name);
	free(person);
}

void node_data_del(void* person)
{
	person_free((Person*)person);
}

int main()
{
	//打开文件
	FILE *cfPtr = fopen("clients.dat", "w+");

	if (cfPtr == 0)
	{
		printf("File could not be opened\n");
		return -1;
	}
	//录入提示信息
	printf("Enter the index , account, name, and balance.\n");
	printf("Enter 0 0 0 0 to end input.\n");
	//创建新链表头结点
	LiteLink *header = dlink_new();
	LiteLink *node = header;

	//循环录入数据
	while (1)
	{
		printf("? ");
		//1 格式化录入数据
		Person *person = person_new();
		scanf("%d%d%s%lf",&person->index, &person->account, person->name, &person->balance);
		//2 如果输入以0 作为account的数据，终止循环
		if (person->account == 0)
		{
			break;
		}
		//3 向链表追加数据
		if (person->index < 0)
		{
			dlink_append_data(node, person);
		}
		else
		{
			node =  dlink_insert_data(node, person->index, person);
			//如果需要更新链表头
			if (person->index == 0)
			{
				header = node;
			}
		}
	}

	//遍历链表，写入文件
	node = header;
	while (node)
	{
		//取数据
		Person* person = (Person*)dlink_data(node);
		//格式化打印到文件中
		fprintf(cfPtr, "%d %d %s %.2f\n",
			person->index, person->account, person->name, person->balance);
		//打印到窗口
		fprintf(stdout, "%d %d %s %.2f\n",
			person->index, person->account, person->name, person->balance);
		//下一个
		node = dlink_next(node, 1);
	}
	//关闭文件
	fclose(cfPtr);
	//删除链表
	dlink_free(header, node_data_del);

}





