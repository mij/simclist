/**
* @file   tier1_testc.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  declares the third test suite of the Tier1
*
* This header file declares the function used for testing the functions:
*   - list_attributes_comparator()
*   - list_empty()
*   - list_insert() 
*   - list_get_min()
*   - list_get_max()
*   - list_iterator_start()
*   - list_iterator_hasnext()
*   - list_iterator_next()
*   - list_iterator_stop()
*   - list_concat()
*   - list_delete_range()
* all the 
*/

#ifndef __TIER1_TESTC_H__
#define __TIER1_TESTC_H__

#include <sys/types.h>

/**
* @name    TestA checks
* @brief   checks functionalities of list_attributes_comparator(), list_empty()
*          list_insert(), list_get_min(), list_get_max(), list_iterator_start()
*          list_iterator_hasnext(), list_iterator_next(), list_iterator_stop()
*          list_concat(), list_delete_range()
*
* The function performs a set of checks with the purpose to check the
* returned value to be the expected one. The functions are checked sequentially
* on the number of lists that have been created.
*
* @param [in] n       number of elements stored in the list.
*
* Example Usage:
* @code
*    testc_check(3);  // creates 3 values stored in the lists
*                     // and performs the checks sequentially on all of them
* @endcode
*/
void testc_check(size_t const n);

#endif  // __TIER1_TESTC_H__
