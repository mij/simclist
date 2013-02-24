/**
* @file   tier1_testa.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  declares of the first test suite of the Tier1
*/
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

#include "../../simclist.h"
#include "tier1_testa.h"

/* empty comparator function */
int          comparator(const void *a, const void *b);
/* empty seeker function */
int          seeker(const void *a, const void *b);
/* empty serializer function */
void        *serializer(const void *restrict el, uint32_t *restrict len);
/* empty unserializer function */
void        *unserializer(const void *restrict el, uint32_t *restrict len);
/* empty hash_computer function */
list_hash_t  hash_computer(const void *el);
/* empty meter function */
size_t       meter(const void *el);

/* implementation of Test A */
void testa_check(size_t const nlists) {
  list_t lists[nlists];
  int i;
  int ret;
  
  // --------
  // CREATION
  // creation of the lists; stimulating:
  //    - list_init()
  // --------
  for(i=0; i<nlists; ++i) {
    ret = list_init(&lists[i]);
    assert(ret == 0 && "list initialization fails");
  }

  // ------------------------------------
  // SETTING AND UN-SETTING OF ATTRIBUTES
  // set and unset of attbriutes; stimulating:
  // ------------------------------------

  // setting comparator attribute
  for(i=0; i<nlists; ++i) {
    ret = list_attributes_comparator(&lists[i], comparator);
    assert(ret == 0 && "setting attribute comparator fails");
  }

  // unsetting comparator attribute
  for(i=0; i<nlists; ++i) {
    ret = list_attributes_comparator(&lists[i], NULL);
    assert(ret == 0 && "unsetting attribute comparator fails");
  }

  // setting seeker attribute
  for(i=0; i<nlists; ++i) {
    ret = list_attributes_seeker(&lists[i], seeker);
    assert(ret == 0 && "setting attribute seeker fails");
  }

  // unsetting seeker attribute
  for(i=0; i<nlists; ++i) {
    ret = list_attributes_seeker(&lists[i], NULL);
    assert(ret == 0 && "unsetting attribute seeker fails");
  }

  // setting copy attribute
  for(i=0; i<nlists; ++i) {
    ret = list_attributes_copy(&lists[i], meter, 0);
    assert(ret == 0 && "setting attribute copy fails");
  }

  // unsetting copy attribute
  for(i=0; i<nlists; ++i) {
    ret = list_attributes_copy(&lists[i], NULL, 0);
    assert(ret == 0 && "unsetting attribute copy fails");
  }

  // setting hash_computer attribute
  for(i=0; i<nlists; ++i) {
    ret = list_attributes_hash_computer(&lists[i], hash_computer);
    assert(ret == 0 && "setting attribute hash_computer fails");
  }

  // unsetting hash_computer attribute
  for(i=0; i<nlists; ++i) {
    ret = list_attributes_hash_computer(&lists[i], NULL);
    assert(ret == 0 && "unsetting attribute hash_computer fails");
  }

  // setting serializer attribute
  for(i=0; i<nlists; ++i) {
    ret = list_attributes_serializer(&lists[i], serializer);
    assert(ret == 0 && "setting attribute serializer fails");
  }

  // unsetting serializer attribute
  for(i=0; i<nlists; ++i) {
    ret = list_attributes_serializer(&lists[i], NULL);
    assert(ret == 0 && "unsetting attribute serializer fails");
  }

  // setting unserializer attribute
  for(i=0; i<nlists; ++i) {
    ret = list_attributes_unserializer(&lists[i], unserializer);
    assert(ret == 0 && "setting attribute unserializer fails");
  }

  // unsetting unserializer attribute
  for(i=0; i<nlists; ++i) {
    ret = list_attributes_unserializer(&lists[i], NULL);
    assert(ret == 0 && "unsetting attribute unserializer fails");
  }

  // -----------
  // DESTRUCTION
  // created lists are destructed; stimulating:
  //  - list_destroy()
  // -----------
  for(i=0; i<nlists; ++i) {
    list_destroy(&lists[i]);
  }
}

int comparator(const void *a, const void *b) {
  // empty declaration
  // needed only for debugging
  return 0;
}

int seeker(const void *a, const void *b) {
  // empty declaration
  // needed only for debugging
  return 0;
}

void *serializer(const void *restrict el, uint32_t *restrict len) {
  // empty declaration
  // needed only for debugging
  return NULL;
}

void *unserializer(const void *restrict el, uint32_t *restrict len) {
  // empty declaration
  // needed only for debugging
  return NULL;
}

list_hash_t hash_computer(const void *el) {
  // empty declaration
  // needed only for debugging
  return 0;
}

size_t meter(const void *el) {
  // empty declaration
  // needed only for debugging
  return 0;
}
