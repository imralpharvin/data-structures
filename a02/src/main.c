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

int main ()
{

  char intro;
	char option;

	HTable * passVault = createVault(109, hashFunction, delete, print);

	printf("\n*********************** PASSWORD VAULT ***********************\n");
  printf("\n(N) Create a new account\n(S) Sign in?\n\n> ");
	scanf("%c", &intro);
	/*fgets(intro, 3, stdin);*/

	/*intro[strlen(intro)-1] = '\0';*/
/*printf("%s", intro);*/
	/*intro = getc(stdin);*/
	/*intro = getchar();*/
  /*scanf("%c", &intro);*/

	User theUser;
	switch(intro)
	{
		/*Ask for username and password*/
		case'N':
		printf("\n[Username]: ");
		/*fgets(theUser.username, 64, stdin);*/
		/*theUser.username[strlen(theUser.username)-1] = '\0';*/
		scanf("%63s", theUser.username);
		printf("[Password]: ");
		/*fgets(theUser.password, 64, stdin);*/
		/*	theUser.password[strlen(theUser.password)-1] = '\0';*/
		scanf("%63s", theUser.password);
		createUser(theUser);
		loadFile(theUser,passVault);
		break;

		case'S':
		printf("\n[Username]: ");
		/*fgets(theUser.username, 64, stdin);*/
		scanf("%63s", theUser.username);
		printf("[Password]: ");
		/*fgets(theUser.password, 64, stdin);*/
		scanf("%63s", theUser.password);
		signin(theUser, passVault);
		printf("\n> [Logged in successfully]\n\n");
		printTable(passVault);

		break;
	}

while(option != '2')
{

	printf("\n*********************** M E N U ***********************\n\n");
	printVault(theUser, passVault);
	printf("\n(A) Add a system and password \n");
	printf("(B) Change a password \n");
	printf("(C) Get a password \n");
	printf("(D) Remove a password \n\n");
	printf("(1) Change your password vault password \n");
	printf("(2) Logout\n\n> ");
	getchar();
	scanf("%c", &option);


	switch(option)
	{
		case 'A':
		printf("\n*********************** ADD NEW SYSTEM AND PASSWORD ***********************\n\n");
		printf("\n[Enter new system]: ");
		User newSystem;
		User * tempSystem = malloc(sizeof(User));
		/*getchar();*/

		scanf("%63s", newSystem.username);
		/*fgets(newSystem.username, 64, stdin);*/
		/*newSystem.username[strlen(newSystem.username)-1] = '\0';*/

		/*scanf("%s", );*/
		printf("[Enter system password]: ");

		/*fgets(newSystem.password, 64, stdin);*/
		/*newSystem.password[strlen(newSystem.password)-1] = '\0';*/
		scanf("%63s", newSystem.password);

		strcpy(tempSystem->username, newSystem.username);
		strcpy(tempSystem->password, newSystem.password);

		insertData(passVault, tempSystem->username, tempSystem->password);
		printVault(theUser, passVault);

		loadTable(theUser, passVault);
		printf("> [Password added successfully]\n");

		break;

		case 'B':
		printf("\n*********************** CHANGE A SYSTEM PASSWORD ***********************\n\n");
		printVault(theUser, passVault);
		printf("\n[Enter system]: ");
		User changeSystem;

		/*fgets(changeSystem.username, 64, stdin);*/
		scanf("%63s", changeSystem.username);
		printf("[Enter new system password]: ");
		/*fgets(changeSystem.password, 64, stdin);*/
		scanf("%63s", changeSystem.password);

		changeData(passVault, changeSystem.username, changeSystem.password);
		loadTable(theUser, passVault);
		printf("\n> [Password changed successfully]\n");
		break;

		case 'C':
		printf("\n*********************** GET A SYSTEM PASSWORD ***********************\n\n");
		printVault(theUser, passVault);
		printf("\n[Enter system]: ");
		User getSystem;
		/*fgets(getSystem.username, 64, stdin);*/
		scanf("%63s", getSystem.username);
		strcpy(getSystem.password, lookupData(passVault, getSystem.username));
		printf("[Your Password is]: %s\n", getSystem.password);
		break;

		case 'D':
		printf("\n*********************** REMOVE A SYSTEM PASSWORD ***********************\n\n");
		printVault(theUser, passVault);
		printf("\n[Enter system]: ");
		User removeSystem;
		/*fgets(removeSystem.username, 64, stdin);*/
		scanf("%63s", removeSystem.username);
		removeData(passVault, removeSystem.username);
		/*printTable(passVault);*/
		loadTable(theUser, passVault);
		printf("\n> [System and password removed successfully]\n");
		break;

		case '1':
		printf("\n*********************** CHANGE YOUR VAULT PASSWORD ***********************\n\n");
		printf("[Your username]: %s\n", theUser.username);
		printf("[Enter new vault password]: ");
		/*fgets(theUser.password, 64, stdin);*/
		scanf("%63s", theUser.password);

		changeData(passVault, theUser.username, theUser.password);
		loadTable(theUser, passVault);
		printf("> [Vault Password updated successfully]\n");
		break;

		case '2':
		printf("> [Logout successful]\n");
		printf("\n*********************** THANK YOU FOR USING PASSWORD VAULT ***********************\n\n");
		exit(-1);
		break;


	}

}
  return 0;
}
