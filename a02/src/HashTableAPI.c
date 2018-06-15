#include <stdio.h>
#include <string.h>

#include "HashTableAPI.h"


HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, char key[]),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{
    HTable * newHTable = malloc(sizeof(HTable));

    newHTable->size = size;
    newHTable->destroyData = destroyData;
    newHTable->hashFunction = hashFunction;
    newHTable->printData = printData;
    newHTable->table = malloc(sizeof(Node*)*size);

    for (int i = 0; i < size; ++i)
    {
		  newHTable->table[i] = NULL;
	  }

	return newHTable;
}

Node *createNode(char key[], void *data)
{
    Node *newNode = malloc(sizeof(Node));

    newNode->next = NULL;
    newNode->key = key;
    newNode->data = data;


    return newNode;
}
/*
void destroyTable(HTable *hashTable)
{
  if(hashTable == NULL)
  {
    return;
  }
  int i;
  for(i = 0; i < hashTable->size; i++)
  {
    Node * temp = hashTable->table[i];
    while(temp != NULL)
    {
      Node *tempDelete = temp;
      temp = temp->next;
      free(tempDelete->data);
      free(tempDelete);
    }
  }

free(hashTable->table);
hashTable->table = NULL;
  free(hashTable);
}*/
void insertData(HTable *hashTable, char key[], void *data)
{

    if(hashTable != NULL)
    {

        Node *newNode = createNode(key, data);
        int index = hashTable->hashFunction(hashTable->size, key);



        if(hashTable->table[index] != NULL)
        {
          Node *temp = hashTable->table[index];
          while(temp != NULL)
          {
            if(temp->next != NULL)
            {
              temp = temp->next;
            }

            else
            {
              temp->next = newNode;
              break;
            }
        }
        }
        else
        {

          hashTable->table[index] = newNode;
        }
    }

}
void removeData(HTable *hashTable, char key[])
{
  if(hashTable != NULL)
{
    int index = hashTable->hashFunction(hashTable->size, key);

    if(hashTable->table[index] != NULL)
    {

        Node *temp = hashTable->table[index];
        Node *prev = NULL;
        while(strcmp(temp->key , key) != 0)
        {
          prev = temp;
          temp = temp->next;
        }
        if(strcmp(temp->key , key) == 0)
        {
          if(prev == NULL)
          {
            if(temp->next == NULL)
            {
              /*hashTable->destroyData(temp->data);*/
              hashTable->table[index] = NULL;
            }

            else
            {
              hashTable->table[index] = hashTable->table[index]->next;
              /*hashTable->destroyData(temp->data);*/
              hashTable->table[index]->next = temp->next;
              free(temp);
            }
          }
          else
          {
            prev->next = temp->next;
            /*hashTable->destroyData(temp->data);*/
          }
        }

    }
  }

  }


void *lookupData(HTable *hashTable, char key[])
{

  if(hashTable != NULL)
  {
      int index = hashTable->hashFunction(hashTable->size, key);

      if(hashTable->table[index] == NULL)
      {
        return NULL;
      }

      Node *temp = hashTable->table[index];
      while(temp != NULL)
      {
        if(strcmp(temp->key, key) == 0)
        {
          return temp->data;
        }
        temp = temp->next;
      }
    }

return NULL;
}

void changeData(HTable *hashTable, char key[], void * data)
{

  if(hashTable != NULL)
  {
      int index = hashTable->hashFunction(hashTable->size, key);

      if(hashTable->table[index] == NULL)
      {
        return;
      }

      Node *temp = hashTable->table[index];
      while(temp != NULL)
      {
        if(strcmp(temp->key, key) == 0)
        {
          temp->data = data;

          return;
        }
        temp = temp->next;
      }
    }


}
