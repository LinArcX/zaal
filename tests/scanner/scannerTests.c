#include <cmocka.h>

#include "../../src/scanner.c"
#include "../../src/util/fileUtil.h"

/**
 * @brief testing getNextChar() function
 *
 * @param state 
 */
static void testScannerGetNextChar(void **state)
{
  // no-op. tells the compiler state is intentionally unused. It suppresses "unused parameter" 
  (void)state;
  getProjectRootPath();

  //// tests
  //uint32_t line = 0;
  //uint32_t putBackChar = 0;
  //int ch = getNextChar(pFile, &line, &putBackChar);
  //assert_int_equal(ch, 12);


  //// close the file
  //if (fclose(pFile) != 0) {
  //  perror("ERROR! fclose: pSourceFile");
  //}
  //pFile = NULL;
}

int scannerRunner(void)
{
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(testScannerGetNextChar),
  };

  return cmocka_run_group_tests_name("Scanner", tests, NULL, NULL);
}
