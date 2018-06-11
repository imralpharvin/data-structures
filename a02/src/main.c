#include <stdio.h>

#include"HashTableAPI.h"

int hashFunction(size_t tableSize, int key) {

	int index = 0;

	index = key  % tableSize;
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
        		printf("Hash :%d | Key :%d | Data : ", hashTable->hashFunction(hashTable->size, cur->key), cur->key);
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

  printf("Would you like to create a new account(N) or sign in(S)? \n");
  scanf("%c", &intro);

  HTable * newUser = createTable(1, hashFunction, print, delete);

  printf("What's your username? \n");
  scanf("%s", userName);
  printf("%s", userName);

  printf("Enter new password \n");
  scanf("%s", password);
  printf("%s", password);

  insertData(newUser, userName, password);
    return 0;
}
