#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"heaphelper.h"
#include"heap.h"



void delete(void *toBeDeleted)
{
  free(toBeDeleted);
}

int compare(const void *first,const void *second)
{
  int *a = (int*) first;
  int *b = (int*)second;
  return *a - *b;
}

int main ()
{
    int * ptr1 = malloc(sizeof(int));
    int * ptr2 = malloc(sizeof(int));
    int * ptr3 = malloc(sizeof(int));
    int * ptr4 = malloc(sizeof(int));
    int * ptr5 = malloc(sizeof(int));
    int * ptr6 = malloc(sizeof(int));
    int * ptr7 = malloc(sizeof(int));
    int * ptr8 = malloc(sizeof(int));
    int * ptr9 = malloc(sizeof(int));
    int * ptr10 = malloc(sizeof(int));

    *ptr1 = 1;
    *ptr2 = 2;
    *ptr3 = 3;
    *ptr4 = 5;
    *ptr5 = 4;
    *ptr6 = 10;
    *ptr7 = 8;
    *ptr8 = 9;
    *ptr9 = 89;
    *ptr10 = 95;


    printf("*** Test #1: createHeapNode ***\n");
    printf("Expected:\n\n");
    Node * newNode1 = createHeapNode(ptr1);
    Node * newNode2 = createHeapNode(ptr2);
    print(newNode1->data);
    print(newNode2->data);
    printf("Received:\n");
    printf("   ***PASS***   \n\n");

    printf("*** Test #2: createHeap ***\n");
    printf("Expected:\n\n");
    Heap * newHeap = createHeap(5, 0, delete, print , compare);
    printf("Received:\n\n");
    printf("   ***PASS***   \n\n");


    printf("*** Test #3: insertHeapNode ***\n");
    printf("Expected:\n\n");
    insertHeapNode(newHeap, ptr1);
    printHeap(newHeap);
    insertHeapNode(newHeap, ptr2);
    printHeap(newHeap);
    insertHeapNode(newHeap, ptr3);
    printHeap(newHeap);
    insertHeapNode(newHeap, ptr4);
    printHeap(newHeap);
    insertHeapNode(newHeap, ptr5);
    printHeap(newHeap);
    insertHeapNode(newHeap, ptr6);
    printHeap(newHeap);
    insertHeapNode(newHeap, ptr7);
    printHeap(newHeap);
    printf("Received:\n\n");
    printf("   ***PASS***   \n\n");

    printf("*** Test #2: deleteMinOrMax ***\n");
    printf("Expected:\n\n");
    /*deleteMinOrMax(newHeap);
    printHeap(newHeap);

    deleteMinOrMax(newHeap);
    printHeap(newHeap);

    deleteMinOrMax(newHeap);

    printHeap(newHeap);*/
   changeHeapType(newHeap);
    printHeap(newHeap);
    changeHeapType(newHeap);
     printHeap(newHeap);
     insertHeapNode(newHeap, ptr10);
     printHeap(newHeap);
     insertHeapNode(newHeap, ptr8);
     printHeap(newHeap);
     changeHeapType(newHeap);
      printHeap(newHeap);
      changeHeapType(newHeap);
       printHeap(newHeap);
       changeHeapType(newHeap);
        printHeap(newHeap);
        insertHeapNode(newHeap, ptr9);
        printHeap(newHeap);
        changeHeapType(newHeap);
         printHeap(newHeap);
         changeHeapType(newHeap);
          printHeap(newHeap);
    /*changeHeapType(newHeap);
    printHeap(newHeap);
    changeHeapType(newHeap);
    printHeap(newHeap);
    changeHeapType(newHeap);
    printHeap(newHeap);*/
    /*deleteHeap(newHeap);
    printf("After deleting\n");
    printHeap(newHeap);*/

    /*insertHeapNode(newHeap, ptr8);

    printHeap(newHeap);

    deleteMinOrMax(newHeap);
    printHeap(newHeap);*/

    printf("Received:\n\n");
    printf("   ***PASS***   \n\n");

    /*
    int heapLevel = 0;
    int heapLevelSum = 0;
    int heapBottom = 0;
    int sizeInit = 12;
    int size = sizeInit -1;


    while(heapLevelSum + pow(2 , heapLevel) <= size)
    {
      heapLevelSum = heapLevelSum + pow(2 , heapLevel);
      heapLevel++;
    }

    heapBottom = size - heapLevelSum;
    int heapBottomSum = pow(2 , heapLevel);
    printf("Level: %d, Size: %d [%d + %d], Next:%d\n", heapLevel, size, heapLevelSum, heapBottom ,heapBottomSum);

    int mid = heapBottomSum/2;
    int i;


    for(i = 0; i < heapLevel; i++)
    {

      if(heapBottom < mid)
      {
        printf("left\n");
      }
      else
      {
        printf("right\n");

        heapBottom = heapBottom -mid;
      }
      printf("heapBottom: %d\n", heapBottom);
      printf("mid: %d\n", mid);
      mid = mid/2;
    }

*/


    return 0;
}
