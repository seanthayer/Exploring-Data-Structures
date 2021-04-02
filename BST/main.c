#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "interfaces.h"


int main(int argc, char const *argv[])
{
  struct BST bst;
  FILE* file;
  const char* fileName;
  int quantity;
  int val;

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
  printf("- BST\n\n");

  printf("Press ENTER to continue.\n\n");
  getchar();

  /* --------------------------------------------
   *
   *              Binary Search Tree
   * 
   * --------------------------------------------
   */

  quantity = 25;

  printf("Here are some BST operations:\n\n");

  initBST(&bst);

  printf("- isEmpty: %d\n\n", isEmptyBST(&bst));

  printf("- Adding values from %s...\n\n", fileName);

  while ( !feof(file) && (quantity > 0) )
  {
    fscanf(file, "%d", &val);

    addBST(&bst, val);

    quantity--;
  }

  printf("- isEmpty: %d\n\n", isEmptyBST(&bst));

  printf("- contains {747}?: %d\n\n", containsBST(&bst, 747));
  printf("- contains {199}?: %d\n\n", containsBST(&bst, 199));
  printf("- contains {500}?: %d\n\n", containsBST(&bst, 500));

  printf("- Ready to print. Press ENTER.\n");
  getchar();

  printBST(&bst);

  printf("\n- removing {747}\n\n");

  removeBST(&bst, 747);

  printf("- contains {747}?: %d\n", containsBST(&bst, 747));

  printf("\n");

  printf("- Freeing BST memory.\n");

  freeBST(&bst);

  /* --------------------------------------------
   *
   *           END Binary Search Tree
   * 
   * --------------------------------------------
   */

  printf("\n--------------------------------------------\n");

  fclose(file);
  
  return 0;
}
