#include <stdio.h>

#include "HashTableAPI.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, int key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{
    HTable * newHTable = malloc(sizeof(HTable));

    newHTable->destroyData = destroyData;
    newHTable->hashFunction = hashFunction;
    newHTable->printData = printData;
    newHTable->table = malloc(sizeof(Node*)*size);

    for (int i = 0; i < size; ++i)
    {
		newHTable->table[i] = malloc(sizeof(Node));
		newHTable->table[i] = NULL;
	}

	return newHTable;
}

Node *createNode(int key, void *data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->key = key;
    newNode->data = data;

    return newNode;
}
void destroyTable(HTable *hashTable)
{
    Node *tempNode;
	for (int i = 0; i < hashTable->size ; i++)
    {
		tempNode = hashTable->table[i];
		while (tempNode != NULL)
      {
			removeData(hashTable, i, temp->data);
			tempNode = tempNode->next;
		}
	}

    free(hashTable->table);
	free(hashTable);
}
void insertData(HTable *hashTable, int key, void *data)
{
    if(HTable != NULL)
    {
        Node *newNode = createNode(key, data);
        int index = hashTable->hashFunction(hashTable->size, key);

        if(hashTable->table[index] != NULL)
        {
          Node *temp = hashTable->table[key];
		      hashTable->table[key] = newNode;
		      hashTable->table[key]->next = temp;
        }

        else
        {
          hashTable->table[key] = newNode;
        }
    }
if (hashTable->table[key] == NULL) {

		hashTable->table[key] = newNode;

	}
}
void removeData(HTable *hashTable, int key)
{

}
void *lookupData(HTable *hashTable, int key)
{
 int loc = hashTable->hashFunction(hashTable->size, key);
}
