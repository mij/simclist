/**
* @file   tier2_testa.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  declares of the first test suite of the Tier2
*/

#include <assert.h>

#include "../../simclist.h"
#include "../lib/random.h"
#include "../lib/helpers.h"
#include "tier2_testa.h"

void testa_check(size_t const n) {
  int32_t values[n];
  int ret, i;
  list_t list;
  list_hash_t hashes[n + 1], tmphash;

  // --------------
  // INITIALIZATION
  // of the list
  // --------------
  ret = list_init(&list);
  assert(ret == 0 && "list initialization fails");

  // ----------------
  // HASH GENERATION
  // starting populating the list, computing and storing
  // all the values and the hashes generated
  // ----------------

  // set the hash computer attribute
  ret = list_attributes_hash_computer(&list, list_hashcomputer_int32_t);
  assert(ret == 0 && "setting attribute hash computer fails");

  // the first hash to check is for the empty list
  ret = list_hash(&list, &hashes[0]);
  assert(ret == 0 && "hashing fails");

  // start populating both the array and the list and generate
  // all the hashes for each change of state of the array
  for(i=0; i<n; ++i) {
    // add and store the value
    randomi(&values[i]);
    ret = list_append(&list, &values[i]);
    assert(ret > 0 && "appending fails");

    // compute the hash
    ret = list_hash(&list, &hashes[i + 1]);
    assert(ret == 0 && "hashing fails");
  }

  list_clear(&list);

  // ---------------
  // HASH COMPARISON
  // re populate the list and check all the hashes
  // ---------------
  ret = list_hash(&list, &tmphash);
  assert(ret == 0 && "hashing fails");
  assert(tmphash == hashes[0] && "check hashing value fails");

  for(i=0; i<n; ++i) {
    // add and store the value
    ret = list_append(&list, &values[i]);
    assert(ret > 0);

    // compute the hash
    ret = list_hash(&list, &tmphash);
    assert(ret == 0);
    assert(tmphash == hashes[i + 1]);
  }

  // finally free the memory
  list_destroy(&list);
}
