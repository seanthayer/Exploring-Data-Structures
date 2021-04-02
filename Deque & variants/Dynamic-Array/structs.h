#ifndef __STRUCTS_H
#define __STRUCTS_H

# ifndef TYPE
# define TYPE      int
# define TYPE_SIZE sizeof(int)
# define EQ(a,b) (a == b)
# define LT(a,b) (a < b) 
# endif

# ifndef DYN_ARR
# define DYN_ARR

typedef struct DynArr
{
	TYPE* data;

	int size;
	int capacity;
} DynArr;

# endif

# ifndef BASIC_STRUCTS
# define BASIC_STRUCTS

struct Deque
{
  TYPE* data;

  int size;
  int capacity;
  int front;
};

#endif

#endif