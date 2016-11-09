
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
	//ȡ����
	Person* person = (Person*)(data);
	//��ʽ����ӡ���ļ���
	fprintf(cfPtr, "%d %d %s %.2f\n",
		person->index, person->account, person->name, person->balance);
	
	//��ӡ������
	fprintf(stdout, "index:%d account:%d name:%s balance:%.2f\n",
		person->index, person->account, person->name, person->balance);
}

int main()
{
	//���ļ�
	cfPtr = fopen("clients.dat", "w+");

	if (cfPtr == 0)
	{
		printf("File could not be opened\n");
		return -1;
	}
	//¼����ʾ��Ϣ
	printf("Enter the index , account, name, and balance.\n");
	printf("Enter 0 0 0 0 to end input.\n");
	//����������
	LiteList *list = dlist_new();
	dlist_data_free_fun(list, node_data_del);

	//ѭ��¼������
	while (1)
	{
		printf("? ");
		//1 ��ʽ��¼������
		Person *person = person_new();
		int ret = scanf("%d%d%s%lf",&person->index, &person->account, person->name, &person->balance);
		//2 ���û�еõ��Ϸ�������,��ֹѭ��
		if (ret < 4)
		{
			break;
		}
		
		//3 �������������
		dlist_insert_before(list, person->index, person);

	}
	//��ӡ��������
	dlist_foreach(list, node_data_print);
	//�ر��ļ�
	fclose(cfPtr);
	//ɾ������
	
	dlist_free(list);

	char* input_name = 0;
	//�����û���

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





