#include <stdio.h>
#include <string.h>
#include"HashTableAPI.h"

//User defined hashfunction
int hashFunction(size_t tableSize, int key)
{
	int index = 0;

	index = key  % tableSize;
	return index;
}

//User defined printTable
void printTable(HTable *hashTable)
{
	int i;
	int empty = 0;
	int notEmpty = 1;
	int emptyOrNot = empty;

	if(hashTable->table == NULL)
	{
		printf("The table is NULL\n");
		return;
	}
	for(i = 0; i < hashTable->size; i++)
	{
    Node *head = hashTable->table[i];
    Node *tempNode = head;
    while(tempNode != NULL)
		{
			emptyOrNot = notEmpty;
      printf("Hash :%4d | Key :%4d | Data : ", hashTable->hashFunction(hashTable->size, tempNode->key), tempNode->key);
      hashTable->printData(tempNode->data);
      tempNode = tempNode->next;
    }
  }

	if(emptyOrNot == empty)
	{
		printf("The table is empty\n");
	}
}

//User defined print
void print(void *toBePrinted)
{
  int number;

  number = *((int *) toBePrinted);
  printf("%d\n", number);
}

//User defined delete
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
	int * ptr5 = malloc(sizeof(int));
	int * ptr6 = malloc(sizeof(int));
	int * ptr7 = malloc(sizeof(int));

	*ptr1 = 35;
	*ptr2 = 32;
	*ptr3 = 80;
	*ptr4 = 11;
	*ptr5 = 67;
	*ptr6 = 97;
	*ptr7 = 89;

  printf("*** Test #1: createTable ***\n");
  printf("Expected:\nThe table is empty\n");
	printf("HTable is NOT null\n\n");
  HTable *newHTable = createTable(109, hashFunction, delete, print);
	printf("Received:\n");
	printTable(newHTable);
	printf("%s\n", newHTable ? "HTable is NOT null" : "HTable is NULL");
	printf("%s", newHTable ? "   ***PASS***   \n\n" : "   ***FAILED***   \n\n");

	printf("*** Test #2: createNode ***\n");
  printf("Expected:\n");
	printf("Node is NOT null\n\n");
  Node *newNode = createNode(62, ptr7);
	printf("Received:\n");
	printf("%s\n", newNode ? "Node is NOT null" : "Node is NULL");
	printf("%s", newNode ? "   ***PASS***   \n\n" : "   ***FAILED***   \n\n");

  printf("*** Test #3: insertData ***\n");
	printf("Test 3.1 [Inserting with different hashes]\n");
	printf("Expected:\nHash :   5 | Key : 114 | Data : 35\nHash :  12 | Key :3500 | Data : 32\nHash : 104 | Key : 213 | Data : 11\n");
  insertData(newHTable, 114, ptr1);
	insertData(newHTable, 3500, ptr2);
	insertData(newHTable, 213, ptr4);
	printf("Received:\n");
	printTable(newHTable);

	printf("\nTest 3.2 [Inserting at the same hash]\n");
	printf("Expected:\nHash :   5 | Key : 114 | Data : 35\nHash :   5 | Key :   5 | Data : 80\nHash :   5 | Key : 223 | Data : 67\nHash :   5 | Key : 332 | Data : 97\nHash :  12 | Key :3500 | Data : 32\nHash : 104 | Key : 213 | Data : 11\n");
	insertData(newHTable, 5, ptr3);
	insertData(newHTable, 223, ptr5);
	insertData(newHTable, 332, ptr6);
  printf("Received:\n");
	printTable(newHTable);
  printf("   ***PASS***   \n\n");

	printf("*** Test #4: removeData ***\n");
	printf("Test 4.1 [Remove at a hash w/ single node]\n");
	printf("Expected:\nHash :   5 | Key : 114 | Data : 35\nHash :   5 | Key :   5 | Data : 80\nHash :   5 | Key : 223 | Data : 67\nHash :   5 | Key : 332 | Data : 97\nHash : 104 | Key : 213 | Data : 11\n");
	removeData(newHTable, 3500);
	printf("Received:\n");
	printTable(newHTable);

	printf("\nTest 4.2 [Removing the first key in hash w/ multiple key]\n");
	printf("Expected:\nHash :   5 | Key :   5 | Data : 80\nHash :   5 | Key : 223 | Data : 67\nHash :   5 | Key : 332 | Data : 97\nHash : 104 | Key : 213 | Data : 11\n");
	removeData(newHTable, 114);
	printf("Received:\n");
	printTable(newHTable);

	printf("\nTest 4.3 [Removing a key in the middle of hash w/ multiple keys]\n");
	printf("Expected:\nHash :   5 | Key :   5 | Data : 80\nHash :   5 | Key : 332 | Data : 97\nHash : 104 | Key : 213 | Data : 11\n");
	removeData(newHTable, 223);
	printf("Received:\n");
	printTable(newHTable);

	printf("\nTest 4.4 [Removing a key at the end of hash w/ multiple keys]\n");
	printf("Expected:\nHash :   5 | Key :   5 | Data : 80\nHash : 104 | Key : 213 | Data : 11\n");
	removeData(newHTable, 332);
	printf("Received:\n");
	printTable(newHTable);
	printf("   ***PASS***   \n\n");

	printf("*** Test #5: lookupData ***\n");
	printf("Expected: 11\n");
	Node * temp = lookupData(newHTable, 213);
	printf("Received: ");
	newHTable->printData(temp);
	printf("   ***PASS***   \n\n");

	printf("*** Test #6: destroyTable ***\n");
	printf("Expected:\nTable is NULL\n");
	destroyTable(newHTable);
	newHTable = NULL;
	printf("Received:\n");
	printf("%s\n", newHTable != NULL ? "Table is NOT null" : "Table is NULL");
	printf("%s", newHTable != NULL ? "   ***FAILED***   \n\n" : "   ***PASS***   \n\n");

	free(ptr7);
	free(newNode);
  return 0;
}
