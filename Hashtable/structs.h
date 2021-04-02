# ifndef __STRUCTS_H
# define __STRUCTS_H

  # ifndef TYPE
  # define TYPE      int
  # define TYPE_SIZE sizeof(int)
  # define EQ(a,b) (a == b)
  # define LT(a,b) (a < b)
  # endif

  # ifndef HASHTABLE
  # define HASHTABLE

  # define KeyType char*
  # define ValueType int

  typedef struct hashLink
  {
    struct hashLink* next;

    KeyType key;
    ValueType val;
  } hashLink;

  typedef struct hashTable
  {
    hashLink** table;

    int tableSize;
    int count;
  } hashTable;

  #endif

  # ifndef BASIC_STRUCTS
  # define BASIC_STRUCTS

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

  #endif

#endif