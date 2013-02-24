/**
* @file   tier1_testc.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  implementation of the third test suite of the Tier1
*/

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include "../../simclist.h"
#include "../lib/random.h"
#include "../lib/helpers.h"
#include "tier1_testc.h"

/* compare helper function */
int int_bigger_than(const void *a, const void *b);

/* implementation Test C */
void testc_check(size_t const n) {
  int valuesa[n], valuesb[n];
  list_t lista, listb, dest;
  int *el;
  int i;
  int max, min, ret;

  // --------------
  // INITIALIZATION
  // set also the comparator and the meter attributes
  // needed later on for checking the functionalities
  // --------------
  ret = list_init(&lista);
  assert(ret == 0 && "list initialization fails");
  ret = list_init(&listb);
  assert(ret == 0 && "list initialization fails");

  // set the comparator attribute
  ret = list_attributes_comparator(&lista, int_bigger_than);
  assert(ret == 0 && "setting attribute comparator fails");
  ret = list_attributes_comparator(&listb, int_bigger_than);
  assert(ret == 0 && "setting attribute comparator fails");

  // set list_attribute_copy for creating new memory areas 
  // and check the correctness of execution.
  ret = list_attributes_copy(&lista, int_size, 1);
  assert(ret == 0 && "setting attribute copy fails");

  // ---------
  // EMPTINESS
  // check if the list is empty
  // ---------
  assert(list_empty(&lista) != 0 && "empty check fails");

  // ----------
  // MIN && MAX
  // the lista is also populated while storing
  // the max value
  // ----------

  max = INT_MIN;
  min = INT_MAX;

  // populate the list and check the value added in the list
  // while doing this store also the maximum and the minimum
  for(i=0; i<n; ++i) {
    randomi(&valuesa[i]);
    ret = list_insert_at(&lista, &valuesa[i], i);
    assert(ret > 0 && "element insertion fails");
    el = (int *)list_get_at(&lista, i);
    assert(valuesa[i] == *el && "retrieved value has wrong value");

    if(max < *el) max = *el;

    if(min > *el) min = *el;
  }

  // check the minimum
  if((int *)list_get_min(&lista) != NULL)
    assert(min == *(int *)list_get_min(&lista) && "minimum value is wrong");

  // check the maximum
  if((int *)list_get_min(&lista) != NULL)
    assert(max == *(int *)list_get_max(&lista) && "maximum value is wrong");

  // ---------
  // ITERATORS
  // ---------

  // check the elements using the iterators
  list_iterator_start(&lista);
  for(i=0; i<n && list_iterator_hasnext(&lista); ++i) {
    assert(valuesa[i] == *(int*)list_iterator_next(&lista)
           && "next iterator fails");
  }
  assert(n==list_size(&lista) && "list size is wrong");
  assert(!list_iterator_hasnext(&lista) && "has next iterator fails");

  list_iterator_stop(&lista);

  // ------
  // CONCAT
  // The concatenation is performed using the same list.
  // The concat is stored in the dest list.
  // ------

  // populate the second list
  for(i=0; i<n; ++i) {
    randomi(&valuesb[i]);
    ret = list_insert_at(&listb, &valuesb[i], i);
    assert(ret > 0 && "element insertion fails");
  }

  // concatenate the lista with itself
  ret = list_concat(&lista, &lista, &dest);
  assert(ret == 0 && "concatenation fails");
  assert(2*n == list_size(&dest) && "list size is wrong");

  for(i=0; i<2*n; ++i) {
    assert(valuesa[i % n] == *(int *)list_get_at(&dest, i)
           && "retrieved value has wrong value");
  }

  // ------------
  // DELETE RANGE
  // deleting the second half of the destination list and then
  // deleting the first half of it.
  // ------------
  if(list_size(&dest) != 0) {
    ret = list_delete_range(&dest, n, 2*n-1);
    assert(ret == (2*n-1 - n + 1) && "number of elements deleted is wrong");
    assert(list_size(&dest) == n && "list size is wrong");

    ret = list_delete_range(&dest, 0, n-1);
    assert(ret == n && "number of elements deleted is wrong");
    assert(list_size(&dest) == 0 && "list size is wrong");
  }

  // ------
  // CONCAT
  // The concatenation is performed using lista and listb.
  // The concat is stored in the dest list.
  // ------

  // concatenate the lista with listb
  ret = list_concat(&lista, &listb, &dest);
  assert(ret == 0 && "concatenation fails");
  assert(2*n == list_size(&dest) && "list size is wrong");

  for(i=0; i<n; ++i) {
    assert(valuesa[i] == *(int *)list_get_at(&dest, i)
           && "retrieved value has wrong value");
  }

  for(; i<2*n; ++i) {
    assert(valuesb[i % n] == *(int *)list_get_at(&dest, i)
           && "retrieved value has wrong value");
  }

  // ------------
  // DELETE RANGE
  // deleting the first half of the destination list and then
  // clearing the list.
  // ------------
  if(list_size(&dest) != 0) {
    unsigned int isize;
    ret = list_delete_range(&dest, 0, n-1);
    assert(ret == n && "number of elements deleted is wrong");
    assert(list_size(&dest) == n && "list size is wrong");

    isize = list_size(&dest);
    ret = list_clear(&dest);
    assert(ret == isize && "list size is wrong");
    assert(list_size(&dest) == 0 && "list size is wrong" );
  }

  // ----
  // SORT
  // ----

  // sort and check that the order is as expected
  // sort the array
  qsort(&valuesa[0], n, sizeof(int), int_bigger_than);

  // a) small to big
  ret = list_sort(&lista, 1);
  assert(ret == 0 && "sorting fails");

  for(i=0; i<n; ++i) {
    assert(valuesa[n - 1 - i] == *(int *)list_get_at(&lista, i)
           && "retrieved value has wrong value");
  }

  // b) big to small
  ret = list_sort(&lista, -1);
  assert(ret == 0 && "sorting fails");

  for(i=0; i<n; ++i) {
    assert(valuesa[i] == *(int *)list_get_at(&lista, i)
           && "retrieved value has wrong value");
  }

  // -------
  // DESTROY
  // -------

  // clean memory
  list_destroy(&lista);
  list_destroy(&listb);
  list_destroy(&dest);
}

int int_bigger_than(const void *a, const void *b) {
  return( *(int *)a < *(int *)b) - (*(int *)a > *(int *)b);
}
