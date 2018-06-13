#include <stdio.h>
#include <string.h>
#include "HashTableAPI.h"
#include "PasswordVault.h"

void createFile(User newUser)
{
  /*User newUser;
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

  printTable2(passVault);*/
  FILE *userFile;

  char filename[64];
  char pathname[64] = "bin/";
  char username[64];
  char password[64];

  strcpy(filename, newUser.username);
  strcat(pathname, filename);
  strcat(pathname, ".bin");
  printf("%s\n", pathname);
  userFile = fopen(pathname,"wb");

  printf("%s : %s\n", newUser.username, newUser.password);

  fwrite(&newUser , sizeof(User), 1 ,userFile);
  fclose(userFile);

  return;
}
void signin(HTable * passVault)
{
	User existingUser;

	printf("Username: ");
	scanf("%s", existingUser.username);
	printf("Password: ");
	scanf("%s", existingUser.password);

	FILE *userFile;
	char filename[64];
	char pathname[64] = "bin/";
	int fileSize;
	int numSystems;

	strcpy(filename, existingUser.username);
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
		 if(strcmp(tempArray[i].username, existingUser.username) == 0)
		 {
			 while(strcmp(tempArray[i].password, existingUser.password) != 0)
			 {
			 if(strcmp(tempArray[i].password, existingUser.password) == 0)
			 {
				 printf("\n***You Successfully Logged In!***\n\n");
				 break;
			 }
				 printf("XX Wrong Password: Try again XX\n");
				 printf("Username: %s\n", existingUser.username);
			 	printf("Password: ");
			 	scanf("%s", existingUser.password);

		 }
		 }

		}


	 for(i = 0; i < numSystems; i++)
	 {
		 insertData(passVault,tempArray[i].username, tempArray[i].password);
	 }
	 fclose(userFile);

}


User * openUser(char username[], char password[], HTable * passVault)
{
  FILE *userFile;
  char filename[64];
  char pathname[64] = "bin/";
  /*Filename to bin*/
  strcpy(filename, username);
  strcat(pathname, filename);
  strcat(pathname, ".bin");
  printf("%s\n", pathname);
  userFile = fopen(pathname,"rb+");

  User * temp = malloc(sizeof(User));

  while(!feof(userFile))
  {
    if(fread(temp, sizeof(User), 1 ,userFile) != 0)
    {
      printf("open user: %s and %s\n",temp->username, temp->password);
      insertData(passVault,temp->username, temp->password);
    }
  }
  fclose(userFile);

  return temp;
}

HTable *createVault(size_t size, int (*hashFunction)(size_t tableSize, char key[]),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{
  HTable * newVault = createTable(size, hashFunction, destroyData, printData);

  return newVault;
}
