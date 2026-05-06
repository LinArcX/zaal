#include <stdio.h>

#include "util/fileUtilTests.h"
#include "scanner/scannerTests.h"
#include "parser/parserTests.h"

int main(void)
{
  int failedTests = 0U;

  failedTests += fileUtilRunner();
  failedTests += scannerRunner();
  failedTests += parserRunner();

  printf("Number of all failed TCs: %d\n", failedTests);

  return failedTests;
}
