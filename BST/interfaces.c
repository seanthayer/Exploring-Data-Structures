#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "structs.h"
#include "interfaces.h"


void initBST(struct BST* tree)
{
  /*  Description:
   *    Function initializes a BST structure using a pointer to its memory address.
   *    The function does not allocate additional memory upon initialization.
   *    
   *  Parameters:
   *    [struct] (BST*) tree: A pointer to the BST.
   * 
   *  Pre-conditions:
   *    - Pointer 'tree' points to a proper memory location.
   * 
   *  Post-conditions:
   *    - The BST is initialized: the size is 0, and the root points to NULL.
   */

  assert(tree);

  tree->size = 0;
  tree->root = NULL;
}

void freeBST(struct BST* tree)
{
  /*  Description:
   *    Function calls recursive function " _freePostOrder() " to free all nodes,
   *    in post-order.
   *    
   *  Parameters:
   *    [struct] (BST*) tree: A pointer to the BST.
   * 
   *  Pre-conditions:
   *    - Pointer 'tree' points to a proper memory location.
   *    - The BST is correctly linked.
   * 
   *  Post-conditions:
   *    - The BST's memory is freed.
   */

  assert(tree);

  _freePostOrder(tree->root);
}

int containsBST(struct BST* tree, TYPE val)
{
  /*  Description:
   *    For a well balanced tree, complexity O(log₂(n)).
   *    Function calls recursive function " _containsNode() " to traverse the BST,
   *    and determine whether the value is contained within it.
   *    
   *  Parameters:
   *    [struct] (BST*) tree: A pointer to the BST.
   *    [TYPE]           val: The value to search for.
   * 
   *  Pre-conditions:
   *    - Pointer 'tree' points to a proper memory location.
   *    - The BST is correctly linked.
   * 
   *  Post-conditions:
   *    - The function returns True (1) if the value is contained, or False (0) if not.
   */

  assert(tree);
  
  if ( isEmptyBST(tree) )
  {
    return 0;
  }
  else
  {
    return _containsNode(tree->root, val);
  }
  
}

void addBST(struct BST* tree, TYPE val)
{
  /*  Description:
   *    For a well balanced tree, complexity O(log₂(n)).
   *    Function calls recursive function " _addNode() " to traverse the BST,
   *    and correctly add a node with the value, maintaining BST principles.
   *    
   *  Parameters:
   *    [struct] (BST*) tree: A pointer to the BST.
   *    [TYPE]           val: The value to insert.
   * 
   *  Pre-conditions:
   *    - Pointer 'tree' points to a proper memory location.
   *    - The BST is correctly linked.
   * 
   *  Post-conditions:
   *    - The function adds and links the given value to the BST.
   */

  assert(tree);

  tree->root = _addNode(tree->root, val);

  tree->size++;
}

void removeBST(struct BST* tree, TYPE val)
{
  /*  Description:
   *    For a well balanced tree, complexity O(log₂(n)).
   *    Function calls recursive function " _removeNode() " to traverse the BST,
   *    and correctly remove a value, maintaining BST principles.
   *    
   *  Parameters:
   *    [struct] (BST*) tree: A pointer to the BST.
   *    [TYPE]           val: The value to remove.
   * 
   *  Pre-conditions:
   *    - Pointer 'tree' points to a proper memory location.
   *    - The BST is correctly linked.
   * 
   *  Post-conditions:
   *    - The function removes the given value and properly re-links the BST.
   */

  assert(tree);

  if ( containsBST(tree, val) )
  {
    tree->root = _removeNode(tree->root, val);

    tree->size--;
  }
  
}

void printBST(struct BST* tree)
{
  /*  Description:
   *    Function calls recursive function " _printInOrder() " to traverse the BST,
   *    and print the nodes in-order.
   *    
   *  Parameters:
   *    [struct] (BST*) tree: A pointer to the BST.
   * 
   *  Pre-conditions:
   *    - Pointer 'tree' points to a proper memory location.
   *    - The BST is correctly linked.
   * 
   *  Post-conditions:
   *    - The function prints the BST in-order to stdout.
   */

  assert(tree);

  _printInOrder(tree->root);
}

int isEmptyBST(struct BST* tree)
{
  /*  Description:
   *    Function checks the BST's size and returns true or false.
   *    
   *  Parameters:
   *    [struct]  (BST*)  tree: A pointer to the BST.
   * 
   *  Returns:
   *    [int]     (1 || 0): True or False, if the structure is empty or not.
   * 
   *  Pre-conditions:
   *    - Pointer 'tree' points to a proper memory location.
   *    - The BST was initialized correctly.
   * 
   *  Post-conditions:
   *    - True (1) or False (0) is returned.
   */

  assert(tree);

  if (tree->size == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
  
}

struct Node* _addNode(struct Node* curr, TYPE val)
{
  /*  Description:
   *    Recursive auxiliary function.
   *    Traverses the BST using binary search. Upon encountering
   *    a NULL pointer, allocates memory for a new node with the given value.
   *    After creating the new node, the function returns the node and further
   *    recursion stops. The BST is correctly re-linked as each recursive call
   *    returns.
   *    
   *  Parameters:
   *    [struct] (Node*) curr: A pointer to the next node to traverse from.
   *    [TYPE]           val : The value to insert.
   * 
   *  Pre-conditions:
   *    - Pointer 'curr' points to a proper memory location.
   *    - The BST is correctly linked.
   * 
   *  Post-conditions:
   *    - The function adds and links the given value to the BST.
   */

  struct Node* node;

  /* When the current node is a NULL pointer, create the new node */
  if (curr == NULL)
  {
    node = (struct Node*) malloc(sizeof(struct Node));

    assert(node);

    node->val = val;
    node->left = NULL;
    node->right = NULL;

    /* Returns the newly created node to the previous recursive call,
     * and any previous recursive calls return, consecutively. */
    return node;
  }
  else
  {

    /* Binary search */
    if ( LT(val, curr->val) )
    {
      /* Traverse left subtree */
      curr->left = _addNode(curr->left, val);
    }
    else
    {
      /* Traverse right subtree */
      curr->right = _addNode(curr->right, val);
    }

  }
  
  /* As recursive calls return in cascade, each unchanged child node is 
   * correctly returned to the previous parent node. */
  return curr;
}

struct Node* _removeNode(struct Node* curr, TYPE val)
{
  /*  Description:
   *    Recursive auxiliary function.
   *    Traverses the BST using binary search. Upon encountering
   *    the node with the given value, the function determines if it has a right child node:
   * 
   *    - No child    -> the function frees the removal node, and returns its left child (NULL or otherwise),
   *                     ending further recursion.
   *    - Right child -> the function finds the leftmost descendant of the right child, overwrites the removal
   *                     node with its value, and calls recursive function " _removeLeftmost " to
   *                     remove its original node and properly re-link any children nodes. The function
   *                     then returns the current node with the overwritten value, ending further recursion.
   *    
   *    As the recursive calls return in cascade, each node maintains correct linkage.
   *    
   *  Parameters:
   *    [struct] (Node*) curr: A pointer to the next node to traverse from.
   *    [TYPE]           val : The value to remove.
   * 
   *  Pre-conditions:
   *    - Pointer 'curr' points to a proper memory location.
   *    - The BST is correctly linked.
   * 
   *  Post-conditions:
   *    - The node with the given value is removed, its memory is freed, and BST principles are maintained.
   */

  struct Node* node;

  if ( EQ(val, curr->val) )
  {

    if (curr->right == NULL)
    {
      node = curr->left;

      free(curr);

      return node;
    }
    else
    {
      /* Finding leftmost descendant of the right child */
      /* { */
      node = curr->right;

      while (node->left)
      {
        node = node->left;
      }
      /* } */

      curr->val = node->val;
      curr->right = _removeLeftmost(curr->right);

    }
    
  }
  else
  {

    /* Binary search */
    if ( LT(val, curr->val) )
    {
      /* Traverse left subtree */
      curr->left = _removeNode(curr->left, val);
    }
    else
    {
      /* Traverse right subtree */
      curr->right = _removeNode(curr->right, val);
    }

  }

  /* As recursive calls return in cascade, each unchanged child node is 
   * correctly returned to the previous parent node. */
  return curr;
}

struct Node* _removeLeftmost(struct Node* curr)
{
  /*  Description:
   *    Recursive auxiliary function.
   *    Traverses the BST through only left child nodes. Upon encountering
   *    a NULL left child pointer, the function frees the current node (the leftmost descendant), and
   *    returns its right child node, ending further recursion.
   *    As the recursive calls return in cascade, each node maintains correct linkage.
   *    
   *  Parameters:
   *    [struct] (Node*) curr: A pointer to the next node to traverse from.
   * 
   *  Pre-conditions:
   *    - Pointer 'curr' points to a proper memory location.
   *    - The BST is correctly linked.
   * 
   *  Post-conditions:
   *    - The leftmost descendant is removed, its memory is freed, and its right child takes its place.
   */

  struct Node* node;

  if(curr->left)
  {
    curr->left = _removeLeftmost(curr->left);

    return curr;
  }
  else
  {
    node = curr->right;

    free(curr);

    return node;
  }

}

int _containsNode(struct Node* curr, TYPE val)
{
  /*  Description:
   *    Recursive auxiliary function.
   *    Traverses the BST using binary search. Upon encountering
   *    the node with the given value, the function returns True (1) to the previous
   *    recursive call, ending further recursion. Else, the function traverses until
   *    encountering a NULL child node pointer, indicating the absence of the given value in the BST.
   *    This ends further recursion, and as the recursive calls return in cascade,
   *    either True (1) or False (0) will be returned to the origin call.
   *    
   *  Parameters:
   *    [struct] (Node*) curr: A pointer to the next node to traverse from.
   *    [TYPE]           val : The value to search for.
   * 
   *  Pre-conditions:
   *    - Pointer 'curr' points to a proper memory location.
   *    - The BST is correctly linked.
   * 
   *  Post-conditions:
   *    - The BST is traversed, and upon reaching the value or upon reaching
   *      a NULL child node pointer, the function returns True (1) or False (0), accordingly.
   */

  int flag = 0;

  if ( EQ(val, curr->val) )
  {
    flag = 1;
  }
  else
  {
    /*  Checks for "curr->left" and "curr->right" to identify
     *  NULL child nodes, and if there's no where to traverse,
     *  then the functions flows naturally and returns the initial
     *  flag value of 0.
     */
    
    if ( LT(val, curr->val) && curr->left)
    {
      flag = _containsNode(curr->left, val);
    }
    else if (curr->right)
    {
      flag = _containsNode(curr->right, val);
    }

  }
  
  return flag;
}

void _printInOrder(struct Node* curr)
{
  /*  Description:
   *    Recursive auxiliary function.
   *    Traverses the BST and prints node values in-order.
   *    
   *  Parameters:
   *    [struct] (Node*) curr: A pointer to the next node to traverse from.
   * 
   *  Pre-conditions:
   *    - Pointer 'curr' points to a proper memory location.
   *    - The BST is correctly linked.
   * 
   *  Post-conditions:
   *    - The BST is traversed and node values are printed to stdout in-order.
   */

  if (curr)
  {
    _printInOrder(curr->left);
    printf("Node with value: { %d }\n", curr->val);
    _printInOrder(curr->right);
  }
  
}

void _freePostOrder(struct Node* curr)
{
  /*  Description:
   *    Recursive auxiliary function.
   *    Traverses the BST and frees node memory allocations post-order.
   *    
   *  Parameters:
   *    [struct] (Node*) curr: A pointer to the next node to traverse from.
   * 
   *  Pre-conditions:
   *    - Pointer 'curr' points to a proper memory location.
   *    - The BST is correctly linked.
   * 
   *  Post-conditions:
   *    - The BST is traversed and node memory allocations are freed post-order.
   */

  if (curr)
  {
    _freePostOrder(curr->left);
    _freePostOrder(curr->right);
    free(curr);
  }
  
}
