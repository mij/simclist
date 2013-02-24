/**
* @file   tier2_testb.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  declares the first test suite of the Tier2
*
* This header file declares the function used for testing:
*
*/

#ifndef TIEAR2_TESTB_H
#define TIEAR2_TESTB_H

#include <sys/types.h>

/**
* @name    TestB checks
* @brief   check of the methods 
*
*
*
*
* @param [in] n        number of elements that are going to be
*                      created and saved.
*
* Example Usage:
* @code
*    testb_check(3);   // this will call the first check and will create a new
*                      // list with 3 elements and check the functions'
*                      // functionalities
* @endcode
*/
void testb_check(size_t const n);

#endif
