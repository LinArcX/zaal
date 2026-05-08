#include <stdio.h>

#include "util/zaalStringsTests.h"
#include "scanner/scannerTests.h"
#include "parser/parserTests.h"

int main(void)
{
  int failedTests = 0U;

  failedTests += zaalStringsRunner();
  failedTests += scannerRunner();
  failedTests += parserRunner();

  printf("\n *** Number of all failed TCs: %d ***\n", failedTests);

  return failedTests;
}
