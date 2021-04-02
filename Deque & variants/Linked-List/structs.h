#ifndef __STRUCTS_H
#define __STRUCTS_H

# ifndef TYPE
# define TYPE      int
# define TYPE_SIZE sizeof(int)
# endif

struct Link
{
  struct Link* next;
  TYPE val;
};

struct DLink
{
  struct DLink* next;
  struct DLink* prev;

  TYPE val;
};

struct Deque
{
  struct DLink* head;
  struct DLink* tail;

  int size;
};

struct Queue
{
  struct Link* head;
  struct Link* tail;

  int size;
};

struct Stack
{
  struct Link* head;
  int size;
};

#endif