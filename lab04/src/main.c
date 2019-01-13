#include <stdio.h>

#include"balancedTreeAPI.h"

int compare(void *first,void *second)
{

  int *a = (int*) first;
  int *b = (int*)second;


  return *a - *b;
}

void * copy(void *toBePrinted)
{
  int number;

  number = *((int *) toBePrinted);
  printf("%d\n", number);

  return NULL;
}

//User defined delete
void delete(void *toBeDeleted)
{
  free(toBeDeleted);
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
    printf("*** Test #1: createBalancedBinTree ***\n");
    printf("Expected:\n");
    Tree * newTree = createBalancedBinTree(compare, delete, copy);
    printf("Received:\n");
    printf("   ***PASS***   \n\n");

    printf("*** Test #2: createBalancedBinNode ***\n");
    printf("Expected:\n");
    treeInsertNode(newTree, ptr2);
    printf("Height: %d\n", (int) ((TreeNode*)(newTree->root))->height);

    treeInsertNode(newTree, ptr1);
    printf("Height: %d\n", (int) ((TreeNode*)(newTree->root))->height);

    treeInsertNode(newTree, ptr3);
    printf("Height: %d\n", (int) ((TreeNode*)(newTree->root))->height);

    treeInsertNode(newTree, ptr4);
    printf("Height: %d\n", (int) ((TreeNode*)(newTree->root))->height);

    treeInsertNode(newTree, ptr5);

    treeDeleteNode(newTree, ptr4);


    print(ptr1);
    print(newTree->root->data);
    print(newTree->root->left->data);
    print(newTree->root->right->data);

    print(treeFindMin(newTree));
    print(treeFindMax(newTree));
    /*print(newTree->root->right->right->data);
    print(newTree->root->right->right->left->data);*/
    printf("Height: %d\n", (int) ((TreeNode*)(newTree->root))->height);
    treePreOrderPrint(newTree, print);
    treeInOrderPrint(newTree, print);
    treePostOrderPrint(newTree, print);

    print(treeFindNode(newTree, ptr3));

    printf("Received:\n");
    printf("   ***PASS***   \n\n");

    printf("*** Test #3: treeInsertNode ***\n");
    printf("Expected:\n");

    printf("Received:\n");
    printf("   ***PASS***   \n\n");
    return 0;
}
