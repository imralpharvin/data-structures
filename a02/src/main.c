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
	char option;

	HTable * passVault = createVault(109, hashFunction, delete, print);

  printf("(N) Create a new account\n(S) Sign in? \n");
  scanf("%c", &intro);

	User theUser;
	switch(intro)
	{
		/*Ask for username and password*/
		case'N':
		printf("Username: ");
		scanf("%s", theUser.username);
		printf("Password: ");
		scanf("%s", theUser.password);
		createUser(theUser);
		loadFile(theUser,passVault);
		break;

		case'S':
		printf("Username: ");
		scanf("%s", theUser.username);
		printf("Password: ");
		scanf("%s", theUser.password);
		signin(theUser, passVault);
		printTable(passVault);

		break;
	}

	scanf("%c", &option);


	fflush(stdin);
	printf("Menu \n");
	printf("(A) Add a system and password \n");
	printf("(C) Change a password \n");
	printf("(G) Get a password \n");
	printf("(R) Remove a password \n\n");
	printf("(S) User settings \n");
	scanf("%c", &option);


	switch(option)
	{
		case 'A':
		printf("What's the system? \n");
		User newSystem;
		scanf("%s", newSystem.username);
		printf("Enter the system password \n");
		scanf("%s", newSystem.password);

		insertData(passVault, newSystem.username, newSystem.password);
		FILE * fptr;
		char filename[64];
		char pathname[64] = "bin/";

		strcpy(filename, theUser.username);
		strcat(pathname, filename);
		strcat(pathname, ".bin");
		fptr = fopen(pathname,"rb+");
		fseek(fptr, 0, SEEK_END);

		fwrite(&newSystem, sizeof(User), 1, fptr);

		fclose(fptr);
		break;

		case 'C':
		printf("What's the system? \n");
		User changeSystem;
		scanf("%s", changeSystem.username);
		printf("Enter new system password \n");
		scanf("%s", changeSystem.password);

		changeData(passVault, changeSystem.username, changeSystem.password);
		loadTable(theUser, passVault);

		case 'G':
		printf("What's the system? \n");
		User getSystem;
		scanf("%s", getSystem.username);
		strcpy(getSystem.password, lookupData(passVault, getSystem.username));
		printf("Password is: %s\n", getSystem.password);

		case 'R':
		printf("What's the system? \n");
		User removeSystem;
		scanf("%s", removeSystem.username);
		removeData(passVault, removeSystem.username);
		printTable(passVault);
		loadTable(theUser, passVault);

		break;

	}

	printf("End\n");
	printTable(passVault);
  return 0;
}
