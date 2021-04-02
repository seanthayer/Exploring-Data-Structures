#include "structs.h"

#ifndef __INTERFACES_H
#define __INTERFACES_H

/* Binary Search Tree */
void initBST(struct BST* tree);
void freeBST(struct BST* tree);
int containsBST(struct BST* tree, TYPE val);
void addBST(struct BST* tree, TYPE val);
void removeBST(struct BST* tree, TYPE val);
void printBST(struct BST* tree);
int isEmptyBST(struct BST* tree);
struct Node* _addNode(struct Node* curr, TYPE val);
struct Node* _removeNode(struct Node* curr, TYPE val);
struct Node *_removeLeftmost(struct Node* curr);
int _containsNode(struct Node* curr, TYPE val);
void _printInOrder(struct Node* curr);
void _freePostOrder(struct Node* curr);

/* END Binary Search Tree */

/* Misc */
void _miscPrintVal(struct Node* curr);
/* END Misc */

#endif