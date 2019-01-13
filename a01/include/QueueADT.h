/**
 * @file QueueADT.h
 * @author Ralph Arvin De Castro
 * @date June 2018
 * @brief File containing the function definitions of a queue wrapping a doubly linked list
 */

#ifndef _QUEUE_ADT_
#define _QUEUE_ADT_

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"

/**
 *Queue. It contains a list pointer, a node pointer that points to the front of the queue  and length that determines number of elements.
 **/
typedef struct queue
{
  List *list;
  Node *front;
  int length;
}Queue;

/**Function to allocate memory to the struct, initialize list pointer, setting front to the the list of the head, initialize length to 0
*@return pointer to the queue
*@param printFunction function pointer that prints a single node of the queue
*@param deleteFunction function pointer that deletes a single piece of data from the queue
*@param compareFunction function pointer that compares two nodes of the list
**/
Queue *initializeQueue(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second));

/** Deletes the queue from front, starting with the nodes, then list, then queue itself.
*@pre 'Queue' type must exist.
*@post Nodes,list and queue are deleted and freed.
*@param queue pointer to a queue
**/
void deleteQueue(Queue *queue);

/**Inserts a Node to the end of a queue
*@pre 'Queue' type must exist and data to be added must exist
*@post A node is inserted and length increases
*@param queue a pointer to a queue
*@param toBeAdded a pointer to data that is to be added to the linked list
**/
void enQueue(Queue *queue, void *toBeAdded);

/**Removes a Node to the end of a queue
*@return void pointer that points to the deleted node
*@pre 'Queue' type must exist
*@post A node is removed and length decreases
*@param queue a pointer to a queue
**/
void *deQueue(Queue *queue);

/**Looks at the data of the front of the queue
*@return void pointer that points to the data of the front node
*@pre 'Queue' type and front must exist
*@param queue a pointer to a queue
**/
void *peekQueue(Queue *queue);

/**Prints the data of the nodes of queue from front to end
*@pre 'Queue' type and front must exist
*@post Data of nodes are printed accordingly
*@param queue a pointer to a queue
**/
void printQueue(Queue *queue);

#endif
