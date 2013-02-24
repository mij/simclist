/**
* @file   tier2_testc.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  declares of the first test suite of the Tier2
*/

#include <assert.h>
#include <stdlib.h>

#include "../../simclist.h"
#include "../lib/random.h"
#include "../lib/helpers.h"
#include "tier2_testc.h"

void testc_check(size_t const n) {
  int values[n];
  int *tmp;
  list_t list;
  int ret;
  int i;

  // --------------
  // INITIALIZATION
  // of the list
  // --------------
  ret = list_init(&list);
  assert(ret == 0);

  // ----
  // COPY
  // check that actually a new memory area is set up
  // and a new pointer is retrieved.
  // ----
  ret = list_attributes_copy(&list, int_size, 1);
  assert(ret == 0);

  // Try to create a new element
  for(i=0; i<n; i++) {
    randomi(&values[i]);

    // Insert the element
    ret = list_insert_at(&list, &values[i], i);
    assert(ret > 0 && "insertion at position failed");

    // check the element inserted
    assert(values[i] == *(int *)list_get_at(&list, i)
           && "value retrieved does not match");
  }

  // Retrieve data back and check the pointer differences
  for(i=n-1; i >= 0; i--) {
    tmp = (int *)list_extract_at(&list, i);
    assert(&values[i] != tmp && "extracting element fails");

    // free() is already performed by list_extract_at()
    // during element deletion
  }

  // check for emptyness
  assert(list_size(&list) == 0 && "list size is wrong");

  // Delete the list
  list_destroy(&list);
}
