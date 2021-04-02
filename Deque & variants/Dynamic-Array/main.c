#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "interfaces.h"


int main(int argc, char const *argv[])
{
  struct Deque dq;
  struct Queue q;
  struct Stack s;
  FILE* file;
  const char* fileName;
  int val;
  int count;
  int quantity;

  if (argc == 2)
  {
    fileName = argv[1];
  }
  else
  {
    fileName = "input.txt";
  } 

  file = fopen(fileName,"r");

  printf("\n--------------------------------------------\n");

  printf("\nHello! I'm here to generate simple visualizations of some basic data structures:\n");
  printf("- Deques\n- Queues\n- Stacks\n\n");

  printf("Implemented as Dynamic Arrays.\n\n");

  printf("Press ENTER to continue.\n\n");
  getchar();

  /* --------------------------------------------
   *
   *                    DEQUE
   * 
   * --------------------------------------------
   */

  quantity = 25;

  printf("Here are some Deque operations:\n\n");

  initDeque(&dq);

  printf("- isEmpty: %d\n\n", isEmptyDeque(&dq));

  printf("- Adding values from %s...\n\n", fileName);

  while ( !feof(file) && (quantity > 0) )
  {
    fscanf(file, "%d", &val);

    addFrontDeque(&dq, val);

    quantity--;
  }

  printf("- isEmpty: %d\n\n", isEmptyDeque(&dq));

  printf("- Ready to print. Press ENTER.\n");
  getchar();

  printDeque(&dq);

  printf("\n");

  printf("- Link-front: { %d }\n", front(&dq));

  printf("- Link-back:  { %d }\n", back(&dq));

  printf("- Freeing Deque memory.\n");  

  freeDeque(&dq);

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
   * --------------------------------------------
   */

  quantity = 25;

  printf("\n");

  printf("Here are some Queue operations:\n\n");

  initQueue(&q);

  printf("- isEmpty: %d\n\n", isEmptyQueue(&q));

  printf("- Adding values from %s...\n\n", fileName);

  while ( !feof(file) && (quantity > 0) )
  {
    fscanf(file, "%d", &val);

    addQueue(&q, val);

    quantity--;
  }

  printf("- isEmpty: %d\n\n", isEmptyQueue(&q));

  printf("- Ready to print. Press ENTER.\n");  
  getchar();

  printQueue(&q);

  printf("\n");

  printf("- Link-front: { %d }\n", frontQueue(&q));

  printf("- Freeing Queue memory.\n");

  freeQueue(&q);

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
   * --------------------------------------------
   */

  count = 0;
  quantity = 25;

  printf("\n");

  printf("Here are some Stack operations:\n\n");

  initStack(&s);

  printf("- isEmpty: %d\n\n", isEmptyStack(&s));

  printf("- Adding values from %s...\n\n", fileName);

  while ( !feof(file) && (quantity > 0) )
  {
    fscanf(file, "%d", &val);

    pushStack(&s, val);

    quantity--;
  }

  printf("- isEmpty: %d\n\n", isEmptyStack(&s));

  printf("- Ready to print. Press ENTER.\n");  
  getchar();

  while ( !isEmptyStack(&s) )
  {
    count++;
    printf("- *POP* Link %d: { %d }\n", count, popStack(&s));
  }

  printf("\n");

  printf("- Freeing Stack memory.\n");

  freeStack(&s);

  /* --------------------------------------------
   *
   *                  END STACK
   * 
   * --------------------------------------------
   */

  printf("\n--------------------------------------------\n");

  fclose(file);
  
  return 0;
}
