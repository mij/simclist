/**
* @file   helpers.c
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  implements the function used for setting list attributes
*/

#include "helpers.h"

/* size of the element-type */
size_t int_size(const void *el) {
  return sizeof(int);
}

/* element comparator for int type */
int list_comparator_int(const void *a, const void *b) {
  return ( *(int *)a < *(int *)b) - (*(int *)a > *(int *)b);
}

/* element seeker for int number_s/subnumber_s */
int number_t_seeker(const void *el, const void *value) {
  // let's check that the number stored in the element
  // is the same es the value and that the sub number is the
  // negation of the number iteslf
  subnumber_t subnum;
  const number_t *num = (number_t *)el;
  int *v = (int *)value;

  if(num != (void *)0 && v != (void *)0) {
    subnum = num->snumber;
    if(*v == num->number && subnum.number == (*v) * -1) return 1;
  }

  return 0;
}
