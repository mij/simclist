/**
* @file   tier3_testc.h
* @author HansDals (@domoslabs on GitHub)
* @date   Oct 10, 2021
* @brief  test for leaks in dump/restore
*
* This header file declares the function used for testing:
*
*/

#ifndef TIER3_TESTC_H
#define TIER3_TESTC_H

#include <sys/types.h>

/**
* @name    TestC checks
*
* @param [in] n        number of elements that are going to be
*                      created and saved.
*
* Example Usage:
* @code
*    testc_check(3);   // this will call the first check and will create a new
*                      // list with 3 elements and check the functions'
*                      // functionalities
* @endcode
*/
int testc_check();

#endif
