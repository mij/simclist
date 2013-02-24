/**
* @file   tier3_testb.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  declares of the first test suite of the Tier3
*/

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "../../simclist.h"
#include "../lib/helpers.h"
#include "../lib/random.h"
#include "tier3_testb.h"


/* shared lists and variables */
list_t list;
list_t list_number_t;
int *array;
pthread_mutex_t mutex;

/* Thread reading the content of the shared list */
void *read_list(void *number_of_elements);

/* Thread changes sequentially 50*n elements of the list by
   deleting an element and inserting it at the same position.
   During the delete/append the thread acquires a lock */
void *delete_insert(void *number_of_elements);

/* Start deleting all the elements randomly and check the
   emptiness of the list */
void *check_and_clear(void *number_of_elements);

/* Check the correct operation over seeker for a struct */
void *number_t_check(void *number_of_elements);


void testb_check(size_t const n) {
  pthread_t tid1, tid2, tid3, tid4;
  int ret, i, err;
  int *element;
  array = (int *)malloc(sizeof(int) * n);

  // --------------
  // INITIALIZATION
  // of the list
  // --------------
  ret = list_init(&list);
  assert(ret == 0);

  // set the comparator
  ret = list_attributes_comparator(&list, list_comparator_int);
  assert(ret == 0);

  // populate the list and the array
  for(i=0; i<n; ++i) {
    randomi(&array[i]);
    list_append(&list, &array[i]);
  }


  // --------------------------
  // READ - READ RACE CONDITION
  // --------------------------
  err = pthread_create(&tid1, NULL, read_list, (void *)&n);
  assert(err == 0 && "failed creating first thread");

  err = pthread_create(&tid2, NULL, read_list, (void *)&n);
  assert(err == 0 && "failed creating second thread");

  err = pthread_join(tid1, NULL);
  assert(err == 0 && "failed joining first thread");

  err = pthread_join(tid2, NULL);
  assert(err == 0 && "failed joining second thread");


  // mutex is needed for locks
  err = pthread_mutex_init(&mutex, NULL);
  assert(err == 0 && "error initializing mutex");

  // ----------------------------
  // WRITE - WRITE RACE CONDITION
  // ----------------------------
  err = pthread_create(&tid3, NULL, delete_insert, (void *)&n);
  assert(err == 0 && "failed creating third thread");

  err = pthread_create(&tid4, NULL, delete_insert, (void *)&n);
  assert(err == 0 && "failed creating fourth thread");

  err = pthread_join(tid3, NULL);
  assert(err == 0 && "failed joining third thread");

  err = pthread_join(tid4, NULL);
  assert(err == 0 && "failed joining fourth thread");


  // Check now the consistency of the array and the list
  // manipulated by the previously created threads.

  // compare
  for(i=0; i<n; ++i) {
    element = (int *)list_get_at(&list, i);
    assert(element != NULL && "failed retrieve element after dump/restore");
    assert(*element == array[i]
           && "value of the element is wrong after threads execution");
  }


  // ----------------------------
  // WRITE - WRITE RACE CONDITION (with deletion)
  // ----------------------------
  err = pthread_create(&tid3, NULL, check_and_clear, (void *)&n);
  assert(err == 0 && "failed creating fifth thread");

  err = pthread_create(&tid4, NULL, check_and_clear, (void *)&n);
  assert(err == 0 && "failed creating sixth thread");

  err = pthread_join(tid3, NULL);
  assert(err == 0 && "failed joining fifth thread");

  err = pthread_join(tid4, NULL);
  assert(err == 0 && "failed joining sixth thread");


  // -------------------------------
  // SEEKER and RACE CONDITION CHECK
  // check the correctness of the seeker in case
  // of multiple thread operating on the list
  // -------------------------------

  // Set the seeker
  ret = list_attributes_seeker(&list, number_t_seeker);
  assert(ret == 0);

  // ----------------------------
  // WRITE - WRITE RACE CONDITION
  // ----------------------------
  err = pthread_create(&tid3, NULL, number_t_check, (void *)&n);
  assert(err == 0 && "failed creating seventh thread");

  err = pthread_create(&tid4, NULL, number_t_check, (void *)&n);
  assert(err == 0 && "failed creating eighth thread");

  err = pthread_join(tid3, NULL);
  assert(err == 0 && "failed joining seventh thread");

  err = pthread_join(tid4, NULL);
  assert(err == 0 && "failed joining eighth thread");



  // finally free the memory
  free(array);
  array=NULL;
  list_destroy(&list);
}

void *read_list(void *number_of_elements) {
  int n = *(int *)number_of_elements;

  int i;
  int *element;

  for(i=0; i<n; ++i) {
    element = (int *)list_get_at(&list, i);
    assert(element != NULL);
    assert(*element == array[i]);
  }

  pthread_exit((void *)0);
}

void *delete_insert(void *number_of_elements) {
  int n = *(int *)number_of_elements;
  int i, ret;
  int array_pos, list_pos;

  for(i=0; i<50 * n; ++i) {
    // determine the position
    pthread_mutex_lock(&mutex);

      array_pos = rand() % n;
      list_pos = list_locate(&list, &array[array_pos]);
      assert(list_pos >= 0);
      assert(list_pos < list_size(&list));
      assert(*(int *)list_get_at(&list, list_pos) == array[array_pos]);

      ret = list_delete_at(&list, list_pos);
      assert(ret == 0);

      ret = list_insert_at(&list, &array[array_pos], list_pos);
      assert(ret > 0);

    pthread_mutex_unlock(&mutex);
  }

  pthread_exit((void *)0);
}

void *check_and_clear(void *number_of_elements) {
  int n = *(int *)number_of_elements;
  int size, pos, ret;

  for(int i=0; i<2*n; ++i) {
    pthread_mutex_lock(&mutex);

      if(!list_empty(&list)) {
        size = list_size(&list);
        assert(size >= 0 && "list size inconsistent during check_and_clear \
                             thread executino");

        pos = rand() % size;
        ret = list_delete_at(&list, pos);
        assert(ret == 0 && "deletion of element fails during check_and_clear \
                            thread executino");
      }

    pthread_mutex_unlock(&mutex);
  }

  pthread_exit((void *)0);
}


void *number_t_check(void *number_of_elements) {
  int n = *(int *)number_of_elements;
  int value, ret, i;
  number_t *number;
  number_t *seeked;

  // Populate
  for(i=0; i<n; ++i) {
    pthread_mutex_lock(&mutex);

      randomi(&value);
      number = (number_t *)malloc(sizeof(number_t));
      number->number = value;
      number->snumber.number = -1 * value;

      if(i % 2 == 0) {
        ret = list_append(&list, number);
        assert(ret == 1
               && "append fails during number_t_check execution");
      } else {
        ret = list_prepend(&list, number);
        assert(ret == 1
               && "prepend fails during number_t_check execution");
      }

      // Check using the seeker
      seeked = (number_t *)list_seek(&list, &value);
      assert(seeked->number == value
             && "number not consistent during number_t_check execution");
      assert((seeked->snumber).number ==  -1 * value
             && "snumber.number not consistent after \
                 number_t_check execution");
      
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit((void *)0);
}
