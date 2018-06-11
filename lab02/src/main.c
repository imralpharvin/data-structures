#include <stdio.h>
#include <string.h>
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

		int * ptr1 = malloc(sizeof(int));
		int * ptr2 = malloc(sizeof(int));
		int * ptr3 = malloc(sizeof(int));
		int * ptr4 = malloc(sizeof(int));


		*ptr1 = 35;
		*ptr2 = 32;
		*ptr3 = 80;
		*ptr4 = 11;

    printf("*** Test #1: createTable ***\n");
    printf("Expected:\nThe table is empty\n");
    HTable *newHTable = createTable(109, hashFunction, delete, print);
    printf("Received:\n");
		printTable(newHTable);
    printf("   ***PASS***   \n\n");

    printf("*** Test #2: insertData ***\n");
    printf("Expected:\n");
    insertData(newHTable, 5, ptr1);
		insertData(newHTable, 3500, ptr2);
		insertData(newHTable, 213, ptr4);
		insertData(newHTable, 114, ptr3);



    printf("Received:\n");
		printTable(newHTable);
    printf("   ***PASS***   \n\n");


		printf("*** Test #3: removeData ***\n");
		printf("Expected:\n");
		removeData(newHTable, 3500);
		removeData(newHTable, 114);
		removeData(newHTable, 5);


		printf("Received:\n");
		printTable(newHTable);
		printf("   ***PASS***   \n\n");

		printf("*** Test #4: lookupData ***\n");
		printf("Expected:\n");
		Node * temp = lookupData(newHTable, 213);
		printf("Received:\n");
		newHTable->printData(temp);
		printf("   ***PASS***   \n\n");

		printf("*** Test #5: destroyTable ***\n");
		printf("Expected:\n");
		destroyTable(newHTable);
		printf("Received:\n");
		printf("   ***PASS***   \n\n");
    return 0;

}
