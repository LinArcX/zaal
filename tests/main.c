#include <stdio.h>

#include "scanner/scannerTests.h"
#include "parser/parserTests.h"

int main(void)
{
  int failedTests = 0U;

  failedTests += scannerRunner();
  failedTests += parserRunner();

  printf("Number of all failed TCs: %d\n", failedTests);

  return failedTests;
}
