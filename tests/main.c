#include <stdint.h>

#include "scanner/scannerTests.h"
#include "parser/parserTests.h"

int main(void)
{
  uint32_t failedTests = 0;

  failedTests += scannerRunner();
  failedTests += parserRunner();

  return failedTests;
}
