#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdbool>

static const int MAX_NUM = 100;

typedef struct _ClientData
{
	int acctNum;
	char lastName[15];
	char firstName[10];
	double balance;
}ClientData;

static ClientData s_clients[MAX_NUM] = { 0 };

int enterChoice(void);
void textFile(FILE *);
void updateRecord(FILE *);
void newRecord(FILE *);
void deleteRecord(FILE *);

void initialize(FILE *);

int  recordIndex(int);

int main()
{
	FILE *cfPtr = 0;
	//对文件是否存在分情况处理
	if ((cfPtr = fopen("credit.dat", "r")) == NULL)
	{
		printf("File could not be opened.\n");
		cfPtr = fopen("credit.dat", "w+");
		if (cfPtr == 0)
		{
			perror("create file:");
			return -1;
		}
	}
	else
	{
		fclose(cfPtr);
		cfPtr = fopen("credit.dat", "r+");
		if (cfPtr == 0)
		{
			perror("create file:");
			return -1;
		}
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
	int count = 0;
	while (!feof(file) && count < MAX_NUM)
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
	for (int i = 0; i < MAX_NUM; i++)
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

			if (client.acctNum != 0)
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
	double transaction;

	printf("Enter account to update ( 1 - 100 ): ");
	scanf("%d", &account);

	int index = recordIndex(account);
	if(-1 == index )
	{
		printf("Acount #%d has no information.\n", account);
		return;
	}

	printf("%-6d%-16s%-11s%10.2f\n\n",
		s_clients[index].acctNum, s_clients[index].lastName,
		s_clients[index].firstName, s_clients[index].balance);
	printf("Enter charge ( + ) or payment ( - ): ");
	scanf("%lf", &transaction);
	s_clients[index].balance += transaction;
	printf("%-6d%-16s%-11s%10.2f\n",
		s_clients[index].acctNum, s_clients[index].lastName,
		s_clients[index].firstName, s_clients[index].balance);

	fseek(fPtr,
		index * sizeof(ClientData),
		SEEK_SET);
	fwrite(&s_clients[index], sizeof(ClientData), 1,
		fPtr);
}

void deleteRecord(FILE *fPtr)
{
	ClientData client,
		blankClient = { 0, "", "", 0 };
	int accountNum;

	printf("Enter account number to "
		"delete ( 1 - 100 ): ");
	scanf("%d", &accountNum);

	int index = recordIndex(accountNum);

	if (-1 == index)
	{
		printf("Account %d does not exist.\n", accountNum);
		return;
	}

	fseek(fPtr, index * sizeof(ClientData), SEEK_SET);
	fwrite(&blankClient,
		sizeof(ClientData), 1, fPtr);
	//更新内存数据
	s_clients[index].acctNum = 0;
	
}

void newRecord(FILE *fPtr)
{
	ClientData client = { 0, "", "", 0.0 };
	int accountNum;
	printf("Enter new account number ( 1 - 100 ): ");
	scanf("%d", &accountNum);
	int index = recordIndex(accountNum);
	if (-1 != index)
	{
		printf("Account #%d already contains information.\n",
			client.acctNum);
		return;
	}

	printf("Enter lastname, firstname, balance\n? ");
	scanf("%s%s%lf", &client.lastName, &client.firstName,
		&client.balance);
	client.acctNum = accountNum;
	fseek(fPtr, 0, SEEK_END);
	fwrite(&client,
		sizeof(ClientData), 1, fPtr);

	//更新内存数据
	index = 0; 
	while (s_clients[index].acctNum != 0)
	{
		index++;
	}
	s_clients[index] = client;
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



