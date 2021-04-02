#include "structs.h"

#ifndef __INTERFACES_H
#define __INTERFACES_H

/* HASHTABLE */
void initTable(hashTable* ht, int tableSize);
void freeTable(hashTable* ht);
void freeTableBody(hashLink** htb, int oldSize);
void insertTable(hashTable* ht, KeyType key, ValueType val);
void removeKey(hashTable* ht, KeyType key);
void printTable(hashTable* ht);
int containsKey(hashTable* ht, KeyType key);
int isEmptyTable(hashTable* ht);
int sizeTable(hashTable* ht);
int emptyBuckets(hashTable* ht);
float tableLoad(hashTable* ht);
struct hashLink* findLink(hashTable* ht, KeyType key);
void _resizeTable(hashTable* ht);
/* END HASHTABLE */

#endif