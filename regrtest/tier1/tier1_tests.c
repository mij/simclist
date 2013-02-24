/**
* @file   tests.c
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  performs the checks required by the tier 1
*/

#include "tier1_testa.h"
#include "tier1_testb.h"
#include "tier1_testc.h"

int main(void) {
  // ----------------
  // Tier1 A checking
  // ----------------
  testa_check(0);
  testa_check(1);
  testa_check(10);
  testa_check(100);
  testa_check(1000);

  // ----------------
  // Tier1 B checking
  // ----------------
  testb_check(0);
  testb_check(1);
  testb_check(10);
  testb_check(100);
  testb_check(1000);

  // ----------------
  // Tier1 C checking
  // ----------------
  testc_check(0);
  testc_check(1);
  testc_check(10);
  testc_check(100);
  testc_check(1000);

  return 0;
}
