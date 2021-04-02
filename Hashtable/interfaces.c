#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "structs.h"
#include "interfaces.h"

int stringHash(char* str)
{

  /* DJB HASH */

  int hash = 5381;
  int c;

  while ( (c = *str++) )
  {
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}

void initTable (hashTable* ht, int tableSize)
{
  int index;

  assert(ht);

  ht->table = (hashLink**) malloc(sizeof(hashLink*) * tableSize);
  ht->tableSize = tableSize;
  ht->count = 0;

  for(index = 0; index < tableSize; index++)
    ht->table[index] = NULL;
  
}

void freeTable(hashTable* ht)
{
  int i;
  int cap;
  hashLink* htLink;
  hashLink* htLinkNxt;
  hashLink* temp;

  assert(ht);

  cap = ht->tableSize;

  for (i = 0; i < cap; i++)
  {

    if (ht->table[i])
    {
      htLink = ht->table[i];
      htLinkNxt = htLink->next;

      while (htLinkNxt)
      {
        temp = htLinkNxt;
        htLinkNxt = htLinkNxt->next;

        free(temp->key);
        free(temp);
      }

      free(htLink->key);
      free(htLink);
    }

  }

  free(ht->table);
}

void freeTableBody(hashLink** htb, int oldSize)
{
  int i;
  struct hashLink* htLink;
  struct hashLink* htLinkNxt;
  struct hashLink* temp;

  assert(htb);

  for (i = 0; i < oldSize; i++)
  {

    if (htb[i])
    {
      htLink = htb[i];
      htLinkNxt = htLink->next;

      while (htLinkNxt)
      {
        temp = htLinkNxt;
        htLinkNxt = htLinkNxt->next;

        free(temp);
      }

      free(htLink);
    }

  }

  free(htb);
}

void insertTable(hashTable* ht, KeyType key, ValueType val)
{
  int index;
  hashLink* htLink;

  htLink = (hashLink*)malloc(sizeof(hashLink));

  assert(htLink);

  htLink->key = key;
  htLink->val = val;

  index = (int)(labs( stringHash(key) ) % ht->tableSize);

  htLink->next = ht->table[index];

  ht->table[index] = htLink;

  ht->count++;
}

void removeKey(hashTable* ht, KeyType key)
{
  int index;
  int htKeyHash;
  int paramKeyHash;
  hashLink* htLink;
  hashLink* htLinkNxt;
  hashLink* prev;

  assert(ht);

  index = (int)(labs( stringHash(key) ) % ht->tableSize);
  paramKeyHash = stringHash(key);

  if (ht->table[index])
  {
    htLink = ht->table[index];
    htKeyHash = stringHash(htLink->key);

    if ( EQ(htKeyHash, paramKeyHash) )
    {
      /* Found key at front index */
      ht->table[index] = htLink->next;
      
      free(htLink->key);
      free(htLink);

      ht->count--;
    }
    else
    {
      prev = htLink;
      htLinkNxt = htLink->next;

      while (htLinkNxt)
      {
        htKeyHash = stringHash(htLinkNxt->key);

        if ( EQ(htKeyHash, paramKeyHash) )
        {
          prev->next = htLinkNxt->next;

          free(htLinkNxt->key);
          free(htLinkNxt);

          htLinkNxt = NULL;

          ht->count--;
        }
        else
        {
          prev = htLinkNxt;
          htLinkNxt = htLinkNxt->next;
        }

      }

    }

  }

}

void printTable(hashTable* ht)
{
  int i;
  struct hashLink* htLink;
  struct hashLink* htLinkNxt;
  struct hashLink* temp;

  assert(ht);

  for (i = 0; i < ht->tableSize; i++)
  {

    if (ht->table[i])
    {
      htLink = ht->table[i];
      htLinkNxt = htLink->next;

      printf("%s: %d\n\n", htLink->key, htLink->val);

      while (htLinkNxt)
      {
        temp = htLinkNxt;
        htLinkNxt = htLinkNxt->next;

        printf("%s: %d\n\n", temp->key, temp->val);
      }

    }

  }

}

int containsKey(hashTable* ht, KeyType key)
{
  int index;
  int htKeyHash;
  int paramKeyHash;
  hashLink* htLink;
  hashLink* htLinkNxt;

  assert(ht);

  index = (int)(labs( stringHash(key) ) % ht->tableSize);
  paramKeyHash = stringHash(key);

  if (ht->table[index])
  {
    htLink = ht->table[index];
    htKeyHash = stringHash(htLink->key);

    if ( EQ(htKeyHash, paramKeyHash) )
    {
      return 1;
    }
    else
    {
      htLinkNxt = htLink->next;

      while (htLinkNxt)
      {
        htKeyHash = stringHash(htLinkNxt->key);

        if ( EQ(htKeyHash, paramKeyHash) )
        {
          return 1;
        }
        else
        {
          htLinkNxt = htLinkNxt->next;
        }

      }

    }

    return 0;
  }
  else
  {
    return 0;
  }

}

int isEmptyTable(hashTable* ht)
{
  assert(ht);

  if (ht->count == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }

}

int sizeTable(hashTable* ht)
{
  int i;
  int cap;
  int count;
  hashLink* htLink;
  hashLink* htLinkNxt;

  assert(ht);

  i = 0;
  cap = ht->tableSize;
  count = 0;

  for (i = 0; i < cap; i++)
  {

    if (ht->table[i])
    {
      count++;

      htLink = ht->table[i];
      htLinkNxt = htLink->next;

      while (htLinkNxt)
      {
        count++;
        htLinkNxt = htLinkNxt->next;
      }

    }

  }

  return count;
}

int emptyBuckets(hashTable* ht)
{
  int i;
  int cap;
  int count;

  assert(ht);

  i = 0;
  cap = ht->tableSize;
  count = 0;

  for (i = 0; i < cap; i++)
  {

    if (!ht->table[i])
      count++;

  }

  return count;
}

float tableLoad(hashTable* ht)
{
  int   elements  = ht->count;
  int   tsize     = ht->tableSize;
  float load      = ((float)elements / (float)tsize);

  return load;
}

struct hashLink* findLink(hashTable* ht, KeyType key)
{
  int index;
  int htKeyHash;
  int paramKeyHash;
  struct hashLink* htLink;
  struct hashLink* htLinkNxt;

  assert(ht);

  index = (int)(labs( stringHash(key) ) % ht->tableSize);
  paramKeyHash = stringHash(key);

  if (ht->table[index])
  {
    htLink = ht->table[index];
    htKeyHash = stringHash(htLink->key);

    if ( EQ(htKeyHash, paramKeyHash) )
    {
      return htLink;
    }
    else
    {
      htLinkNxt = htLink->next;

      while (htLinkNxt)
      {
        htKeyHash = stringHash(htLinkNxt->key);

        if ( EQ(htKeyHash, paramKeyHash) )
        {
          return htLinkNxt;
        }
        else
        {
          htLinkNxt = htLinkNxt->next;
        }

      }

    }

    return NULL;
  }
  else
  {
  return NULL;
  }

}

void _resizeTable(hashTable* ht)
{
  int i;
  int oldSize = ht->tableSize;
  hashLink** oldTable = ht->table;
  hashLink* curr;

  assert(ht);

  initTable(ht, 2 * oldSize);

  for (i = 0; i < oldSize; i++)
  {
    curr = oldTable[i];

    while (curr != NULL)
    {
      insertTable(ht, curr->key, curr->val);

      curr = curr->next;
    }

  }

  freeTableBody(oldTable, oldSize);
}