/**
* @file   tier1_testa.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  declares the first test suite of the Tier1
*
* This header file declares the function used for testing:
*   - list_attributes_comparator()
*   - list_attributes_seeker()
*   - list_attributes_copy()
*   - list_attributes_hash_computer()
*   - list_attributes_serializer()
*   - list_attributes_unserializer()
* The lists are created, the attributes are set using empty functions and
* finally the lists are destroyed.
*/

#ifndef TIEAR1_TESTA_H
#define TIEAR1_TESTA_H

#include <sys/types.h>

/**
* @name    TestA checks
* @brief   check of the methods list_init(), list_destroy(), list_attributes_*()
*
* The function performs a set of checks with the purpose to check the
* returned value to be the expected one. The functions are checked sequentially
* on the number of lists that have been created.
*
* @param [in] nlists   number of lists that are going to be created.
*
* Example Usage:
* @code
*    testa_check(3);  // creates 3 lists and performs the checks sequentially
*                     // on all of them
* @endcode
*/
void testa_check(size_t const nlists);

#endif
