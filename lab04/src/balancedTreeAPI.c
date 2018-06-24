#include <stdio.h>


#include "balancedTreeAPI.h"


Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *toBeDeleted),void *(*copyFP)(void *toBeCopy))
{
  Tree * newTree = malloc(sizeof(Tree));

  newTree->root = NULL;
  newTree->compareFP = compareFP;
  newTree->destroyFP = destroyFP;
  newTree->copyFP = copyFP;
  return newTree;
}

TreeNode *createBalancedBinNode(void *data)
{
  TreeNode * newNode = malloc(sizeof(TreeNode));

  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->height = 1;
  return newNode;
}

void destroyBalancedBinTree(Tree *toBeDeleted)
{

}

void treeInsertNode(Tree *theTree, void *toBeInserted)
{


  Tree * tempTree = theTree;
  tempTree->root = insert(tempTree ,tempTree->root, toBeInserted);



}

void treeDeleteNode(Tree *theTree, void *toBeDeleted)
{
  Tree * tempTree = theTree;
  tempTree->root = deleteNode(tempTree ,tempTree->root, toBeDeleted);
}

int treeIsEmpty(Tree *theTree)
{
  if(theTree->root == NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }

  return 0;
}

int treeHasTwoChildren(TreeNode *root)
{
  if(root->left != NULL && root->right != NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }

  return 0;
}

void *treeFindNode(Tree *theTree, void *data)
{
  Tree * tempTree = theTree;
  TreeNode * node = node;

  node =  getNode(tempTree, tempTree->root, data);
  return node->data;
}

void *treeFindMin(Tree *theTree)
{
  TreeNode * root = theTree->root;
  while(root->left != NULL)
  {
      root = root->left;
  }

return root->data;
}

void *treeFindMax(Tree *theTree)
{
  TreeNode * root = theTree->root;
  while(root->right != NULL)
  {
      root = root->right;
  }

return root->data;
}

void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
  printInorder(theTree->root);
}

void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
  preOrder(theTree->root);
}

void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{

  printPostorder(theTree->root);

}
int max(int a, int b)
{
    return (a > b)? a : b;
}

TreeNode* insert(Tree * theTree, TreeNode* node, void * toBeInserted)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
    {
        return(createBalancedBinNode(toBeInserted));
    }

    if (theTree->compareFP(toBeInserted , node->data) < 0)
    {
        node->left  =insert(theTree, node->left, toBeInserted);
    }
    else if (theTree->compareFP(toBeInserted , node->data) > 0)
    {
        node->right = insert(theTree, node->right, toBeInserted);
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
    if (balance > 1 && theTree->compareFP(toBeInserted , node->left->data) < 0)
       return rightRotate(node);

   // Right Right Case
   if (balance < -1 && theTree->compareFP(toBeInserted, node->right->data) > 0)
       return leftRotate(node);

   // Left Right Case
   if (balance > 1 && theTree->compareFP(toBeInserted , node->left->data) > 0)
   {
       node->left =  leftRotate(node->left);
       return rightRotate(node);
   }

   // Right Left Case
   if (balance < -1 && theTree->compareFP(toBeInserted , node->right->data) < 0)
   {
       node->right = rightRotate(node->right);
       return leftRotate(node);
   }
    return node;

}

void print(void *toBePrinted)
{
  int number;

  number = *((int *) toBePrinted);
  printf("%d\n", number);
}

int height(TreeNode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

TreeNode *rightRotate(TreeNode *y)
{
    TreeNode *x = y->left;
    TreeNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
TreeNode *leftRotate(TreeNode *x)
{
    TreeNode *y = x->right;
    TreeNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(TreeNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

void preOrder(TreeNode *root)
{
    if(root != NULL)
    {
        printf("%d ", *(int*) root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

TreeNode* deleteNode(Tree * tree, TreeNode* root, void * key)
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if (tree->compareFP (key , root->data ) < 0)
        root->left = deleteNode(tree, root->left, key);

    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( tree->compareFP (key , root->data )> 0)
        root->right = deleteNode(tree, root->right, key);

    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            TreeNode *temp = root->left ? root->left :
                                             root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            TreeNode* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(tree, root->right, temp->data);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
      return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

TreeNode * minValueNode(TreeNode* node)
{
    TreeNode* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

TreeNode* getNode(Tree * theTree, TreeNode* node, void * toBeInserted)
{

  if (theTree->compareFP(toBeInserted , node->data) ==  0)
  {
    TreeNode * toBePassed = createBalancedBinNode(toBeInserted);
    print(toBeInserted);
    print(node->data);
    printf("equal\n");
    return toBePassed;
  }

  else if (theTree->compareFP(toBeInserted , node->data) < 0)
  {
    printf("left\n");
    print(node->data);

      /*node->left  = */return getNode(theTree, node->left, toBeInserted);
  }
  else if (theTree->compareFP(toBeInserted , node->data) > 0)
  {
    printf("right\n");
    print(node->data);

      /*node->right =*/ return getNode(theTree, node->right, toBeInserted);
  }

  return node;
}

void printInorder(TreeNode* node)
{
     if (node == NULL)
          return;

     /* first recur on left child */
     printInorder(node->left);

     /* then print the data of node */
     printf("%d ", *(int*)(node->data));

     /* now recur on right child */
     printInorder(node->right);
}

void printPostorder(TreeNode* node)
{
     if (node == NULL)
        return;

     // first recur on left subtree
     printPostorder(node->left);

     // then recur on right subtree
     printPostorder(node->right);

     // now deal with the node
     printf("%d ", *(int*)(node->data));
}
