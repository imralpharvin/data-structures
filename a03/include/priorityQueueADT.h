#ifndef _P_QUEUE_
#define _P_QUEUE_

#include "heaphelper.h"
typedef struct PQueue
{
    Heap *heap; /// contains all of the heap nodes
    Node *front;
}PQueue;

PQueue *createPriorityQueue(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second));

void enQueue(PQueue *pqueue, void *data);
void deQueue(PQueue *pqueue);
void deletePriorityQueue(PQueue *pqueue);
void printPriorityQueue(PQueue *pqueue);
void *getFront(PQueue *pqueue);


#endif
