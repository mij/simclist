/**
* @file   tier1_testb.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  declares of the second test suite of the Tier2
*
* This header file declares the function used for testing:
*   - list_insert_at()
*   - list_prepend()
*   - list_append()
*   - list_get_at()
*   - list_delete_at()
*   - list_size()
*   - list_empty()
*   - list_clear()
* The lists are created, the attribute meter is set. This is done so that
* each time a new element is added, the allocation of a new memory area is
* performed. After checking all the operations lists are destroyed.
*/

#ifndef TIER1_TESTB_H
#define TIER1_TESTB_H

#include <sys/types.h>

/**
* @name    TestB checks
* @brief   check of the methods list_insert_at(), list_prepend(), list_append(),
*                               list_get_at(), list_delete_at(), list_size(),
*                               list_empty(), list_clear()
*
* @param [in] nlists   number of lists that are going to be created.
*
* Example Usage:
* @code
*    testb_check(3);  // creates 2 lists with 3 elements each
* @endcode
*/
void testb_check(size_t const n);

#endif
