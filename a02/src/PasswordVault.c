#include <stdio.h>
#include <string.h>
#include "HashTableAPI.h"
#include "PasswordVault.h"


void createUser (User newUser)
{

	FILE *newFile;
	char filename[64];
	char pathname[64] = "bin/";

	strcpy(filename, newUser.username);
	strcat(pathname, filename);
	strcat(pathname, ".bin");
	newFile = fopen(pathname,"wb+");

	fwrite(&newUser , sizeof(User), 1 ,newFile);

	fclose(newFile);

	printf("\n> [New account successfully]\n\n");

}

void loadFile(User theUser, HTable * passVault)
{
  FILE *userFile;
	char filename[64];
	char pathname[64] = "bin/";
	int fileSize;
	int numSystems;

	strcpy(filename, theUser.username);
	strcat(pathname, filename);
	strcat(pathname, ".bin");
	userFile = fopen(pathname,"rb+");

	User * tempArray = NULL;

	fseek(userFile, 0, SEEK_END);
	fileSize = ftell(userFile);
	numSystems = fileSize/sizeof(User);
	tempArray = (User *) calloc(numSystems, sizeof(User));
	fseek(userFile, 0, SEEK_SET);
	fread(tempArray, sizeof(User), numSystems ,userFile);

  int i;
	 for(i = 0; i < numSystems; i++)
	 {
		 printf("Load file: %s:%s",tempArray[i].username,tempArray[i].password);
		 insertData(passVault,tempArray[i].username, tempArray[i].password);

	 }
	/* free(tempArray);*/
	 fclose(userFile);
	 printVault(theUser,passVault);

}

void loadTable(User theUser, HTable * passVault)
{
  FILE *userFile;
	char filename[64];
	char pathname[64] = "bin/";

	strcpy(filename, theUser.username);
	strcat(pathname, filename);
	strcat(pathname, ".bin");
	userFile = fopen(pathname,"wb");

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

void signin(User theUser, HTable * passVault)
{

	FILE *userFile;
	char filename[64];
	char pathname[64] = "bin/";
	int fileSize;
	int numSystems;

	strcpy(filename, theUser.username);
	strcat(pathname, filename);
	strcat(pathname, ".bin");

	userFile = fopen(pathname,"rb+");

	fseek(userFile, 0, SEEK_END);
	fileSize = ftell(userFile);
	numSystems = fileSize/sizeof(User);

		User * tempArray = (User *) calloc(numSystems, sizeof(User));

	fseek(userFile, 0, SEEK_SET);
	fread(tempArray, sizeof(User), numSystems ,userFile);


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
				scanf("%63s", theUser.password);

		 }
		 }

		}

	 for(i = 0; i < numSystems; i++)
	 {
		 insertData(passVault,tempArray[i].username, tempArray[i].password);
	 }
	 printVault(theUser,passVault);
	 
	 fclose(userFile);

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
