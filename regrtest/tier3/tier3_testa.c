/**
* @file   tier3_testa.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  declares of the first test suite of the Tier3
*/

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../simclist.h"
#include "../lib/random.h"
#include "../lib/helpers.h"
#include "tier3_testa.h"

#define DUMP_FILE_NAME    "list.simc"
#define NAME_LENGTH       20
#define PHONE_LENGTH      10

// person type
struct person_s {
  char *name;
  char *phone;
};

typedef struct person_s person_t;



/* size of the perons_t type */
size_t person_size(const void *el);

/* serializer for the type person */
void
*person_t_serializer(const void *restrict el, uint32_t *restrict len);

/* unserializer for the type person */
void *person_t_unserializer(const void *restrict data, uint32_t *restrict len);

/* hash computer for the person_t type*/
list_hash_t list_hashcomputer_person(const void *el);


void testa_check(size_t const n) {
  // int values
  list_t list;
  list_t list_mirror;
  list_hash_t hash;
  list_hash_t hash_mirror;
  // person values
  list_t list_person;
  list_t list_person_mirror;
  list_hash_t hash_person;
  list_hash_t hash_person_mirror;
  // other variables
  person_t person;
  person_t *p1, *p2;
  int value;
  int i, ret;


  // ------------------------
  // SERIALIZE & DUMP-RESTORE
  // test the dump into a file, restore the contento of the
  // file and check the content of the list restored
  // ------------------------

  // Initialization of the two lists
  ret = list_init(&list);
  assert(ret == 0);
  ret = list_init(&list_mirror);
  assert(ret == 0);

  // for achieving the insertion of new elements creating new
  // memory areas, instead of calling malloc(), we set the
  // list_attribute_copy and check the correctness.
  ret = list_attributes_copy(&list, int_size, 1);
  assert(ret == 0);
  ret = list_attributes_copy(&list_mirror, int_size, 1);
  assert(ret == 0);

  // Populate the two lists with the same elements
  for(i=0; i<n; ++i) {
    randomi(&value);

    ret = list_insert_at(&list, &value, i);
    assert(ret == 1);
    ret = list_insert_at(&list_mirror, &value, i);
    assert(ret == 1);
  }

  ret = list_dump_file(&list, DUMP_FILE_NAME, NULL);
  assert(ret == 0 && "dumping into file with meter set fails");

  // clear the list
  i = (int)list_size(&list);
  ret = list_clear(&list);
  assert(ret == i && "list clear with meter set fails");

  // Restore the list into a file
  ret = list_restore_file(&list, DUMP_FILE_NAME, NULL);
  assert(ret == 0 && "restoring from file with meter set fails");


  // Check the content of the lists
  for(i=0; i<n; ++i) {
    assert(
      *(int *)list_get_at(&list, i) == *(int *)list_get_at(&list_mirror, i)
      && "content of the list after restoring is wrong"
    );
  }

  // Use hash comparison
  list_attributes_hash_computer(&list, list_hashcomputer_int32_t);
  list_attributes_hash_computer(&list_mirror, list_hashcomputer_int32_t);
 
  list_hash(&list, &hash);
  list_hash(&list_mirror, &hash_mirror);
 
  assert(hash == hash_mirror
         && "hash of the lists are different after dump/restore");

  // delete the file created previously
  assert(remove(DUMP_FILE_NAME) == 0 && "unable to delete the file");



  // -------------------------------
  // SERIALIZE & DUMP-RESTORE STRUCT
  // serialize and dump the created structure using
  // the personalized serializer and unserializer
  // -------------------------------

  // Initialization of the two lists
  ret = list_init(&list_person);
  assert(ret == 0);
  ret = list_init(&list_person_mirror);
  assert(ret == 0);

  // for achieving the insertion of new elements creating new
  // memory areas, instead of calling malloc(), we set the
  // list_attribute_copy and check the correctness.
  ret = list_attributes_copy(&list_person, person_size, 1);
  assert(ret == 0);
  ret = list_attributes_copy(&list_person_mirror, person_size, 1);
  assert(ret == 0);

  // Populate the two lists with the same elements
  for(i=0; i<n; ++i) {
    person.name  = randoms(NAME_LENGTH);
    person.phone = randoms(PHONE_LENGTH);

    ret = list_insert_at(&list_person, &person, i);
    assert(ret == 1);
    ret = list_insert_at(&list_person_mirror, &person, i);
    assert(ret == 1);
  }

  // Set the personal created serializer and unserializer functions
  ret = list_attributes_serializer(&list_person, person_t_serializer);
  assert(ret == 0 && "setting serializer for structure fails");
  ret = list_attributes_unserializer(&list_person, person_t_unserializer);
  assert(ret == 0 && "setting unserializer for structure fails");

  ret = list_dump_file(&list_person, DUMP_FILE_NAME, NULL);
  assert(ret == 0 && "dumping using the self defined dumper fails");

  // clear the list
  i = (int)list_size(&list_person);
  ret = list_clear(&list_person);
  assert(ret == i && "clear with list of structs fails");

  // Restore the list into a file
  ret = list_restore_file(&list_person, DUMP_FILE_NAME, NULL);
  assert(ret == 0 && "restoring using the self defined restorer fails" );


  // Check the content of the lists
  for(i=0; i<n; ++i) {
    p1 = (person_t *)list_get_at(&list_person, i);
    p2 = (person_t *)list_get_at(&list_person, i);

    assert(strncmp(p1->name, p2->name, NAME_LENGTH) == 0
           && "value of the name after dump/restore is wrong");
    assert(strncmp(p1->phone, p2->phone, PHONE_LENGTH) == 0
           && "value of the phone after dump/restore is wrong");
  }

  // Use hash comparison
  list_attributes_hash_computer(&list_person, list_hashcomputer_person);
  list_attributes_hash_computer(&list_person_mirror, list_hashcomputer_person);
 
  list_hash(&list_person, &hash_person);
  list_hash(&list_person_mirror, &hash_person_mirror);
  assert(hash_person == hash_person_mirror
         && "hash of the lists of structs are different after dump/restore");

  // delete the file created previously
  assert(remove(DUMP_FILE_NAME) == 0
         && "unable to remove file after dump/restore");

  // finally free the memory
  list_destroy(&list);
  list_destroy(&list_mirror);

  list_destroy(&list_person);
  list_destroy(&list_person_mirror);
}



size_t person_size(const void *el) {
  return sizeof(person_t);
}

void *person_t_serializer(const void *restrict el, uint32_t *restrict len) {
  int i, j;
  char *person_skel;
  person_t *person;

  *len = sizeof(char) * (NAME_LENGTH + PHONE_LENGTH);
  person = (person_t *)el;
  person_skel = (char *)malloc(*len);

  // add the name without the terminating '\0' character
  for(i=0; i<19 ; ++i) person_skel[i] = person->name[i];

  // add a separating '!'
  person_skel[i++] = '!';

  // add the phone number finally
  for(j=0; j<PHONE_LENGTH; ++i, ++j) person_skel[i] = person->phone[j];

  return person_skel;
}

void *person_t_unserializer(const void *restrict data, uint32_t *restrict len) {

  int i, j;
  char *person_skel;
  person_t *person;

  *len = sizeof(person_t);
  person_skel = (char *)data;
  person = (person_t *)malloc(sizeof(person_t));
  person->name = (char *)malloc(NAME_LENGTH * sizeof(char));
  person->phone = (char *)malloc(PHONE_LENGTH * sizeof(char));

  for(i=0; i<(NAME_LENGTH-1) ; ++i) {
    person->name[i] = person_skel[i];
  }

  // complete the name string
  person->name[i++] = '\0';

  // add the phone number finally
  for(j=0; j<PHONE_LENGTH; ++i, ++j) person->phone[j] = person_skel[i];

  return person;
}

list_hash_t list_hashcomputer_person(const void *el) {
  person_t *person = (person_t *)el;
  list_hash_t hash;

  hash = list_hashcomputer_string(person->name);
  hash ^= list_hashcomputer_string(person->phone);

  return hash;
}
