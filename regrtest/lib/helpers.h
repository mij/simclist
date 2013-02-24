/**
* @file   helpers.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  declares the function used for setting list attributes
*/

#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <sys/types.h>
#include "../../simclist.h"

/* Shared subnumber_t type used in different checks */
struct subnumber_s {
  int number;
};
typedef struct subnumber_s subnumber_t;

/* Shared number_t type used in different checks */
struct number_s {
  int number;
  subnumber_t snumber;
};
typedef struct number_s number_t;


/**
* @name    Int meter
* @brief   size of int as meter function
*
* Provides the meter needed by list_attribute_copy() for the type int.
*
* @param  [in] el       element stored in the list.
* @return      size_t   size of the type int.
*
* Example Usage:
* @code
*    list_t l;
*    list_init(&l);
*    list_attributes_copy(&l, int_size, 1);
* @endcode
*/
size_t int_size(const void *el);

/**
* @name    int hash computer
* @brief   determines the hash value for the current element
*
* Provides the hash needed by list_attribute_hash_computer() for the type int.
*
* @param  [in] el             element stored in the list
* @return      list_hash_t    hash of the element considered
*
* Example Usage:
* @code
*    list_t l;
*    list_init(&l);
*    list_attributes_hash_computer(&l, list_hashcomputer_int, 1);
* @endcode
*/
list_hash_t list_hashcomputer_int(const void *el);

/**
* @name    int hash computer
* @brief   determines the similarity between values of two elements
*
* Provides the hash needed by list_attribute_hash_computer() for the type int.
*
*
* @param  [in] el             element stored in the list
* @return      list_hash_t    hash of the element considered
*
* Example Usage:
* @code
*    list_t l;
*    list_init(&l);
*    list_attributes_hash_computer(&l, list_comparator_int);
* @endcode
*/
int list_comparator_int(const void *a, const void *b);


/* seeker function for the number-subnumber struct */
int number_t_seeker(const void *el, const void *value);

#endif  // __HELPERS_H__
