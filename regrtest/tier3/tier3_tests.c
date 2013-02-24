/**
* @file   tests.c
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  performs the checks required by the tier 3
*/

#include "tier3_testa.h"
#include "tier3_testb.h"

int main(void) {
  // ----------------
  // Tier2 A checking
  // ----------------
  testa_check(0);
  testa_check(1);
  testa_check(10);
  testa_check(100);
  testa_check(1000);

  // ----------------
  // Tier2 B checking
  // ----------------
  testb_check(0);
  testb_check(1);
  testb_check(3);
  testb_check(10);
  testb_check(100);

  return 0;
}
