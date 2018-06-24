#ifndef STUDENT_TREE_API_
#define STUDENT_TREE_API_
#include "balancedTreeAPI.h"

/*You may add anything to this .h file that you need to add to your tree ADT*/

//YOU MUST LEAVE THESE TYPEDEFS AS IS.
/**typedef for struct name*/
typedef struct BalancedBinTreeNode TreeNode;

/**typedef for struct name*/
typedef struct BalancedBinTree Tree;




/*complete the struct definitions.  You can change the existing parts if you wish.
*/
struct BalancedBinTree {
  //define your tree here.  You can change these if you need to but your tree must be abstract.
    TreeNode *root; ///< pointer to generic data that is to be stored in the tree
    int (*compareFP) (void *data1, void *data2); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
    void (*destroyFP) (void *data); ///< function pointer to a function to free a single pointer that is deleted from the tree
    void *(*copyFP)(void *toBeCopy); ///< function pointer to a function that copies pointer data

  };



struct BalancedBinTreeNode{
    void *data; ///< pointer to generic data that is to be stored in the heap
    TreeNode *left; ///< pointer to left tree node of current node. Null if empty.
    TreeNode *right; ///< pointer to right tree node of current node. Null if empty.

    //Add additional structure elements here
    int height;
};

//add function prototypes as necessary

void print(void *toBePrinted);

int max(int a, int b);
TreeNode* insert(Tree * theTree, TreeNode* node, void * toBeInserted);
int height(TreeNode *N);
TreeNode *rightRotate(TreeNode *y);

TreeNode *leftRotate(TreeNode *x);

int getBalance(TreeNode *N);

void preOrder(TreeNode *root);

TreeNode* deleteNode(Tree * tree, TreeNode* root, void * key);
TreeNode * minValueNode(TreeNode* node);

TreeNode* getNode(Tree * theTree, TreeNode* node, void * toBeInserted);
void printInorder(TreeNode* node);
void printPostorder(TreeNode* node);


#endif
