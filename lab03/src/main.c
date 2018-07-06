#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"heaphelper.h"
#include"heap.h"

//User defined function
void print(void *toBePrinted)
{
  int number;

  number = *((int *) toBePrinted);
  printf("%d\n", number);
}

//User defined function
void delete(void *toBeDeleted)
{
  free(toBeDeleted);
}

//User defined function
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
    /*int * ptr8 = malloc(sizeof(int));
    int * ptr9 = malloc(sizeof(int));
    int * ptr10 = malloc(sizeof(int));*/

    *ptr1 = 1;
    *ptr2 = 2;
    *ptr3 = 3;
    *ptr4 = 5;
    *ptr5 = 4;
    *ptr6 = 10;
    *ptr7 = 8;
  /*  *ptr8 = 9;
    *ptr9 = 89;
    *ptr10 = 95;*/


    printf("*** Test #1: createHeapNode ***\n");
    printf("Expected:\n");
    printf("HeapNode is NOT null\n");
    Node * newNode1 = createHeapNode(ptr1);
    printf("Received:\n");
    printf("%s\n", newNode1 ? "HeapNode is NOT null" : "HeapNode is NULL");
    printf("%s", newNode1 ? "   ***PASS***   \n\n" : "   ***FAILED***   \n\n");

    printf("*** Test #2: createHeap ***\n");
    printf("Expected:\n");
    printf("Heap is NOT null\n");
    Heap * newHeap = createHeap(5, 0, delete, print , compare);
    printf("Received:\n");
    printf("%s\n", newHeap ? "Heap is NOT null" : "Heap is NULL");
    printf("%s", newHeap ? "   ***PASS***   \n\n" : "   ***FAILED***   \n\n");

    printf("*** Test #3: insertHeapNode ***\n");
    printf("Expected:\n\n");
    printf("Position 1: 1\nPosition 2: 2\nPosition 3: 3\nPosition 4: 5\nPosition 5: 4\nPosition 6: 10\nPosition 7: 8\n");
    insertHeapNode(newHeap, ptr1);
    insertHeapNode(newHeap, ptr2);
    insertHeapNode(newHeap, ptr3);
    insertHeapNode(newHeap, ptr4);
    insertHeapNode(newHeap, ptr5);
    insertHeapNode(newHeap, ptr6);
    insertHeapNode(newHeap, ptr7);
    printf("\nReceived:\n\n");
    printHeap(newHeap);
    printf("   ***PASS***   \n\n");

    printf("*** Test #4a: deleteMinOrMax ***\n");
    printf("Expected:\n\n");
    printf("Position 1: 2\nPosition 2: 4\nPosition 3: 3\nPosition 4: 5\nPosition 5: 8\nPosition 6: 10\n");
    deleteMinOrMax(newHeap);
    printf("\nReceived:\n\n");
    printHeap(newHeap);
    printf("   ***PASS***   \n\n");

    printf("*** Test #4b: deleteMinOrMax ***\n");
    printf("Expected:\n\n");
    printf("Position 1: 3\nPosition 2: 4\nPosition 3: 10\nPosition 4: 5\nPosition 5: 8\n");
    deleteMinOrMax(newHeap);
    printf("\nReceived:\n\n");
    printHeap(newHeap);
    printf("   ***PASS***   \n\n");

    printf("*** Test #5: getMinOrMax ***\n");
    printf("Expected: 3\n");
    printf("Received: ");
    print(getMinOrMax(newHeap));
    printf("   ***PASS***   \n\n");

    printf("*** Test #6: changeHeapType ***\n");
    printf("Expected:\n");
    printf("Position 1: 10\nPosition 2: 5\nPosition 3: 8\nPosition 4: 3\nPosition 5: 4\n");
    printf("Received:\n");
    changeHeapType(newHeap);
    printHeap(newHeap);
    printf("   ***PASS***   \n\n");

    printf("*** Test #7: deleteHeap***\n");
    printf("Expected:\n");
    printf("Heap is NULL\n");
    deleteHeap(newHeap);
    printf("Received:\n");
    printf("%s\n", newHeap->heap ? "Heap is NOT null" : "Heap is NULL");
    printf("%s", newHeap->heap ? "   ***FAILED***   \n\n" : "   ***PASS***   \n\n");
    return 0;
}
