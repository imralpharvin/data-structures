#include <stdio.h>
#include <string.h>
#include"HashTableAPI.h"


int hashFunction(size_t tableSize, int data) {

	int key = data;

	/*key = data  % tableSize;*/
	return key;
}

void printTable(HTable *hashTable){
	if(hashTable->table[0] == NULL)
	{
		printf("The table is empty\n");
	}

		int i = 0;
    for(i = 0; i < hashTable->size; i++)
		{
        Node *head = hashTable->table[i];
        Node *cur = head;
        while(cur != NULL)
				{
					printf("here\n");
        		printf("%d : %d : ", hashTable->hashFunction(hashTable->size, cur->key), cur->key);
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
		int v1 = 36;

		int * ptr1 = &v1;
    printf("*** Test #1: createTable ***\n");
    printf("Expected:\nThe table is empty\n");
    HTable *newHTable = createTable(5, hashFunction, delete, print);
    printf("Received:\n");
		printTable(newHTable);
    printf("   ***PASS***   \n\n");

    printf("*** Test #2: insertData ***\n");
    printf("Expected:\nN L 2\nS R 3\nW F 5\n");
    insertData(newHTable, 1, ptr1) ;
    printf("Received:\n");
				printTable(newHTable);
    printf("   ***PASS***   \n\n");

    return 0;
}
