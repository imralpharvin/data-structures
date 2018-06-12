#include <stdio.h>
#include <string.h>
#include"HashTableAPI.h"
#include"PasswordVault.h"


int hashFunction(size_t tableSize, char key[]) {

	int index = 0;
	int letter;
	int i;
	int total = 0;

	letter = strlen(key);
	for(i = 0; i < letter; i++)
	{
		int temp = key[i] - '0';
		total += temp;

	}
	index = total  % tableSize;
	return index;
}

void printTable(HTable *hashTable){

		int i = 0;
    for(i = 0; i < hashTable->size; i++)
		{

        Node *head = hashTable->table[i];
        Node *cur = head;
        while(cur != NULL)
				{
        		printf("Hash :%d | Key :%s | Data : ", hashTable->hashFunction(hashTable->size, cur->key), cur->key);
            hashTable->printData(cur->data);
            cur = cur->next;
        }
    }
}
void print(void *toBePrinted)
{
  int number;

  number = *((int *) toBePrinted);
  printf("%d\n", number);
}

void delete(void *toBeDeleted)
{
  free(toBeDeleted);
}


int main ()
{

  char intro;
  char userName[15];
  char password[15];
	char option;
	FILE *userPtr;

  printf("Would you like to create a new account(N) or sign in(S)? \n");
  scanf("%c", &intro);

	HTable * newFile = createTable(109, hashFunction, delete, print);

  printf("What's your username? \n");
  scanf("%s", userName);


  printf("Enter new password \n");
  scanf("%s", password);

  User * newUser = createUser(userName, password);

/*	printTable(newUser);*/

	scanf("%c", &option);

	printf("What would you like to do? \n");
	printf("Add a system and password (A) \n");
	printf("Change a password (C) \n");
	printf("Get a password (G) \n");
	printf("Remove a password (R) \n");
	scanf("%c", &option);

	switch(option)
	{
		case 'A':
		printf("What's the system? \n");
		scanf("%s", userName);

		printf("Enter the system password \n");
		scanf("%s", password);
		insertData(newFile, userName, password);

	}

	printTable(newFile);
  return 0;
}
