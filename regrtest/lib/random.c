/**
* @file   random.c
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  implements the functions for generating random values
*/

#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <limits.h>

#define PRINT_CHAR_RANGE        94
#define PRINT_CHAR_OFFSET       33


/* integer random generator */
unsigned int randomi(int *value) {
  struct timeval tv;     // time value

  if(gettimeofday(&tv, NULL)==0) {
    unsigned int usec = (unsigned int)(tv.tv_usec);
    srand(usec);
    *value = rand() % INT_MAX;
    return 0;
  }
  return 1;
}


/* ignoring the character '!' */
char *randoms(int length) {
  int i;
  struct timeval tv;     // time value
  char *string = (char *)malloc(length * sizeof(char));

  for(i=0; i<length-1; ++i) {
    if(gettimeofday(&tv, NULL)==0) {
      unsigned int usec = (unsigned int)(tv.tv_usec);
      srand(usec);
      string[i] = (rand() % PRINT_CHAR_RANGE) + PRINT_CHAR_OFFSET;
    }
  }

  string[i] = '\0';

  return string;
}
