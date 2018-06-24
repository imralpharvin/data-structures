#include <stdio.h>
#include <string.h>
#include "PasswordVault.h"

User createUser (HTable * passVault)
{
	FILE *newFile;
	User newUser;

	//Prompt User to put username and password
	printf("\n[Username]: ");
	fgets(newUser.username, 100, stdin);
	newUser.username[strlen(newUser.username) - 1] = '\0';
	printf("[Password]: ");
	fgets(newUser.password, 100, stdin);
	newUser.password[strlen(newUser.password) - 1] = '\0';

	//Create file and add the user
	newFile = fopen(createPathname(newUser),"wb+");
	fwrite(&newUser , sizeof(User), 1 ,newFile);
	fclose(newFile);

	//Load the file to the hashtable
	loadFile(newUser,passVault);

	printf("\n> [New account created successfully]\n\n");
	return newUser;
}

void signin(User theUser, HTable * passVault)
{
	FILE *userFile;
	int fileSize;
	int numSystems;

	//Open file
	userFile = fopen(createPathname(theUser),"rb+");
	fseek(userFile, 0, SEEK_END);
	fileSize = ftell(userFile);
	numSystems = fileSize/sizeof(User);
	fseek(userFile, 0, SEEK_SET);

	//Read file and put all of the users in a temp array
	User * tempArray = (User *) calloc(numSystems, sizeof(User));
	fread(tempArray, sizeof(User), numSystems ,userFile);

	//Check if password is correct, Prompts user again if incorrect
	int i;
	for(i = 0; i < numSystems; i++)
	{
		if(strcmp(tempArray[i].username, theUser.username) == 0)
		{
			while(strcmp(tempArray[i].password, theUser.password) != 0)
			{
				if(strcmp(tempArray[i].password, theUser.password) == 0)
				{
					break;
				}
				printf("\n> Wrong Password: Try again \n\n");
				printf("[Username]: %s\n", theUser.username);
				printf("[Password]: ");
				fgets(theUser.password, 100, stdin);
				theUser.password[strlen(theUser.password) - 1] = '\0';
	 		}
		}
	}

	//Load contents of array to the hashtable
	for(i = 0; i < numSystems; i++)
	{
		insertData(passVault,tempArray[i].username, tempArray[i].password);
	}
	printVault(theUser,passVault);

	fclose(userFile);
}

void loadFile(User theUser, HTable * passVault)
{
  FILE *userFile;
	int fileSize;
	int numSystems;
	User * tempArray = NULL;

	userFile = fopen(createPathname(theUser),"rb+");

	fseek(userFile, 0, SEEK_END);
	fileSize = ftell(userFile);
	numSystems = fileSize/sizeof(User);
	fseek(userFile, 0, SEEK_SET);

	tempArray = (User *) calloc(numSystems, sizeof(User));
	fread(tempArray, sizeof(User), numSystems ,userFile);

  int i;
	for(i = 0; i < numSystems; i++)
	{
		insertData(passVault,tempArray[i].username, tempArray[i].password);
	}
	fclose(userFile);
	printVault(theUser,passVault);
}

void loadTable(User theUser, HTable * passVault)
{
  FILE *userFile;

	userFile = fopen(createPathname(theUser),"wb");

  int i;
  for(i = 0; i < passVault->size; i++)
  {
    Node * temp = passVault->table[i];
    while(temp != NULL)
    {
      Node *tempDelete = temp;
      User tempUser;
      strcpy(tempUser.username , tempDelete->key);
      strcpy(tempUser.password , tempDelete->data);
      fwrite(&tempUser, sizeof(User),1,userFile);
      temp = temp->next;
    }
  }
  fclose(userFile);
	printVault(theUser,passVault);
}

void addPassword(User * theUser, HTable * passVault )
{
	insertData(passVault, theUser->username, theUser->password);

}

void changePassword(User * theUser, HTable * passVault )
{
	changeData(passVault, theUser->username, theUser->password);
}

char * getPassword(User * theUser, HTable * passVault )
{
	return lookupData(passVault, theUser->username);
}

void removePassword(User * theUser, HTable * passVault )
{
	removeData(passVault, theUser->username);
}

HTable *createVault(size_t size, int (*hashFunction)(size_t tableSize, char key[]),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{
  HTable * newVault = createTable(size, hashFunction, destroyData, printData);

  return newVault;
}

void printVault(User theUser, HTable * passVault)
{
	printf("----------------\n");
	printf("[Your Accounts]:\n");
	int i = 0;
	for(i = 0; i < passVault->size; i++)
	{
			Node *head = passVault->table[i];
			Node *cur = head;
			while(cur != NULL)
			{
				if(strcmp(cur->key , theUser.username) != 0)
				{
					printf("%s \n", cur->key);
				}
				cur = cur->next;
			}
	}
	printf("----------------\n");

}

int hashFunction(size_t tableSize, char key[])
{
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

void printTable(HTable *hashTable)
{
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

void printPassword(void *toBePrinted)
{
  char * number;

  number = ((char *) toBePrinted);
  printf("%s\n", number);
}

void deletePassword(void *toBeDeleted)
{
  return;
}

char * createPathname (User theUser)
{
	static char pathname[64];

	strcpy(pathname, "assets/");
	strcat(pathname, theUser.username);
	strcat(pathname, ".bin");

	printf("Path: %s\n", pathname);

	return pathname;
}
