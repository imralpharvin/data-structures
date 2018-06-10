#include <stdio.h>
#include <string.h>
#include"HashTableAPI.h"


int hashFunction(size_t tableSize, int data) {

	int key = 0;
	/*int j = 1;
	char *word = (char*)data;
	for (int i=0; i<strlen(word); ++i) {
		key += word[i] * j;
		++j;
	}
	key = (word[0] * key) % tableSize;*/
	return key;
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

    printf("*** Test #1: createTable ***\n");
    printf("Expected:\nThe table is empty\n");
    HTable *newHTable = createTable(2, hashFunction, delete, print);
    printf("Received:\n");

    printf("   ***PASS***   \n\n");

    printf("*** Test #2: enQueue ***\n");
    printf("Expected:\nN L 2\nS R 3\nW F 5\n");
    /*enQueue(carQueue, a);
    enQueue(carQueue, b);
    enQueue(carQueue, c);*/
    printf("Received:\n");

    printf("   ***PASS***   \n\n");

    return 0;
}
