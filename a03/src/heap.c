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
  /*printf("Heap Size Before: %d\n", heap->size);
  printf("Data to insert: " );*/
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
    /*printf("Heap: ");*/
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


    /*printf("Data to insert: ");
    print(newNode->data);
    printf("Data of Parent: ");
    print(parentNode->data);
    printf("Data of Child: ");
    print(parentNode->left->data);
    printf("Data of child's parent: ");
    print(newNode->parent->data);*/

    heap->size ++;
    heap->lastPosition = newNode;
    /*printf("lastPosition: ");
    print(heap->lastPosition->data);*/
    heapifyUp(heap, newNode);
    /*printf("lastPosition: ");
    print(heap->lastPosition->data);*/

  }
  /*printf("\nHeap Size After: %d\n\n", heap->size);*/

  //Add node

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
  /*printf("Heap Before: ");

  print(heap->heap->data);*/
  heap->heap->data = heap->lastPosition->data;
  heap->size--;


  /*printf("Heap After: ");
  print(heap->heap->data);*/


  /*if(heap->compare(heap->lastPosition->parent->left->data, heap->lastPosition->parent->right->data) == 0 )
  {
    heap->lastPosition->parent->right = NULL;
  }
  else*/
  /*if(heap->compare(heap->lastPosition->parent->left->data, heap->lastPosition->data) == 0 )*/
  if(heap->lastPosition->parent->left == heap->lastPosition)

  {

    heap->lastPosition->parent->left = NULL;
  }

  /*else if(heap->compare(heap->lastPosition->parent->right->data, heap->lastPosition->data) == 0 )*/
  else if(heap->lastPosition->parent->right == heap->lastPosition )

  {
    heap->lastPosition->parent->right = NULL;
  }

  heap->lastPosition->data = NULL;

  /*print(heap->heap->data);*/

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
  /*printf("Position %d: ", heap->size);
  print(lastNode->data);
  print(heap->lastPosition->data);*/

  heapifyDown(heap, heap->heap);

}

  /*if(heap->)

  heap->heap =*/
}

void *getMinOrMax(Heap *heap)
{
  return heap->heap->data;
}

void changeHeapType(Heap *heap)
{
  int j;
  if(heap->type == 0)
  {
    heap->type =1 ;
  }

  else if(heap->type == 1)
  {
    heap->type = 0 ;
  }

  for(j = heap->size; j > 0; j--)
  {
    if( j == 1)
    {
      /*Node * printNode = heap->heap;
      printf("Position 1: ");
      print(printNode->data);*/
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
      Node * exchangeNode = heap->heap;


      int heapBottomSum = pow(2 , heapLevel);
      /*printf("Level: %d, Size: %d [%d + %d], Next:%d\n", heapLevel, j1, heapLevelSum, heapBottom ,heapBottomSum);*/
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

      /*void * temp = heap->heap->data;
      heap->heap->data = exchangeNode->data;
      exchangeNode->data = temp;
      print(exchangeNode->data);*/
      heapifyUp(heap, exchangeNode);
      /*printf("Here1\n");
      printf("Position %d: \n", j);*/

    }
  }

  for(j = 1; j <= heap->size; j++)
  {
    if( j == 1)
    {
      /*printf("Position 1: ");
      print(printNode->data);*/
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
      Node * exchangeNode = heap->heap;


      int heapBottomSum = pow(2 , heapLevel);
      /*printf("Level: %d, Size: %d [%d + %d], Next:%d\n", heapLevel, j1, heapLevelSum, heapBottom ,heapBottomSum);*/
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

      /*void * temp = heap->heap->data;
      heap->heap->data = exchangeNode->data;
      exchangeNode->data = temp;
      print(exchangeNode->data);*/
      heapifyDown(heap, exchangeNode);
      /*printf("Here1\n");
      printf("Position %d: \n", j);*/

    }
  }
}

void deleteHeap(Heap *heap)
{

  while(heap->size > 0)
  {
    printf("heap->size: %d", heap->size);

    deleteMinOrMax(heap);
    printHeap(heap);
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
      /*printf("\nBefore\nNewnode:");
      print(newNode->data);
      printf("Parentnode:");
      print(parentNode2->data);*/

      void * temp = newNode->data;
      newNode->data = parentNode2->data;
      parentNode2->data = temp;


      newNode = parentNode2;
      parentNode2 = parentNode2->parent;
      /*printf("\nAfter\nNewnode:");
      print(newNode->data);
      printf("Parentnode:");
      if(parentNode2 != NULL)
      {
      print(parentNode2->data);
    }*/
    }
  }
  else if(heap->type == 0)
  {
    while(parentNode2 != NULL && heap->compare(newNode->data,parentNode2->data) < 0)
    {
      /*printf("\nBefore\nNewnode:");
      print(newNode->data);
      printf("Parentnode:");
      print(parentNode2->data);*/

      void * temp = newNode->data;
      newNode->data = parentNode2->data;
      parentNode2->data = temp;


      newNode = parentNode2;
      parentNode2 = parentNode2->parent;
    /*  printf("\nAfter\nNewnode:");
      print(newNode->data);
      printf("Parentnode:");
      if(parentNode2 != NULL)
      {
      print(parentNode2->data);
    }*/
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
  /*printf("tempNode: ");
  print(tempNode->data);*/

    if(heap->type == 1)
    {
      while(tempNode->right != NULL || tempNode->left != NULL)
      {
        /*printf("tempNode: ");
        print(tempNode->data);*/

        if(tempNode->right != NULL)
        {
          if(heap->compare(tempNode->right->data, tempNode->left->data) > 0)
          {
            if(heap->compare(tempNode->right->data, tempNode->data) > 0)
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

            if(heap->compare(tempNode->left->data, tempNode->data) > 0)
            {
              void * temp = tempNode->left->data;
              tempNode->left->data = tempNode->data;
              tempNode->data = temp;

              tempNode = tempNode->left;
              printf("Supposed to be here\n");

            }
            else
            {
              printf("Supposed to be here\n");
              break;
            }
          }
        }
        else
        {
          /*printf("Here\n");*/

          if(heap->compare(tempNode->left->data, tempNode->data) > 0)
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

    else if(heap->type == 0)
    {
      while(tempNode->right != NULL || tempNode->left != NULL)
      {
        if(tempNode->right != NULL)
        {
          heap->printNode(tempNode->left->data);
            heap->printNode(tempNode->right->data);
          if(heap->compare(tempNode->right->data, tempNode->left->data) < 0)
          {
            if(heap->compare(tempNode->right->data, tempNode->data) < 0)
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
            if(heap->compare(tempNode->left->data, tempNode->data) < 0)
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

          if(heap->compare(tempNode->left->data, tempNode->data) < 0)
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
      heap->printNode(printNode->data);
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
      heap->printNode(printNode->data);


    }
  }
  printf("\n");
}
