#include <stdio.h>

#include "emergency.h"
#include "heaphelper.h"
#include "heap.h"
#include "priorityQueueADT.h"

PQueue *createPriorityQueue(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{
  PQueue * newPQueue = malloc(sizeof(PQueue));
  Heap * newHeap = createHeap(initialSize, htype, destroyDataFP, printNodeFP,compareFP);

  newPQueue->heap = newHeap;
  newPQueue->front = newHeap->heap;
  return newPQueue;
}

void enQueue(PQueue *pqueue, void *data)
{
  insertHeapNode(pqueue->heap, data);
  pqueue->front = pqueue->heap->heap;
}

void deQueue(PQueue *pqueue)
{
  deleteMinOrMax(pqueue->heap);
  pqueue->front = pqueue->heap->heap;
}

void deletePriorityQueue(PQueue *pqueue)
{
  deleteHeap(pqueue->heap);
}
void printPriorityQueue(PQueue *pqueue)
{
  printHeap(pqueue->heap);
}

void *getFront(PQueue *pqueue)
{
  return pqueue->front->data;
}
