/**
* @file   random.h
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  declares the functions for generating random values
*
* This header file is intended to provide a small library for
* generating different kind of random values.
*
* @todo provide more random generators
*/

/**
* @name    Integer random generator
* @brief   generates random integers
*
* @param [out] value    container holding the generated random value.
* @return      int      0 if the number was correctly generated, 1 otherwise
*
* Example Usage:
* @code
*    int value;               // container of the value
*    if(randomi(&value) == 0) // generates a random value that is stored in value
*       ;
* @endcode
*/
int randomi(int *value);


/*  */
char *randoms(int length);
