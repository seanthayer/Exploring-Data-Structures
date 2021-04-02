#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "structs.h"
#include "interfaces.h"

/* The Deque interfaces are implemented assuming double links are the base data structure. */
/* --------------------------------------------
 *
 *                    DEQUE
 * 
 * Foundation used:   Double-Link
 * 
 * Sentinels:         Front & Back sentinels
 * 
 * --------------------------------------------
 */

void initDeque(struct Deque* dq)
{
  /*  Description:
   *    Function initializes a Deque structure using a pointer to its memory address.
   *    The function allocates memory for two initial Double-Links, the front & back sentinels.
   *    The sentinels initially point to each-other, and elements are added between, maintaining
   *    correct linkages.
   *    
   *  Parameters:
   *    [struct] (Deque*) dq: A pointer to the Deque.
   * 
   *  Pre-conditions:
   *    - Pointer 'dq' points to a proper memory location.
   *    - There is memory available to allocate.
   * 
   *  Post-conditions:
   *    - The Deque is initialized: the size is 0, both sentinels are created, and linkages are correct. 
   */

  struct DLink* senFront;
  struct DLink* senBack;

  assert(dq);

  dq->size = 0;

  senFront = (struct DLink*) malloc(sizeof(struct DLink));
  senBack = (struct DLink*) malloc(sizeof(struct DLink));

  assert(senFront);
  assert(senBack);

  dq->head = senFront;
  dq->tail = senBack;

  dq->head->next = dq->tail;
  dq->tail->prev = dq->head;

  dq->head->prev = NULL;
  dq->tail->next = NULL;
}

void freeDeque(struct Deque* dq)
{
  /*  Description:
   *    Function frees all allocated memory associated with the Deque, such as the sentinels and Double-Links.
   *    
   *  Parameters:
   *    [struct] (Deque*) dq: A pointer to the Deque.
   * 
   *  Pre-conditions:
   *    - Pointer 'dq' points to a proper memory location.
   *    - The Deque was initialized correctly.
   * 
   *  Post-conditions:
   *    - The Deque's memory is freed.
   */

  struct DLink* curr, * temp;

  assert(dq);

  curr = dq->head;

  while (curr)
  {
    temp = curr;

    curr = curr->next;

    free(temp);
  }

}

void addFrontDeque(struct Deque* dq, TYPE val)
{
  /*  Description:
   *    Function allocates memory for a Double-Link with the given value and adds it to the front of the Deque.
   *    
   *  Parameters:
   *    [struct]  (Deque*)  dq  : A pointer to the Deque.
   *    [TYPE]              val : The value to insert.
   * 
   *  Pre-conditions:
   *    - Pointer 'dq' points to a proper memory location.
   *    - The Deque was initialized correctly.
   * 
   *  Post-conditions:
   *    - A Double-Link with the given value is inserted after the front sentinel, and correct linkages are maintained.
   */

  struct DLink* dLink;

  assert(dq);

  dLink = (struct DLink*) malloc(sizeof(struct DLink));

  assert(dLink);

  dLink->val = val;
  dLink->next = dq->head->next;
  dLink->prev = dq->head;
  
  dLink->next->prev = dLink;
  dq->head->next = dLink;

  dq->size++;
}

void addBackDeque(struct Deque* dq, TYPE val)
{
  /*  Description:
   *    Function allocates memory for a Double-Link with the given value and adds it to the back of the Deque.
   *    
   *  Parameters:
   *    [struct]  (Deque*)  dq  : A pointer to the Deque.
   *    [TYPE]              val : The value to insert.
   * 
   *  Pre-conditions:
   *    - Pointer 'dq' points to a proper memory location.
   *    - The Deque was initialized correctly.
   * 
   *  Post-conditions:
   *    - A Double-Link with the given value is inserted before the back sentinel, and correct linkages are maintained.
   */

  struct DLink* dLink;

  assert(dq);

  dLink = (struct DLink*) malloc(sizeof(struct DLink));

  assert(dLink);

  dLink->val = val;
  dLink->next = dq->tail;
  dLink->prev = dq->tail->prev;
  
  dLink->prev->next = dLink;
  dq->tail->prev = dLink;

  dq->size++;
}

void printDeque(struct Deque* dq)
{
  /*  Description:
   *    Function iterates through the Deque, starting at the front, and prints each corresponding value.
   *    (Assuming an integer value.)
   *    
   *  Parameters:
   *    [struct]  (Deque*)  dq  : A pointer to the Deque.
   * 
   *  Pre-conditions:
   *    - Pointer 'dq' points to a proper memory location.
   *    - The Deque was initialized correctly.
   * 
   *  Post-conditions:
   *    - The Deque's values are printed to stdout.
   */

  int count = 0;
  struct DLink* curr;

  assert(dq);

  printf("Front to Back:\n\n");

  curr = dq->head->next;

  while (curr && (curr != dq->tail))
  {
    count++;

    printf("- Link %d: { %d }\n", count, curr->val);

    curr = curr->next;
  }

  /*
  printf("\nBack to Front:\n\n");

  curr = dq->tail->prev;

  while (curr && (curr != dq->head))
  {
    printf("- Link %d: { %d }\n", count, curr->val);

    curr = curr->prev;

    count--;
  }
  */
 
}

void removeFront(struct Deque* dq)
{
  /*  Description:
   *    Function unlinks the Double-Link at the front of the Deque and frees its memory.
   *    
   *  Parameters:
   *    [struct]  (Deque*)  dq  : A pointer to the Deque.
   * 
   *  Pre-conditions:
   *    - Pointer 'dq' points to a proper memory location.
   *    - The Deque was initialized correctly.
   * 
   *  Post-conditions:
   *    - The Double-Link at the front of the Deque is unlinked and has its memory freed.
   */

  struct DLink* rmv;

  assert(dq);

  if ( isEmptyDeque(dq) )
  {
    return;
  }
  else
  {
    rmv = dq->head->next;

    dq->head->next = rmv->next;
    rmv->next->prev = dq->head;

    free(rmv);

    dq->size--;
  }
    
}

void removeBack(struct Deque* dq)
{
  /*  Description:
   *    Function unlinks the Double-Link at the back of the Deque and frees its memory.
   *    
   *  Parameters:
   *    [struct]  (Deque*)  dq  : A pointer to the Deque.
   * 
   *  Pre-conditions:
   *    - Pointer 'dq' points to a proper memory location.
   *    - The Deque was initialized correctly.
   * 
   *  Post-conditions:
   *    - The Double-Link at the back of the Deque is unlinked and has its memory freed.
   */

  struct DLink* rmv;

  assert(dq);

  if ( isEmptyDeque(dq) )
  {
    return;
  }
  else
  {
    rmv = dq->tail->prev;

    dq->tail->prev = rmv->prev;
    rmv->prev->next = dq->tail;

    free(rmv);

    dq->size--;
  }

}

int isEmptyDeque(struct Deque* dq)
{
  /*  Description:
   *    Function checks the Deque's size and returns true or false.
   *    
   *  Parameters:
   *    [struct]  (Deque*)  dq  : A pointer to the Deque.
   * 
   *  Returns:
   *    [int]     (1 || 0): True or False, if the structure is empty or not.
   * 
   *  Pre-conditions:
   *    - Pointer 'dq' points to a proper memory location.
   *    - The Deque was initialized correctly.
   * 
   *  Post-conditions:
   *    - True (1) or False (0) is returned.
   */

  assert(dq);

  if (dq->size == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }

}

TYPE front(struct Deque* dq)
{
  /*  Description:
   *    Function accesses the value at the front of the Deque and returns it.
   *    
   *  Parameters:
   *    [struct]  (Deque*)  dq  : A pointer to the Deque.
   * 
   *  Returns:
   *    [TYPE]    returnVal:      The value at the front of the Deque.
   * 
   *  Pre-conditions:
   *    - Pointer 'dq' points to a proper memory location.
   *    - The Deque was initialized correctly.
   * 
   *  Post-conditions:
   *    - The Deque's front element value is returned, or NULL if Deque is empty.
   */

  TYPE returnVal = NULL;

  assert(dq);

  if ( isEmptyDeque(dq) )
  {
    return returnVal;
  }
  else
  {
    returnVal = (TYPE) dq->head->next->val;

    return returnVal;
  }

}

TYPE back(struct Deque* dq)
{
  /*  Description:
   *    Function accesses the value at the back of the Deque and returns it.
   *    
   *  Parameters:
   *    [struct]  (Deque*)  dq  : A pointer to the Deque.
   * 
   *  Returns:
   *    [TYPE]    returnVal:      The value at the back of the Deque.
   * 
   *  Pre-conditions:
   *    - Pointer 'dq' points to a proper memory location.
   *    - The Deque was initialized correctly.
   * 
   *  Post-conditions:
   *    - The Deque's back element value is returned, or NULL if empty.
   */

  TYPE returnVal = NULL;

  assert(dq);

  if ( isEmptyDeque(dq) )
  {
    return returnVal;
  }
  else
  {
    returnVal = (TYPE) dq->tail->prev->val;

    return returnVal;
  }

}

/* --------------------------------------------
 *
 *                  END DEQUE
 * 
 * --------------------------------------------
 */

/*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*/

/* --------------------------------------------
 *
 *                   QUEUE
 * 
 * Foundation used:   Single-Link
 * 
 * Sentinels:         Front sentinel
 * 
 * --------------------------------------------
 */

void initQueue(struct Queue* q)
{
  /*  Description:
   *    Function initializes a Queue structure using a pointer to its memory address.
   *    The function allocates memory for one initial Single-Link, the front sentinel.
   *    The sentinel initially points to NULL, and elements are appended to the end of the Queue, maintaining
   *    correct linkages.
   *    
   *  Parameters:
   *    [struct] (Queue*) q: A pointer to the Queue.
   * 
   *  Pre-conditions:
   *    - Pointer 'q' points to a proper memory location.
   *    - There is memory available to allocate.
   * 
   *  Post-conditions:
   *    - The Queue is initialized: the size is 0, the front sentinel is created, and linkages are correct. 
   */

  struct Link* senFront;

  assert(q);

  q->size = 0;

  senFront = (struct Link*) malloc(sizeof(struct Link));

  assert(senFront);

  senFront->next = NULL;

  q->head = senFront;
  q->tail = senFront;
}

void freeQueue(struct Queue* q)
{
  /*  Description:
   *    Function frees all allocated memory associated with the Queue, such as the front sentinel and Single-Links.
   *    
   *  Parameters:
   *    [struct] (Queue*) q: A pointer to the Queue.
   * 
   *  Pre-conditions:
   *    - Pointer 'q' points to a proper memory location.
   *    - The Queue was initialized correctly.
   * 
   *  Post-conditions:
   *    - The Queue's memory is freed.
   */

  struct Link* curr, * temp;

  assert(q);

  curr = q->head;

  while (curr)
  {
    temp = curr;

    curr = curr->next;

    free(temp);
  }

}

void addQueue(struct Queue* q, TYPE val)
{
  /*  Description:
   *    Function allocates memory for a Single-Link with the given value and appends it to the end of the Queue.
   *    
   *  Parameters:
   *    [struct]  (Queue*)  q   : A pointer to the Queue.
   *    [TYPE]              val : The value to insert.
   * 
   *  Pre-conditions:
   *    - Pointer 'q' points to a proper memory location.
   *    - The Queue was initialized correctly.
   * 
   *  Post-conditions:
   *    - A Single-Link with the given value is inserted after the tail link, and correct linkages are maintained.
   */

  struct Link* link;

  assert(q);

  link = (struct Link*) malloc(sizeof(struct Link));

  assert(link);

  link->val = val;
  link->next = NULL;

  q->tail->next = link;
  q->tail = link;

  q->size++;
}

void printQueue(struct Queue* q)
{
  /*  Description:
   *    Function iterates through the Queue, starting at the front, and prints each corresponding value.
   *    (Assuming an integer value.)
   *    
   *  Parameters:
   *    [struct]  (Queue*)  q   : A pointer to the Queue.
   * 
   *  Pre-conditions:
   *    - Pointer 'q' points to a proper memory location.
   *    - The Queue was initialized correctly.
   * 
   *  Post-conditions:
   *    - The Queue's values are printed to stdout.
   */
  
  struct Link* curr;
  int count = 0;

  assert(q);

  printf("Front to Back:\n\n");

  curr = q->head->next;

  while (curr)
  {
    count++;

    printf("- Link %d: { %d }\n", count, curr->val);

    curr = curr->next;
  }
  
}

void removeQueue(struct Queue* q)
{
  /*  Description:
   *    Function unlinks the Single-Link at the front of the Queue and frees its memory.
   *    
   *  Parameters:
   *    [struct]  (Queue*)  q   : A pointer to the Queue.
   * 
   *  Pre-conditions:
   *    - Pointer 'q' points to a proper memory location.
   *    - The Queue was initialized correctly.
   * 
   *  Post-conditions:
   *    - The Single-Link at the front of the Queue is unlinked and has its memory freed.
   *      Correct linkages are maintained.
   */

  struct Link* curr;

  assert(q);

  if ( isEmptyQueue(q) )
  {
    return;
  }
  else
  {
    curr = q->head->next;

    q->head->next = curr->next;

    if (curr == q->tail)
      q->tail = q->head;

    free(curr);

    q->size--;
  }
  
}

int isEmptyQueue(struct Queue* q)
{
  /*  Description:
   *    Function checks the Queue's size and returns true or false.
   *    
   *  Parameters:
   *    [struct]  (Queue*)  q   : A pointer to the Queue.
   * 
   *  Returns:
   *    [int]     (1 || 0): True or False, if the structure is empty or not.
   * 
   *  Pre-conditions:
   *    - Pointer 'dq' points to a proper memory location.
   *    - The Deque was initialized correctly.
   * 
   *  Post-conditions:
   *    - True (1) or False (0) is returned.
   */

  assert(q);

  if (q->size == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }

}

TYPE frontQueue(struct Queue* q)
{
  /*  Description:
   *    Function accesses the value at the front of the Queue and returns it.
   *    
   *  Parameters:
   *    [struct]  (Queue*)  q   : A pointer to the Queue.
   * 
   *  Returns:
   *    [TYPE]    returnVal:      The value at the front of the Queue.
   * 
   *  Pre-conditions:
   *    - Pointer 'q' points to a proper memory location.
   *    - The Queue was initialized correctly.
   * 
   *  Post-conditions:
   *    - The Queue's front element value is returned, or NULL if Queue is empty.
   */

  TYPE returnVal = NULL;

  assert(q);

  if ( isEmptyQueue(q) )
  {
    return returnVal;
  }
  else
  {
    returnVal = (TYPE) q->head->next->val;

    return returnVal;
  }

}

/* --------------------------------------------
 *
 *                  END QUEUE
 * 
 * --------------------------------------------
 */

/*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*/

/* --------------------------------------------
 *
 *                    STACK
 * 
 * Foundation used:   Single-Link
 * 
 * --------------------------------------------
 */

void initStack(struct Stack* s)
{
  /*  Description:
   *    Function initializes a Stack structure using a pointer to its memory address.
   *    The function does not allocate additional memory upon initialization, as this Stack structure
   *    implementation does not use a sentinel. Simply having a pointer to 'head' element is sufficient.
   *    
   *  Parameters:
   *    [struct] (Stack*) s: A pointer to the Stack.
   * 
   *  Pre-conditions:
   *    - Pointer 's' points to a proper memory location.
   * 
   *  Post-conditions:
   *    - The Stack is initialized: the size is 0, and the 'head' points to NULL. 
   */

  assert(s);

  s->size = 0;

  s->head = NULL;
}

void freeStack(struct Stack* s)
{
  /*  Description:
   *    Function frees all allocated memory associated with the Stack, the Single-Link entries (if any exist).
   *    
   *  Parameters:
   *    [struct] (Stack*) s : A pointer to the Stack.
   * 
   *  Pre-conditions:
   *    - Pointer 's' points to a proper memory location.
   *    - The Stack was initialized correctly.
   * 
   *  Post-conditions:
   *    - The Stack's memory is freed.
   */
  assert(s);

  while ( !isEmptyStack(s) )
  {
    popStack(s);
  }
  
}

int isEmptyStack(struct Stack* s)
{
  /*  Description:
   *    Function checks the Stack's size and returns true or false.
   *    
   *  Parameters:
   *    [struct]  (Stack*)  s   : A pointer to the Stack.
   * 
   *  Returns:
   *    [int]     (1 || 0): True or False, if the structure is empty or not.
   * 
   *  Pre-conditions:
   *    - Pointer 's' points to a proper memory location.
   *    - The Stack was initialized correctly.
   * 
   *  Post-conditions:
   *    - True (1) or False (0) is returned.
   */

  assert(s);

  if (s->size == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
  
}

void pushStack(struct Stack* s, TYPE val)
{
  /*  Description:
   *    Function allocates memory for a Single-Link with the given value and pushes on top of the Stack.
   *    
   *  Parameters:
   *    [struct]  (Stack*)  s   : A pointer to the Stack.
   *    [TYPE]              val : The value to insert.
   * 
   *  Pre-conditions:
   *    - Pointer 's' points to a proper memory location.
   *    - The Stack was initialized correctly.
   * 
   *  Post-conditions:
   *    - A Single-Link with the given value is inserted on the head of the Stack, and correct linkages are maintained.
   */

  struct Link* link;

  assert(s);

  link = (struct Link*) malloc(sizeof(struct Link));

  link->val = val;
  link->next = s->head;

  s->head = link;

  s->size++;
}

TYPE popStack(struct Stack* s)
{
  /*  Description:
   *    Function accesses the value on the top of the Stack, frees the Single-Link, and returns the value.
   *    
   *  Parameters:
   *    [struct]  (Stack*)  s: A pointer to the Stack.
   * 
   *  Returns:
   *    [TYPE]      returnVal: The value on the top of the Stack.
   * 
   *  Pre-conditions:
   *    - Pointer 's' points to a proper memory location.
   *    - The Stack was initialized correctly.
   * 
   *  Post-conditions:
   *    - The Stack's top element is unlinked and freed; 'head' is moved to next element.
   *    - The Stack's top element value is returned, or NULL if Stack is empty.
   */

  struct Link* pop;
  TYPE returnVal = NULL;

  assert(s);

  if ( isEmptyStack(s) )
  {
    return returnVal;
  }
  else
  {
    pop = s->head;

    returnVal = (TYPE) pop->val;

    s->head = pop->next;

    free(pop);

    s->size--;

    return returnVal;
  }
  
}

TYPE peepStack(struct Stack* s)
{
  /*  Description:
   *    Function accesses the value on the top of the Stack and returns the value.
   *    
   *  Parameters:
   *    [struct]  (Stack*)  s   : A pointer to the Stack.
   * 
   *  Returns:
   *    [TYPE]    returnVal:      The value on the top of the Stack.
   * 
   *  Pre-conditions:
   *    - Pointer 's' points to a proper memory location.
   *    - The Stack was initialized correctly.
   * 
   *  Post-conditions:
   *    - The Stack's top element value is returned, or NULL if Stack is empty.
   */

  TYPE returnVal = NULL;

  assert(s);

  if ( isEmptyStack(s) )
  {
    return returnVal;
  }
  else
  {
    returnVal = s->head->val;

    return returnVal;
  }
  
}

/* --------------------------------------------
 *
 *                  END STACK
 * 
 * --------------------------------------------
 */