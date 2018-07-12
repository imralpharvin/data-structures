#ifndef _HEAP_HELP_
#define _HEAP_HELP_

#define MIN_HEAP 0
#define MAX_HEAP 1
#define HEAP_TYPE unsigned char

typedef struct Node
{
   void * data;
   struct Node * left;
   struct Node * right;
   struct Node * parent;
}Node;
/*Heap struct for binary tree implementation of a Heap*/
typedef struct Heap
{
    Node *heap; /// contains all of the heap nodes
    HEAP_TYPE type; ///< flag for choosing between min and max heap
    Node * lastPosition; //optional element useful for finding where to insert the next value
    void (*destroyData)(void *data); ///< function pointer to a function to delete a single piece of data from the heap
    void (*printNode)(void *toBePrinted); ///< function pointer to a function that prints out a data element of the heap
    int (*compare)(const void *first, const void *second); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
    int size;
}Heap;
/**
*Hash table structure
**/

void heapifyUp(Heap * heap, Node * newNode);

void heapifyDown(Heap * heap, Node * MaxMinNode);
void print(void *toBePrinted);
void printHeap(Heap * heap);

int getData(void *toBePrinted);



#endif
