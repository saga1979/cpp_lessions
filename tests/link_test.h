
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
	//���ļ�
	FILE *cfPtr = fopen("clients.dat", "w+");

	if (cfPtr == 0)
	{
		printf("File could not be opened\n");
		return -1;
	}
	//¼����ʾ��Ϣ
	printf("Enter the index , account, name, and balance.\n");
	printf("Enter 0 0 0 0 to end input.\n");
	//����������ͷ���
	LiteLink *header = dlink_new();
	LiteLink *node = header;

	//ѭ��¼������
	while (1)
	{
		printf("? ");
		//1 ��ʽ��¼������
		Person *person = person_new();
		scanf("%d%d%s%lf",&person->index, &person->account, person->name, &person->balance);
		//2 ���������0 ��Ϊaccount�����ݣ���ֹѭ��
		if (person->account == 0)
		{
			break;
		}
		//3 ������׷������
		if (person->index < 0)
		{
			dlink_append_data(node, person);
		}
		else
		{
			node =  dlink_insert_data(node, person->index, person);
			//�����Ҫ��������ͷ
			if (person->index == 0)
			{
				header = node;
			}
		}
	}

	//��������д���ļ�
	node = header;
	while (node)
	{
		//ȡ����
		Person* person = (Person*)dlink_data(node);
		//��ʽ����ӡ���ļ���
		fprintf(cfPtr, "%d %d %s %.2f\n",
			person->index, person->account, person->name, person->balance);
		//��ӡ������
		fprintf(stdout, "%d %d %s %.2f\n",
			person->index, person->account, person->name, person->balance);
		//��һ��
		node = dlink_next(node, 1);
	}
	//�ر��ļ�
	fclose(cfPtr);
	//ɾ������
	dlink_free(header, node_data_del);

}





