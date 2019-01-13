/**
 * @file heaphelper.h
 * @author Ralph Arvin De Castro
 * @date July 2018
 * @brief File containing the function definitions of a hash table
 */

#ifndef _HEAP_HELP_
#define _HEAP_HELP_

#define MIN_HEAP 0
#define MAX_HEAP 1
#define HEAP_TYPE unsigned char

/**
*Node of the heap
**/
typedef struct Node
{
   void * data;
   struct Node * left;
   struct Node * right;
   struct Node * parent;
}Node;

/**
*Heap structure for binary tree implementation of a Heap
**/
typedef struct Heap
{
    Node *heap; ///< contains all of the heap nodes
    HEAP_TYPE type; ///< flag for choosing between min and max heap
    Node * lastPosition; ///<optional element useful for finding where to insert the next value
    void (*destroyData)(void *data); ///< function pointer to a function to delete a single piece of data from the heap
    void (*printNode)(void *toBePrinted); ///< function pointer to a function that prints out a data element of the heap
    int (*compare)(const void *first, const void *second); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
    int size;
}Heap;


/**Function to rearrange a heap to maintain heap property.Starts with a selected to heapify node then switch and traverse up if needed
 *@pre Heap must exist and have data allocated to it
 *@param heap Pointer to a heap
 *@param node Pointer to a node to heapify up
**/
void heapifyUp(Heap * heap, Node * node);

/**Function to rearrange a heap to maintain heap property.Starts with a selected to heapify node then switch and traverse down if needed
 *@pre Heap must exist and have data allocated to it
 *@param heap Pointer to a heap
 *@param node Pointer to a node to heapify down
**/
void heapifyDown(Heap * heap, Node * node);

/**Function to print all the nodes of the heap
 *@pre Heap must exist and have data allocated to it
 *@param heap Pointer to a heap
**/
void printHeap(Heap * heap);


#endif
