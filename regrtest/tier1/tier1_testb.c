/**
* @file   tier1_testb.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  implements of the second test suite of the Tier2
*/

#include <assert.h>
#include <stdlib.h>
#include <limits.h>

#include "../../simclist.h"
#include "../lib/random.h"
#include "../lib/helpers.h"
#include "tier1_testb.h"

#define NUM_OF_LISTS      2

/* implementation of Test B */
void testb_check(size_t const n) {
  list_t lists[NUM_OF_LISTS];
  int *added_value;
  int values[NUM_OF_LISTS][n];
  int ret, i, j;
  int value;

  // --------------
  // INITIALIZATION
  // of the lists and check for correctness
  // --------------
  for(i=0; i<NUM_OF_LISTS; ++i) {
    ret = list_init(&lists[i]);
    assert(ret == 0 && "list initialization fails");
  }

  // for achieving the insertion of new elements creating new
  // memory areas, instead of calling malloc(), we set the
  // list_attribute_copy and check the correctness.
  for(i=0; i<NUM_OF_LISTS; ++i) {
    ret = list_attributes_copy(&lists[i], int_size, 1);
    assert(ret == 0 && "setting attribute copy fails");
  }

  // ---------
  // INSERTION
  // both successful and unsuccessful
  // ---------
  for(i=0; i<NUM_OF_LISTS; ++i) {
    // successful insertion in empty list
    randomi(&value);
    ret = list_insert_at(&lists[i], &value, 0);
    assert(ret > 0 && "element insertion fails");
    assert(list_size(&lists[i]) == 1 && "list size is wrong");
    // checking the inserted value
    added_value = (int *)list_get_at(&lists[i], 0);
    assert(added_value != NULL && "retrieving element fails");
    assert(value == *added_value && "retrieved value has wrong value");
    // successful deletion 
    ret = list_delete_at(&lists[i], 0);
    assert(ret == 0 && "delete element fails");
    assert(list_size(&lists[i]) == 0 && "list size is wrong");
  }

  // Failure of insertion on multiple elements.
  // The insertion is done at indexes that are not
  // reachable for the list because it's empty
  for(i=0; i<NUM_OF_LISTS; ++i) {
    randomi(&value);
    for(j=1; j<4; ++j) {
      ret = list_insert_at(&lists[i], &value, j);
      assert(ret < 0 && "element insertion failure fails");
      assert(list_size(&lists[i]) == 0 && "list size is wrong");

      ret = list_delete_at(&lists[i], j);
      assert(ret < 0 && "element deletion failure fails");
      assert(list_size(&lists[i]) == 0 && "list size is wrong");
    }
  }

  // ---------
  // PREAPPEND
  // ---------

  // append the second half of the lists
  for(i=0; i<NUM_OF_LISTS; ++i) {
    for(j=0; j<(n/2); ++j) {
      randomi(&value);
      ret = list_prepend(&lists[i], &value);
      assert(ret == 1 && "element prepend fails");
      // checking also the value appended
      added_value = (int *)list_get_at(&lists[i], 0);
      assert(added_value != NULL && "retrieving element fails");
      assert(value == *added_value && "retrieved value has wrong value");
      // store the max for each list
      values[i][(n/2-1)-j] = value;
    }

    assert(list_size(&lists[i]) == n/2 && "list size is wrong");
  }

  // ------
  // APPEND
  // ------

  // append the first half of the lists
  for(i=0; i<NUM_OF_LISTS; ++i) {
    for(j=(n/2); j<n; ++j) {
      randomi(&value);
      ret = list_append(&lists[i], &value);
      assert(ret == 1 && "element append fails");
      // checking also the value appended
      added_value = (int *)list_get_at(&lists[i], j);
      assert(added_value != NULL && "retrieving element fails");
      assert(value == *added_value && "retrieved value has wrong value");
      // store the value in the matrix
      values[i][j] = value;
    }

    assert(list_size(&lists[i]) == n && "list size is wrong");
  }

  // check the values inserted in the lists
  for(i=0; i<NUM_OF_LISTS; ++i) {
    for(j=0; j<n; ++j) {
      assert(values[i][j] == *(int *)list_get_at(&lists[i], j)
             && "retrieved value has wrong value");
    }
  }

  // -----
  // CLEAR
  // -----

  // check the correctness of the clear function execution
  // and check also the length of the cleared list
  for(i=0; i<NUM_OF_LISTS; ++i) {
      unsigned int isize;
    isize = list_size(&lists[i]);

    ret = list_clear(&lists[i]);
    assert(ret == (int)isize && "clearing list fails");

    ret = list_size(&lists[i]);
    assert(ret == 0 && "list size is wrong");
  }

  // -------
  // DESTROY
  // -------

  // destroy both lists
  for(i=0; i<NUM_OF_LISTS; ++i)
    list_destroy(&lists[i]);
}
