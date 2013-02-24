/**
* @file   tier2_testb.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  declares of the first test suite of the Tier2
*/

#include <assert.h>
#include <stdlib.h>

#include "../../simclist.h"
#include "../lib/random.h"
#include "../lib/helpers.h"
#include "tier2_testb.h"

void testb_check(size_t const n) {
  int value, size;
  int values[n];
  list_t list;
  int ret, i;

  // --------------
  // INITIALIZATION
  // of the list
  // --------------
  ret = list_init(&list);
  assert(ret == 0 && "initialization of the list fails");

  // for achieving the insertion of new elements creating new
  // memory areas, instead of calling malloc(), we set the
  // list_attribute_copy and check the correctness.
  ret = list_attributes_copy(&list, int_size, 1);
  assert(ret == 0 && "setting copy attribute fails");

  // ----------
  // COMPARISON
  // test the comparison of the elements in the list by
  // - locating elements in the list
  // - ordering the list and checking for order correctness
  // ----------
  ret = list_attributes_comparator(&list, list_comparator_int);
  assert(ret == 0 && "setting comparator attribute fails");

  // populate the array and the list with random elements
  for(i=0; i<n; ++i) {
    randomi(&value);
    values[i] = value;

    ret = list_append(&list, &value);
    assert(ret == 1 && "appending fails");
  }

  // lets try to locate the two extremes and a
  // random value from the array (if possible)
  size = list_size(&list);
  assert(size == n && "list size is wrong");

  if(size >= 1)
    assert(*(int *)(list_get_at(&list, 0)) == values[0]);

  if(size > 1)
    assert(values[size - 1] == *(int *)(list_get_at(&list, size - 1)));

  if(size > 2) {
    i = (size % (size - 2)) + 1;
    assert(values[i] == *(int *)(list_get_at(&list, i)));
  }

  // now order both the list and the array and check
  // that the values are successfully ordered
  // - sort the array
  qsort(values, n, 4, list_comparator_int);
  // - sort list
  list_sort(&list, -1);
  // - compare

  for(i=0; i<n; i++) {
    value = *(int *)(list_get_at(&list, i));
    assert(value == values[i] && "list not in oder");
  }

  // check the min and max functions
  if(size >= 1)
    assert(values[0] == *(int *)(list_get_max(&list))
           && "maximum value does not match");

  if(size > 1)
    assert(values[size - 1] == *(int *)(list_get_min(&list))
           && "minimum value does not match");

  // finally free the memory
  list_destroy(&list);
}
