#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "QueueADT.h"
#include "LinkedListAPI.h"

Queue *initializeQueue(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second))
{
  Queue *newQueue = malloc(sizeof(Queue));

  newQueue->list = initializeList(printFunction, deleteFunction,compareFunction);
  newQueue->front = newQueue->list->head;
  newQueue->length = 0;

  return newQueue;
}

void deleteQueue(Queue *queue)
{
  if(queue->front != NULL)
  {
    deleteList(queue->list);

    queue->front = NULL;
  }
  free(queue->list);
  free(queue);
}

void enQueue(Queue *queue, void *toBeAdded)
{
  insertBack(queue->list, toBeAdded);
  queue->front = queue->list->head;
  queue->length += 1;
}

void * deQueue(Queue *queue)
{
  void * theFront = peekQueue(queue);

  deleteDataFromList(queue->list, theFront);
  queue->front = queue->list->head;
  queue->length -= 1;

  return theFront;
}

void * peekQueue(Queue *queue)
{
  if(queue->front == NULL)
  {
    printf("List empty when peeking Queue\n");
    return NULL;
  }
  return getFromFront(queue->list);
}

void printQueue(Queue *queue)
{
  printForward(queue->list);
}
