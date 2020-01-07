#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedListAPI.h"

void print(void *toBePrinted);
void delete(void *toBeDeleted);
int compare(const void *first,const void *second);

void print(void *toBePrinted)
{
  int number;

  number = *((int *) toBePrinted);
  printf("%d\n", number);
}

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

int main()
{
  List *list1 = initializeList(print, delete, compare);

  int* voidptr1 = malloc(sizeof(int));
  int* voidptr2 = malloc(sizeof(int));
  int* voidptr3 = malloc(sizeof(int));
  int* voidptr4 = malloc(sizeof(int));
  int* voidptr5 = malloc(sizeof(int));

  *voidptr1 = 1;
  *voidptr2 = 2;
  *voidptr3 = 3;
  *voidptr4 = 4;
  *voidptr5 = 5;

  printf("LIST 1\n");
  insertFront(list1,voidptr4);
  insertFront(list1,voidptr3);
  insertFront(list1,voidptr2);
  insertFront(list1,voidptr1);
  insertBack(list1,voidptr5);

  printf("Print forward\n");
  printForward(list1);

  printf("Print backwards\n");
  printBackwards(list1);

  printf("Get data from the front\n");
  list1->printData(getFromFront(list1));

  printf("Get data from the back\n");
  list1->printData(getFromBack(list1));

  printf("Delete data from list\n");
  deleteDataFromList(list1,voidptr3);

  printf("Print forward\n");
  printForward(list1);

  printf("Delete List\n\n");
  deleteList(list1);

  printf("LIST 2\n");
  printf("Insert Sorted\n");
  List *list2 = initializeList(print, delete, compare);

  int* vptr1 = malloc(sizeof(int));
  int* vptr2 = malloc(sizeof(int));
  int* vptr3 = malloc(sizeof(int));

  *vptr1 = 2;
  *vptr2 = 1;
  *vptr3 = 4;

  insertSorted(list2, vptr1);
  insertSorted(list2, vptr2);
  insertSorted(list2, vptr3);

  printf("Printing forward\n");
  printForward(list2);
  deleteList(list2);
  printForward(list2);
  free(list1);
  free(list2);
  return 0;
}
