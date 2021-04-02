#include "structs.h"

#ifndef __INTERFACES_H
#define __INTERFACES_H

/* DEQUE */
void initDeque(struct Deque* dq, int cap);
void freeDeque(struct Deque* dq);
void addFrontDeque(struct Deque* dq, TYPE val);
void addBackDeque(struct Deque* dq, TYPE val);
void printDeque(struct Deque* dq);
void removeFront(struct Deque* dq);
void removeBack(struct Deque* dq);
int isEmptyDeque(struct Deque* dq);
TYPE front(struct Deque* dq);
TYPE back(struct Deque* dq);
void _doubleCapacity(struct Deque* dq);
/* END DEQUE */


/* QUEUE */
void initQueue(struct Queue* q);
void freeQueue(struct Queue* q);
void addQueue(struct Queue* q, TYPE val);
void printQueue(struct Queue* q);
void removeQueue(struct Queue* q);
int isEmptyQueue(struct Queue* q);
TYPE frontQueue(struct Queue* q);
/* END QUEUE */

/* STACK */
void initStack(struct Stack* s);
void freeStack(struct Stack* s);
int isEmptyStack(struct Stack* s);
void pushStack(struct Stack* s, TYPE val);
TYPE popStack(struct Stack* s);
TYPE peepStack(struct Stack* s);
/* END STACK */

#endif