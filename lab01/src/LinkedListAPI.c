#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedListAPI.h"

List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second))
{
  List *newList = malloc(sizeof(List));
  newList->head = NULL;
  newList->tail = NULL;
  newList->deleteData = deleteFunction;
  newList->printData = printFunction;
  newList->compare = compareFunction;

  return newList;
}

Node *initializeNode(void *data)
{
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->previous = NULL;
  newNode->next = NULL;

  return newNode;
}

void insertFront(List *list, void *toBeAdded)
{
  if( list == NULL)
  {
    return;
  }

  Node *frontNode = initializeNode(toBeAdded);

  if(list->head == NULL && list->tail == NULL)
  {
    list->head = frontNode;
    list->tail = frontNode;
    return;
  }

  frontNode->next = list->head;
  list->head->previous = frontNode;
  list->head = frontNode;
}

void insertBack(List *list, void *toBeAdded)
{
  if(list == NULL)
  {
    return;
  }

  Node *backNode = initializeNode(toBeAdded);

  if(list->head == NULL && list->tail == NULL)
  {
    list->head = backNode;
    list->tail = backNode;
    return;
  }

  list->tail->next = backNode;
  backNode->previous = list->tail;
  list->tail = backNode;
}

void deleteList(List *list)
{
  if(list == NULL)
  {
    return;
  }

  if(list->head == NULL)
  {

    free(list);
    return;
  }

  while(list->head != NULL)
  {
    Node *tempNode = NULL;
    tempNode = list->head;
    list->head = list->head->next;
    tempNode->next = NULL;
    tempNode->previous = NULL;
    if(tempNode->data != NULL)
    {
      list->deleteData(tempNode->data);
    }
    free(tempNode);
  }
  list->head = NULL;
  list->tail = NULL;

}

void insertSorted(List *list, void *toBeAdded)
{
  if (list == NULL || toBeAdded == NULL)
  {
    return;
  }

  if ((list->head == NULL && list->tail == NULL) || (list->compare(list->head->data, toBeAdded) >= 0))
  {
    insertFront(list, toBeAdded);
  }

  else
  {
    Node *tempNode = list->head;
    Node *beforeNode = NULL;

    while (tempNode != NULL && (list->compare(toBeAdded, tempNode->data) > 0))
    {
      beforeNode = tempNode;
      tempNode = tempNode->next;
    }

    if (tempNode == NULL)
    {
      insertBack(list, toBeAdded);
    }

    else
    {
      Node *betweenNode = initializeNode(toBeAdded);

      betweenNode->next = tempNode;
      betweenNode->previous = beforeNode;
      tempNode->previous = betweenNode;
      beforeNode->next = betweenNode;
    }
  }
}

int deleteDataFromList(List *list, void *toBeDeleted)
{
  if (list == NULL || list->head == NULL || toBeDeleted == NULL)
  {
    return -1;
  }

  Node *tempNode = list->head;

  while(tempNode->data != toBeDeleted)
  {
    if(tempNode->next == NULL)
    {
      return -1;
    }
    else
    {
      tempNode = tempNode->next;
    }
  }

  if(list->head == list->tail)
  {
    free(tempNode);
    list->head = NULL;
    list->tail = NULL;
    return 1;
  }

  if(tempNode == list->head)
  {
    list->head = list->head->next;
    list->head->previous = NULL;
    free(tempNode);
    return 1;
  }

  if(tempNode->next == NULL)
  {
    tempNode->previous->next = NULL;
    list->tail = tempNode->previous;
    free(tempNode);
    return 1;
  }

  tempNode->previous->next = tempNode->next;
  tempNode->next->previous = tempNode->previous;
  free(tempNode->data);
  free(tempNode);
  return 1;

}

void *getFromFront(List *list)
{
  if(list == NULL || list->head == NULL)
  {
    return NULL;
  }

  else
  {
    return list->head->data;
  }
}

void *getFromBack(List *list)
{
  if(list == NULL || list->tail == NULL)
  {
    return NULL;
  }

  else
  {
    return list->tail->data;
  }
}

void printForward(List *list)
{
  if(list == NULL || (list->head == NULL && list->tail == NULL))
  {

    return;
  }

  Node *tempNode = list->head;
  while(tempNode != NULL)
  {
    list->printData(tempNode->data);
    tempNode = tempNode->next;
  }
}

void printBackwards(List *list)
{
  if(list == NULL || (list->head == NULL && list->tail == NULL))
  {
    return;
  }

  Node* tempNode = list->tail;

  while(tempNode != NULL)
  {
    list->printData(tempNode->data);
    tempNode = tempNode->previous;
  }
}
