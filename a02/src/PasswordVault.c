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
  printf("%s\n", pathname);
	newFile = fopen(pathname,"wb+");

	fwrite(&newUser , sizeof(User), 1 ,newFile);

	fclose(newFile);

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
  printf("No: %d\n", numSystems);
	tempArray = (User *) calloc(numSystems, sizeof(User));

	fseek(userFile, 0, SEEK_SET);
	fread(tempArray, sizeof(User), numSystems ,userFile);

  int i;
	 for(i = 0; i < numSystems; i++)
	 {
		 insertData(passVault,tempArray[i].username, tempArray[i].password);
	 }
	 fclose(userFile);

}

void loadTable(User theUser, HTable * passVault)
{
  FILE *userFile;
	char filename[64];
	char pathname[64] = "bin/";
	int fileSize;
	int numSystems;

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
      printf("%s : %s\n", tempUser.username, tempUser.password);
      fwrite(&tempUser, sizeof(User),1,userFile);
      temp = temp->next;

    }
  }
  fclose(userFile);

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
		 if(strcmp(tempArray[i].username, theUser.username) == 0)
		 {
			 while(strcmp(tempArray[i].password, theUser.password) != 0)
			 {
			 if(strcmp(tempArray[i].password, theUser.password) == 0)
			 {
				 printf("\n***You Successfully Logged In!***\n\n");
				 break;
			 }
				 printf("\nXX Wrong Password: Try again XX\n\n");
				 printf("Username: %s\n", theUser.username);
			 	printf("Password: ");
			 	scanf("%s", theUser.password);

		 }
		 }

		}

	 for(i = 0; i < numSystems; i++)
	 {
		 insertData(passVault,tempArray[i].username, tempArray[i].password);
	 }
	 fclose(userFile);

}


HTable *createVault(size_t size, int (*hashFunction)(size_t tableSize, char key[]),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{
  HTable * newVault = createTable(size, hashFunction, destroyData, printData);

  return newVault;
}
