#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "heaphelper.h"
#include "heap.h"

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{
  /*Create and allocate space for a new Heap of initialSize
     set heap type to htype
     set delete function to the destrpuDataFP function pointer parameter
     set compare function to the compareFP function parameter
     set printNode function to the printNode function parameter
     return the new Heap*/

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
  /*create a pointer to a new Node
    set new nodes left, right and parent pointers to NULL
    set the node's data to the parameter data value
    return the pointer to the new Node*/
  Node *newNode = malloc(sizeof(Node));
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->parent = NULL;
  newNode->data = data;

  return newNode;
}

void insertHeapNode(Heap *heap, void *data)
{
/*
  create a node from the data
      locate the next position in the heap (the left most position with no node)
      add the new node to the located position
      reheapify the heap to maintain the heap property*/
  printf("Heap Size Before: %d\n", heap->size);
  printf("Data to insert: " );
  print((int*)data);
  Node * newNode = createHeapNode(data);

  //Locate to insert
  if(heap->heap == NULL && heap->size == 0)
  {
    heap->heap = newNode;
    heap->size ++;
  }

  else
  {
    int heapLevel = 0;
    int heapLevelSum = 0;
    int heapBottom = 0;
    int i;
    while(heapLevelSum + pow(2 , heapLevel) <= heap->size)
    {
      heapLevelSum = heapLevelSum + pow(2 , heapLevel);
      heapLevel++;
    }

    heapBottom = heap->size - heapLevelSum;
    Node * childNode = malloc(sizeof(Node));
    childNode = heap->heap;
    printf("Heap: ");
    print(heap->heap->data);
    Node * parentNode;
    int heapBottomSum = pow(2 , heapLevel);
    int mid = heapBottomSum/2;
    int direction = 0;

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


    printf("Data to insert: ");
    print(newNode->data);
    printf("Data of Parent: ");
    print(parentNode->data);
    printf("Data of Child: ");
    print(parentNode->left->data);
    printf("Data of child's parent: ");
    print(newNode->parent->data);

    /*insertNode->data = newNode->data;*/

    /*newNode->parent = parentNode;*/
    /*print(parentNode->data);*/

    heap->size ++;
    heap->lastPosition = newNode;
    heapifyUp(heap, newNode);

  }
  printf("\nHeap Size After: %d\n\n", heap->size);

  //Add node

}

void deleteMinOrMax(Heap *heap)
{
  printf("Heap Before: ");
  print(heap->heap->data);

  heap->heap->data = heap->lastPosition->data;
  heap->size--;


  printf("Heap After: ");
  print(heap->heap->data);

  if(getData(heap->lastPosition->parent->left->data) == getData(heap->lastPosition->data) )
  {
    printf("left\n");
    heap->lastPosition->parent->left = NULL;
  }

  else if(getData(heap->lastPosition->parent->right->data) == getData(heap->lastPosition->data))
  {
    printf("right\n");
    heap->lastPosition->parent->right = NULL;
  }

  heap->lastPosition->data = NULL;

  print(heap->heap->data);

  int heapLevel = 0;
  int heapLevelSum = 0;
  int heapBottom = 0;
  int j1 = heap->size -1;
  int i;
  while(heapLevelSum + pow(2 , heapLevel) <= j1)
  {
    heapLevelSum = heapLevelSum + pow(2 , heapLevel);
    heapLevel++;
  }

  heapBottom = j1 - heapLevelSum;
  Node * lastNode = heap->heap;


  int heapBottomSum = pow(2 , heapLevel);
  /*printf("Level: %d, Size: %d [%d + %d], Next:%d\n", heapLevel, j1, heapLevelSum, heapBottom ,heapBottomSum);*/
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
  printf("Position %d: ", heap->size);
  print(lastNode->data);
  print(heap->lastPosition->data);

  heapifyDown(heap, heap->heap);



  /*if(heap->)

  heap->heap =*/
}

void *getMinOrMax(Heap *heap)
{
  return heap->heap->data;
}

void changeHeapType(Heap *heap)
{

}

void deleteHeap(Heap *heap)
{

}

void heapifyUp(Heap * heap, Node * newNode)
{
  if(heap->size > 1)
  {
  Node * parentNode2 = newNode->parent;


  while(parentNode2 != NULL && getData(newNode->data) > getData(parentNode2->data))
  {
    printf("\nBefore\nNewnode:");
    print(newNode->data);
    printf("Parentnode:");
    print(parentNode2->data);

    void * temp = newNode->data;
    newNode->data = parentNode2->data;
    parentNode2->data = temp;


    newNode = parentNode2;
    parentNode2 = parentNode2->parent;
    printf("\nAfter\nNewnode:");
    print(newNode->data);
    printf("Parentnode:");
    if(parentNode2 != NULL)
    {
    print(parentNode2->data);
    }


  }
}


     /*parentNode = get parent node of newNode
     while(newNode->data is greater than parentNode->data  //or less than for a min heap
     {
        swap positions of newNode and Parent Node
        parentNode = get parent node of newNode (has changed because of the swap)
     }*/
}

void heapifyDown(Heap * heap, Node * newNode)
{

  if(heap->size > 1)
  {
  Node * tempNode = newNode;

    while(tempNode->right != NULL && tempNode->left != NULL)
    {
      if(tempNode->right != NULL)
      {
        if(getData(tempNode->right->data) > getData(tempNode->left->data))
        {
          if(getData(tempNode->right->data) > getData(tempNode->data))
          {
            void * temp = tempNode->right->data;
            tempNode->right->data = tempNode->data;
            tempNode->data = temp;

            tempNode = tempNode->right;
          }
        }
        else
        {
          if(getData(tempNode->left->data) > getData(tempNode->data))
          {
            void * temp = tempNode->left->data;
            tempNode->left->data = tempNode->data;
            tempNode->data = temp;

            tempNode = tempNode->left;
          }
        }
      }
      else
      {
        if(getData(tempNode->left->data) > getData(tempNode->data))
        {
          void * temp = tempNode->left->data;
          tempNode->left->data = tempNode->data;
          tempNode->data = temp;

          tempNode = tempNode->left;
          }
      }

    }
  }

}

void print(void *toBePrinted)
{
  int number;

  number = *((int *) toBePrinted);
  printf("%d\n", number);
}

int getData(void *toBePrinted)
{
  int number;

  number = *((int *) toBePrinted);

  return number;
}

void printHeap(Heap * heap)
{
  int j;

  for(j = 1; j <= heap->size; j++)
  {
    if( j == 1)
    {
      Node * printNode = heap->heap;
      printf("Position 1: ");
      print(printNode->data);
    }
    else
    {
      int heapLevel = 0;
      int heapLevelSum = 0;
      int heapBottom = 0;
      int i;
      int j1 = j -1;
      while(heapLevelSum + pow(2 , heapLevel) <= j1)
      {
        heapLevelSum = heapLevelSum + pow(2 , heapLevel);
        heapLevel++;
      }

      heapBottom = j1 - heapLevelSum;
      Node * printNode = heap->heap;


      int heapBottomSum = pow(2 , heapLevel);
      /*printf("Level: %d, Size: %d [%d + %d], Next:%d\n", heapLevel, j1, heapLevelSum, heapBottom ,heapBottomSum);*/
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
      print(printNode->data);


    }
  }
  printf("\n");
}
