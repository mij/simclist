/**
* @file   tests.c
* @author Armando Miraglia (arma@lamortenera.it)
* @date   July, 2011
* @brief  performs the checks required by the tier 2
*/

#include "tier2_testa.h"
#include "tier2_testb.h"
#include "tier2_testc.h"
#include "tier2_testd.h"

#include <stdio.h>

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
  testb_check(10);
  testb_check(100);
  testb_check(1000);

  // ----------------
  // Tier2 C checking
  // ----------------
  testc_check(0);
  testc_check(1);
  testc_check(2);
  testc_check(3);
  testc_check(10);
  testc_check(100);
  testc_check(1000);

  // ----------------
  // Tier2 D checking
  // ----------------
  testd_check(0);
  testd_check(1);
  testd_check(10);
  testd_check(100);
  testd_check(1000);

  return 0;
}
