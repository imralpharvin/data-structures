#include <stdio.h>
#include <string.h>
#include "PasswordVault.h"

User createUser (HTable * passVault)
{
	FILE *newFile;
	User newUser;

	//Prompt User to put username and password
	printf("> [Username]: ");
	fgets(newUser.username, 100, stdin);
	newUser.username[strlen(newUser.username) - 1] = '\0';
	printf("> [Password]: ");
	fgets(newUser.password, 100, stdin);
	newUser.password[strlen(newUser.password) - 1] = '\0';

	//Create file and add the user
	newFile = fopen(createPathname(newUser),"wb+");
	fwrite(&newUser , sizeof(User), 1 ,newFile);
	fclose(newFile);

	//Load the file to the hashtable
	loadFile(newUser,passVault);

	printf("\n> [New account created successfully]\n");
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
				printf("> Wrong Password: Try again \n");
				printf("> [Username]: %s\n", theUser.username);
				printf("> [Password]: ");
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

HTable *createVault(size_t size, int (*hashFunction)(size_t tableSize, char key[]),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{
	//Create vault
  HTable * newVault = createTable(size, hashFunction, destroyData, printData);

  return newVault;
}

void addPassword(User * theUser, HTable * passVault )
{
	//Insert password
	insertData(passVault, theUser->username, theUser->password);
}

void changePassword(User * theUser, HTable * passVault )
{
	//change password
	changeData(passVault, theUser->username, theUser->password);
}

char * getPassword(User * theUser, HTable * passVault )
{
	//return password
	return lookupData(passVault, theUser->username);
}

void removePassword(User * theUser, HTable * passVault )
{
	//remove password
	removeData(passVault, theUser->username);
}

int checkSystem(User * theUser, HTable * passVault )
{
	//Check if user in the hashtable
	return checkKey(passVault, theUser->username);
}

void printVault(User theUser, HTable * passVault)
{
	printf("----------------\n");
	printf("[Your Accounts]:\n");
	//Print keys
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
		total += temp; //Sums the ASCII value of each letter

	}
	index = total  % tableSize; //Divide total by size of table

	return index;
}

void printPassword(void *toBePrinted)
{
  char * number;
	//Print password
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

	return pathname;
}

void loadFile(User theUser, HTable * passVault)
{
  FILE *userFile;
	int fileSize;
	int numSystems;
	User * tempArray = NULL;
	//Open file
	userFile = fopen(createPathname(theUser),"rb+");
	fseek(userFile, 0, SEEK_END);
	fileSize = ftell(userFile);
	numSystems = fileSize/sizeof(User);
	fseek(userFile, 0, SEEK_SET);

	//Read file and put them in an array
	tempArray = (User *) calloc(numSystems, sizeof(User));
	fread(tempArray, sizeof(User), numSystems ,userFile);

	//Insert the contents of array to the hashtable
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
	//Open file
	userFile = fopen(createPathname(theUser),"wb");

	//Write the contents of the hashtable to the file
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
