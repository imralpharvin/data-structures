#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "heaphelper.h"
#include "heap.h"

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{
  Heap * newHeap = malloc(sizeof(Heap));
  newHeap->heap = NULL;
  newHeap->lastPosition = newHeap->heap;
  newHeap->type = htype;
  newHeap->destroyData = destroyDataFP;
  newHeap->compare = compareFP;
  newHeap->printNode = printNodeFP;
  newHeap->size = 0;

  return newHeap;
}

Node *createHeapNode(void *data)
{
  Node *newNode = malloc(sizeof(Node));
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->parent = NULL;
  newNode->data = data;

  return newNode;
}

void insertHeapNode(Heap *heap, void *data)
{
  Node * newNode = createHeapNode(data);

  //Locate to insert
  //if heap size is 0
  if(heap->heap == NULL && heap->size == 0)
  {
    heap->heap = newNode;
    heap->size ++;
  }
  else
  {
    int heapLevel = 0; //height or level of heap
    int heapLevelSum = 0; //no of nodes of a heap level
    int heapBottom = 0;
    int i;

    //Calculate highest completed level of heap
    while(heapLevelSum + pow(2 , heapLevel) <= heap->size)
    {
      heapLevelSum = heapLevelSum + pow(2 , heapLevel);
      heapLevel++;
    }
    //Calculate number of nodes in current level
    heapBottom = heap->size - heapLevelSum;
    Node * childNode = heap->heap;
    Node * parentNode;

    int mid = (pow(2 , heapLevel))/2;
    int direction = 0;

    //Traverse to the last node
    for(i = 0; i < heapLevel; i++)
    {
      if(heapBottom < mid)
      {
        parentNode = childNode;
        childNode = childNode->left;
        direction = 0;
      }
      else
      {
        parentNode = childNode;
        childNode = childNode->right;
        heapBottom = heapBottom -mid;
        direction = 1;
      }
        mid = mid/2;
    }

    if(direction == 0)
    {
      parentNode->left = newNode;
    }
    else if(direction == 1)
    {
      parentNode->right = newNode;
    }

    newNode->parent = parentNode;

    heap->size ++;
    heap->lastPosition = newNode;

    heapifyUp(heap, newNode);

  }
}

void deleteMinOrMax(Heap *heap)
{

  if(heap->size == 1)
  {
    heap->heap->data = NULL;
    heap->heap = NULL;
    heap->lastPosition = NULL;
    heap->size --;
  }
  else
  {
    heap->heap->data = heap->lastPosition->data;
    heap->size--;

    if(heap->lastPosition->parent->left == heap->lastPosition)
    {
      heap->lastPosition->parent->left = NULL;
    }

    else if(heap->lastPosition->parent->right == heap->lastPosition )
    {
      heap->lastPosition->parent->right = NULL;
    }
    heap->lastPosition->data = NULL;

    int heapLevel = 0;
    int heapLevelSum = 0;
    int heapBottom = 0;
    int currentPosition = heap->size -1;
    int i;
    while(heapLevelSum + pow(2 , heapLevel) <= currentPosition)
    {
      heapLevelSum = heapLevelSum + pow(2 , heapLevel);
      heapLevel++;
    }

    heapBottom = currentPosition - heapLevelSum;
    Node * lastNode = heap->heap;

    int heapBottomSum = pow(2 , heapLevel);
    int mid = heapBottomSum/2;

    for(i = 0; i < heapLevel; i++)
    {
      if(heapBottom < mid)
      {
        lastNode = lastNode->left;
      }
      else
      {
        lastNode = lastNode->right;
        heapBottom = heapBottom -mid;
      }
        mid = mid/2;
    }
    heap->lastPosition = lastNode;

    heapifyDown(heap, heap->heap);
  }
}

void *getMinOrMax(Heap *heap)
{
  return heap->heap->data;
}

void changeHeapType(Heap *heap)
{
  int j;
  //Change heap type
  if(heap->type == 0)
  {
    heap->type = 1 ;
  }
  else if(heap->type == 1)
  {
    heap->type = 0 ;
  }

  //Heapify every single node in the array
  for(j = heap->size; j > 0; j--)
  {
    if( j == 1)
    {
      return;
    }
    else
    {
      int heapLevel = 0;
      int heapLevelSum = 0;
      int heapBottom = 0;
      int i;
      int currentPosition = j -1;
      while(heapLevelSum + pow(2 , heapLevel) <= currentPosition)
      {
        heapLevelSum = heapLevelSum + pow(2 , heapLevel);
        heapLevel++;
      }

      heapBottom = currentPosition - heapLevelSum;
      Node * exchangeNode = heap->heap;

      int heapBottomSum = pow(2 , heapLevel);
      int mid = heapBottomSum/2;

      for(i = 0; i < heapLevel; i++)
      {
        if(heapBottom < mid)
        {
          exchangeNode = exchangeNode->left;
        }
        else
        {
          exchangeNode = exchangeNode->right;
          heapBottom = heapBottom -mid;
        }
          mid = mid/2;
      }
      heapifyUp(heap, exchangeNode);
    }
  }


  for(j = 1; j <= heap->size; j++)
  {
    if( j == 1)
    {
      return;
    }
    else
    {
      int heapLevel = 0;
      int heapLevelSum = 0;
      int heapBottom = 0;
      int i;
      int currentPosition = j -1;
      while(heapLevelSum + pow(2 , heapLevel) <= currentPosition)
      {
        heapLevelSum = heapLevelSum + pow(2 , heapLevel);
        heapLevel++;
      }

      heapBottom = currentPosition - heapLevelSum;
      Node * exchangeNode = heap->heap;


      int heapBottomSum = pow(2 , heapLevel);
      int mid = heapBottomSum/2;

      for(i = 0; i < heapLevel; i++)
      {
        if(heapBottom < mid)
        {
          exchangeNode = exchangeNode->left;
        }
        else
        {
          exchangeNode = exchangeNode->right;
          heapBottom = heapBottom -mid;
        }
          mid = mid/2;
      }
      heapifyDown(heap, exchangeNode);
    }
  }
}

void deleteHeap(Heap *heap)
{
  while(heap->size > 0)
  {
    deleteMinOrMax(heap);
  }
}

void heapifyUp(Heap * heap, Node * newNode)
{
  if(heap->size > 1)
  {
  Node * parentNode2 = newNode->parent;

  if(heap->type == 1)
  {
    while(parentNode2 != NULL && heap->compare(newNode->data,parentNode2->data) > 0)
    {
      void * temp = newNode->data;
      newNode->data = parentNode2->data;
      parentNode2->data = temp;

      newNode = parentNode2;
      parentNode2 = parentNode2->parent;
    }
  }
  else if(heap->type == 0)
  {
    while(parentNode2 != NULL && heap->compare(newNode->data,parentNode2->data) < 0)
    {
      void * temp = newNode->data;
      newNode->data = parentNode2->data;
      parentNode2->data = temp;

      newNode = parentNode2;
      parentNode2 = parentNode2->parent;
    }
  }
}

}

void heapifyDown(Heap * heap, Node * newNode)
{
  if(heap->size > 1)
  {
  Node * tempNode = newNode;

    while(tempNode->right != NULL || tempNode->left != NULL)
    {
      if(tempNode->right != NULL)
      {
        if((heap->compare(tempNode->right->data, tempNode->left->data) > 0 && heap->type == 1) || (heap->compare(tempNode->right->data, tempNode->left->data) < 0 && heap->type == 0))
        {
          if((heap->compare(tempNode->right->data, tempNode->data) > 0 && heap->type == 1) || (heap->compare(tempNode->right->data, tempNode->data) < 0 && heap->type == 0))
          {
            void * temp = tempNode->right->data;
            tempNode->right->data = tempNode->data;
            tempNode->data = temp;

            tempNode = tempNode->right;
          }
          else
          {
            break;
          }
        }
        else
        {
          if((heap->compare(tempNode->left->data, tempNode->data) > 0 && heap->type == 1) || (heap->compare(tempNode->left->data, tempNode->data) < 0 && heap->type == 0))
          {
            void * temp = tempNode->left->data;
            tempNode->left->data = tempNode->data;
            tempNode->data = temp;

            tempNode = tempNode->left;
          }
          else
          {
            break;
          }
        }
      }
      else
      {
        if((heap->compare(tempNode->left->data, tempNode->data) > 0 && heap->type == 1) || (heap->compare(tempNode->left->data, tempNode->data) < 0 && heap->type == 0))
        {
          void * temp = tempNode->left->data;
          tempNode->left->data = tempNode->data;
          tempNode->data = temp;

          tempNode = tempNode->left;
        }
        else
        {
          break;
        }
      }
    }
  }

}


void printHeap(Heap * heap)
{
  int j;

  for(j = 1; j <= heap->size; j++)
  {
    if(j == 1)
    {
      Node * printNode = heap->heap;
      printf("Position 1: ");
      heap->printNode(printNode->data);
    }
    else
    {
      int heapLevel = 0;
      int heapLevelSum = 0;
      int heapBottom = 0;
      int i;
      int currentPosition = j -1;
      while(heapLevelSum + pow(2 , heapLevel) <= currentPosition)
      {
        heapLevelSum = heapLevelSum + pow(2 , heapLevel);
        heapLevel++;
      }

      heapBottom = currentPosition - heapLevelSum;
      Node * printNode = heap->heap;


      int heapBottomSum = pow(2 , heapLevel);
      int mid = heapBottomSum/2;

      for(i = 0; i < heapLevel; i++)
      {
        if(heapBottom < mid)
        {
          printNode = printNode->left;
        }
        else
        {
          printNode = printNode->right;
          heapBottom = heapBottom -mid;

        }
          mid = mid/2;
      }
      printf("Position %d: ", j);
      heap->printNode(printNode->data);
    }
  }
  printf("\n");
}
