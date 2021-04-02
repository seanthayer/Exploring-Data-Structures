#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "structs.h"
#include "interfaces.h"


char* getWord(FILE *file); /* getWord function referenced from Professor Sinisa Todorovic */

/*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*/

int main(int argc, char const *argv[])
{
  hashTable ht;
  hashLink* htLink;
  FILE* file;

  const char* fileName;
  char* word;

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
  printf("- Hashtable\n\n");

  printf("Press ENTER to continue.\n\n");
  getchar();

  /* --------------------------------------------
   *
   *                  HASHTABLE
   * 
   * --------------------------------------------
   */

  printf("Here are some Hashtable operations:\n\n");

  initTable(&ht, 30);

  printf("- isEmpty: %d\n\n", isEmptyTable(&ht));

  printf("- Adding values from %s...\n\n", fileName);

  do
  {
    word = getWord(file);

    if (word)
    {

      if ( containsKey(&ht, word) )
      {

        htLink = findLink(&ht, word);

        htLink->val++;

        free(word);

      }
      else
      {

        insertTable(&ht, word, 1);

        if (tableLoad(&ht) > 1)
          _resizeTable(&ht);

      }

    }

  } while (word);

  printf("- isEmpty: %d\n\n", isEmptyTable(&ht));

  printf("- Ready to print. Press ENTER.\n");
  getchar();

  printTable(&ht);

  printf("- Contains key {\"the\"}?: %d\n\n", containsKey(&ht, "the"));

  printf("- Removing key {\"the\"}\n\n");

  removeKey(&ht, "the");

  printf("- Contains key {\"the\"}?: %d\n\n", containsKey(&ht, "the"));

  printf("- Book-kept element count:  %d\n", ht.count);
  printf("- Calculated element count: %d\n\n", sizeTable(&ht));

  printf("- Empty buckets:  %d\n", emptyBuckets(&ht));
  printf("- Table load:     %f\n", tableLoad(&ht));

  printf("\n");

  printf("- Freeing Hashtable memory.\n");  

  freeTable(&ht);

  /* --------------------------------------------
   *
   *                END HASHTABLE
   * 
   * --------------------------------------------
   */

  printf("\n--------------------------------------------\n");

  fclose(file);
  
  return 0;
}

/*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*/

char* getWord(FILE *file)
{
  
  int length = 0;
  int maxLength = 16;
  char character;
    
  char* word = (char*)malloc(sizeof(char) * maxLength);
  assert(word != NULL);
    
  while( (character = fgetc(file)) != EOF)
  {
    if((length+1) > maxLength)
    {
      maxLength *= 2;
      word = (char*)realloc(word, maxLength);
    }
    if((character >= '0' && character <= '9') || /*is a number*/
       (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
       (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
       character == 39) /*or is an apostrophy*/
    {
      word[length] = character;
      length++;
    }
    else if(length > 0)
      break;
  }
    
  if(length == 0)
  {
    free(word);
    return NULL;
  }
  word[length] = '\0';
  return word;
}
