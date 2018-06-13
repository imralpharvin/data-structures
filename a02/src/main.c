#include <stdio.h>
#include <string.h>
#include "HashTableAPI.h"
#include "PasswordVault.h"

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
  char * number;

  number = ((char *) toBePrinted);
  printf("%s\n", number);
}

void delete(void *toBeDeleted)
{
  free(toBeDeleted);
}

/*int main()
{
	HTable * passVault = createVault(113, hashFunction, delete, print);

	createUser(passVault);

	User newUser;
  printf("Enter username: \n");
  fgets(newUser.username, 64, stdin);
  newUser.username[strlen(newUser.username)-1] = '\0';

  printf("Enter password: \n");
  fgets(newUser.password, 64, stdin);
  newUser.password[strlen(newUser.password)-1] = '\0';
char username[64];
char password[64];
  printf("Enter username: \n");
  fgets(username, 64, stdin);
  username[strlen(username)-1] = '\0';
  printf("Enter password: \n");
  fgets(password, 64, stdin);
  password[strlen(password)-1] = '\0';
  insertData(passVault, newUser.username, newUser.password);
  insertData(passVault, username, password);

	printTable(passVault);
	createUser(passVault);
	printTable(passVault);

	return 0;
}*/
int main ()
{

  char intro;
  /*char userName[64];
  char password[64];*/
	char option;

	HTable * passVault = createVault(109, hashFunction, delete, print);
	User newUser;

  printf("(N) Create a new account\n(S) Sign in? \n");
  scanf("%c", &intro);


	switch(intro)
	{
		/*Ask for username and password*/
		case'N':

		printf("Enter username: \n");
	  scanf("%s", newUser.username);
	  printf("Enter password: \n");
	  scanf("%s", newUser.password);
		createFile(newUser);
	  insertData(passVault, newUser.username, newUser.password);
		break;

		case'S':
		signin(passVault);
		printf("After signing in:\n" );
		printTable(passVault);


		break;
	}


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
		User newSystem;
		scanf("%s", newSystem.username);
		printf("Enter the system password \n");
		scanf("%s", newSystem.password);
		printTable(passVault);

		insertData(passVault, newSystem.username, newSystem.password);
		FILE * fptr;
		fptr = fopen("bin/Ralph.bin","wb");
		printf("after\n");
		printTable(passVault);

		int i;
		for(i = 0; i < passVault->size; i++)
		{
			Node * temp = passVault->table[i];
			while(temp != NULL)
			{
				Node *tempDelete = temp;
				User *tempUser = malloc(sizeof(User));
				printf("add: %s : %s\n", tempDelete->key, (char*)tempDelete->data);
				strcpy(tempUser->username ,tempDelete->key);
				strcpy(tempUser->password , tempDelete->data);

				fwrite(tempUser, sizeof(User), 1, fptr);
				temp = temp->next;
			}
		}


		fclose(fptr);
		break;

		case 'B':
		printf("What's the system? \n");

		FILE * fptr2;
		fptr2 = fopen("bin/ralph3.bin","rb");
		HTable * vault2 = createVault(109, hashFunction, delete, print);;

		fread(vault2, sizeof(HTable), 1, fptr2);
		printTable(vault2);
		fclose(fptr2);
		break;

	}

	printTable(passVault);
  return 0;
}
