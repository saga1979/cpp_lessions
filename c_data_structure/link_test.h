
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

static FILE *cfPtr = 0;

void node_data_print(void* data)
{
	//取数据
	Person* person = (Person*)(data);
	//格式化打印到文件中
	fprintf(cfPtr, "%d %d %s %.2f\n",
		person->index, person->account, person->name, person->balance);
	
	//打印到窗口
	fprintf(stdout, "index:%d account:%d name:%s balance:%.2f\n",
		person->index, person->account, person->name, person->balance);
}

int main()
{
	//打开文件
	cfPtr = fopen("clients.dat", "w+");

	if (cfPtr == 0)
	{
		printf("File could not be opened\n");
		return -1;
	}
	//录入提示信息
	printf("Enter the index , account, name, and balance.\n");
	printf("Enter 0 0 0 0 to end input.\n");
	//创建新链表
	LiteList *list = dlist_new();
	dlist_data_free_fun(list, node_data_del);

	//循环录入数据
	while (1)
	{
		printf("? ");
		//1 格式化录入数据
		Person *person = person_new();
		int ret = scanf("%d%d%s%lf",&person->index, &person->account, person->name, &person->balance);
		//2 如果没有得到合法的数据,终止循环
		if (ret < 4)
		{
			break;
		}
		
		//3 向链表插入数据
		dlist_insert_before(list, person->index, person);

	}
	//打印链表数据
	dlist_foreach(list, node_data_print);
	//关闭文件
	fclose(cfPtr);
	//删除链表
	
	dlist_free(list);

	char* input_name = 0;
	//输入用户名

	int size = dlist_size(list);
	Person* p = 0;
	for (int index = 0; index < size; index++)
	{
		p = (Person*)dlist_data(list, index);
		if (strcmp(p->name, "sfdsdf") == 0)
		{
			break;
		}
	}

	dlist_remove(list, p);

}





