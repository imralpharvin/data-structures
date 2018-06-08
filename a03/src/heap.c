#include <stdio.h>

#include "heap.h"

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{

}

Node *createHeapNode(void *data)
{

}

void insertHeapNode(Heap *heap, void *data)
{

}

void deleteMinOrMax(Heap *heap)
{

}

void *getMinOrMax(Heap *heap)
{

}

void changeHeapType(Heap *heap)
{

}

void deleteHeap(Heap *heap)
{
    
}