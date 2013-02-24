/**
* @file   tier2_testd.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  declares of the first test suite of the Tier2
*/

#include <assert.h>
#include <stdlib.h>

#include "../../simclist.h"
#include "../lib/random.h"
#include "../lib/helpers.h"
#include "tier2_testd.h"

void testd_check(size_t const n) {
  number_t *number[n];
  number_t *seeked;
  list_t list;
  int values[n];
  int ret, i;

  // --------------
  // INITIALIZATION
  // of the list
  // --------------
  ret = list_init(&list);
  assert(ret == 0 && "list initialization fails");

  // ------
  // SEEKER
  // based on the defined structure, check if the
  // seeker acts as expected.
  // ------

  // Set the seeker
  ret = list_attributes_seeker(&list, number_t_seeker);
  assert(ret == 0 && "set seeker attribute fails");

  // Populate
  for(i=0; i<n; ++i) {
    randomi(&values[i]);
    number[i] = (number_t *)malloc(sizeof(number_t));
    number[i]->number = values[i];
    number[i]->snumber.number = -1 * values[i];

    ret = list_append(&list, number[i]);
    assert(ret == 1);
  }

  // Check the resulting seeked value
  for(i=0; i<n; ++i) {
    seeked = (number_t *)list_seek(&list, &values[i]);
    assert(seeked != NULL && "seeker execution fails");
    assert(seeked->number == values[i]);
    assert((seeked->snumber).number ==  -1 * values[i]);
  }

  // Delete the list
  list_destroy(&list);
}


