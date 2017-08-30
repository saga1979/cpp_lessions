#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdbool>
#include <cstring>


static const int MAX_ACCOUNT_NUM = 100;
static const char* FILE_PATH = "credit.dat";


enum 
{
	INVALID_ACCOUNT_NO = 0,
};



typedef struct _ClientData
{
	int acctNum;
	char lastName[15];
	char firstName[10];
	double balance;
}ClientData;

static ClientData s_clients[MAX_ACCOUNT_NUM] = { 0 };

enum OperatorType
{
	INSERT,
	DELETE,
	UPDATE,
};

int	 updateData(OperatorType type, const ClientData* data);


int  enterChoice(void);
void textFile(FILE *);
void updateRecord(FILE *);
void newRecord(FILE *);
void deleteRecord(FILE *);

void initialize(FILE *);

int  recordIndex(int);

bool fileExist(const char* file)
{
	FILE *pf = fopen(file, "r");
	if (pf == 0)
		return false;
	fclose(pf);
	return true;
}

static FILE *cfPtr = 0;

int main()
{
	
	//对文件是否存在分情况处理
	if (!fileExist(FILE_PATH))
	{
		cfPtr = fopen(FILE_PATH, "w+");
	}
	else
	{
		cfPtr = fopen(FILE_PATH, "r+");
	}

	if (cfPtr == 0)
	{
		perror("create file:");
		return -1;
	}

	initialize(cfPtr);

	int choice;
	while ((choice = enterChoice()) != 5)
	{

		switch (choice)
		{
		case 1:
			textFile(cfPtr);
			break;
		case 2:
			updateRecord(cfPtr);
			break;
		case 3:
			newRecord(cfPtr);
			break;
		case 4:
			deleteRecord(cfPtr);
			break;
		}
	}

	fclose(cfPtr);


	return 0;
}

void initialize(FILE *file)
{
	memset(s_clients, 0, MAX_ACCOUNT_NUM * sizeof(ClientData));
	int count = 0;
	while (!feof(file) && count < MAX_ACCOUNT_NUM)
	{
		size_t ret = fread(&s_clients[count], sizeof(ClientData), 1, file);
		if (ret != 1)
		{
			break;
		}
		count++;
	}
}

int recordIndex(int account)
{
	for (int i = 0; i < MAX_ACCOUNT_NUM; i++)
	{
		if (s_clients[i].acctNum == account)
		{
			return i;
		}
	}
	return  -1;
}

void textFile(FILE *readPtr)
{
	FILE *writePtr = 0;
	ClientData client = { 0, "", "", 0.0 };

	if ((writePtr = fopen("accounts.txt", "w")) == NULL)
	{
		printf("File could not be opened.\n");
	}
	else
	{
		rewind(readPtr);
		fprintf(writePtr, "%-6s%-16s%-11s%10s\n",
			"Acct", "Last Name", "First Name", "Balance");

		while (!feof(readPtr))
		{
			size_t ret = fread(&client, sizeof(ClientData), 1,
				readPtr);
			if (ret != 1)
			{
				break;
			}

			if (client.acctNum != INVALID_ACCOUNT_NO)
				fprintf(writePtr, "%-6d%-16s%-11s%10.2f\n",
					client.acctNum, client.lastName,
					client.firstName, client.balance);
		}

		fclose(writePtr);
	}

}

void updateRecord(FILE *fPtr)
{
	int account;

	printf("Enter account to update ( 1 - 100 ): ");
	scanf("%d", &account);

	int index = recordIndex(account);
	if(-1 == index )
	{
		printf("Acount #%d has no information.\n", account);
		return;
	}

	ClientData data = s_clients[index];

	printf("%-6d%-16s%-11s%10.2f\n\n",
		data.acctNum, data.lastName,
		data.firstName, data.balance);
	printf("Enter charge ( + ) or payment ( - ): ");
	double transaction;
	scanf("%lf", &transaction);
	data.balance += transaction;
	printf("%-6d%-16s%-11s%10.2f\n",
		data.acctNum, data.lastName,
		data.firstName, data.balance);

	updateData(UPDATE, &data);	
}

void deleteRecord(FILE *fPtr)
{	
	int accountNum;

	printf("Enter account number to "
		"delete ( 1 - 100 ): ");
	scanf("%d", &accountNum);

	ClientData 	blankClient = { INVALID_ACCOUNT_NO, "", "", 0 };
	blankClient.acctNum = accountNum;

	updateData(DELETE, &blankClient);	
	
}

void newRecord(FILE *fPtr)
{
	ClientData client = { 0, "", "", 0.0 };
	int accountNum;
	printf("Enter new account number ( 1 - 100 ): ");
	scanf("%d", &accountNum);
	//找到该记录在列表中的索引
	int index = recordIndex(accountNum);
	if (-1 != index)//如果该记录已经存在
	{
		printf("Account #%d already contains information.\n",
			client.acctNum);
		return;
	}
	printf("Enter lastname, firstname, balance\n? ");
	scanf("%s%s%lf", &client.lastName, &client.firstName,
		&client.balance);
	client.acctNum = accountNum;

	updateData(INSERT, &client);	
}

int updateData(OperatorType type, ClientData * data)
{
	int index = recordIndex(type == INSERT ? INVALID_ACCOUNT_NO:data->acctNum);
	if (-1 == index)
	{
		printf("Account %d does not valid.\n", data->acctNum);
		return -1;
	}	

	switch (type)
	{
	case DELETE:
	{			
		//更新文件
		fseek(cfPtr, index * sizeof(ClientData), SEEK_SET);
		data->acctNum = INVALID_ACCOUNT_NO;
		fwrite(data,
			sizeof(ClientData), 1, cfPtr);
		//更新内存数据
		s_clients[index].acctNum = INVALID_ACCOUNT_NO;
	}
		break;
	case UPDATE:
	{		
		//更新数据
		s_clients[index].balance = data->balance;//更新数据缓冲
		fseek(cfPtr,
			index * sizeof(ClientData),
			SEEK_SET);
		fwrite(&s_clients[index], sizeof(ClientData), 1,
			cfPtr);//更新文件

	}
	break;
	case INSERT:
	{
		//更新数据记录文件
		fseek(cfPtr, index * sizeof(ClientData), SEEK_SET);
		fwrite(data, sizeof(ClientData), 1, cfPtr);
		//更新缓冲区数据	
		s_clients[index] = *data;
	}
	break;
	default:
		break;
	}

	return 0;
}

int enterChoice(void)
{
	int menuChoice;

	printf("\nEnter your choice\n"
		"1 - store a formatted text file of acounts called\n"
		"    \"accounts.txt\" for printing\n"
		"2 - update an account\n"
		"3 - add a new account\n"
		"4 - delete an account\n"
		"5 - end program\n? ");
	scanf("%d", &menuChoice);
	return menuChoice;
}



