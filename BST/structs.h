#ifndef __STRUCTS_H
#define __STRUCTS_H

# ifndef TYPE
# define TYPE      int
# define TYPE_SIZE sizeof(int)
# define EQ(a,b) (a == b)
# define LT(a,b) (a < b)
# endif

struct BST
{
  struct Node* root;
  int size;
};

struct Node
{
  struct Node* left;
  struct Node* right;

  TYPE val;
};

#endif