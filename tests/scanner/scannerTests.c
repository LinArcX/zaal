#include <libgen.h>
#include <cmocka.h>
#include "scannerTests.h"
#include "../../src/scanner.c"

/**
 * @brief Test that example_main() correctly processes a valid expression
 *        and produces expected output.
 *
 * This integration test verifies the complete application behavior including
 * output formatting.
 */
static void scanner_test_spaces(void **state)
{
  (void)state;

  // open the file
  char fileName[512];
  strncpy(fileName, __FILE__, sizeof fileName);

  char *srcDir = dirname(fileName);

  char path[512];
  snprintf(path, sizeof path, "%s/%s", srcDir, "data.txt");

  const FILE* pFile = fopen(path, "r");
  assert_non_null(pFile);

  // tests
  uint32_t line = 0;
  uint32_t putBackChar = 0;
  int ch = getNextChar(pFile, &line, &putBackChar);
  assert_int_equal(ch, 12);


  // close the file
  if (fclose(pFile) != 0) {
    perror("ERROR! fclose: pSourceFile");
  }
  pFile = NULL;
}

static void scanner_test_null(void **state)
{
  // no-op. tells the compiler state is intentionally unused. It suppresses "unused parameter" 
  (void) state; /* unused */
}

int scannerRunner(void)
{
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(scanner_test_null),
      cmocka_unit_test(scanner_test_spaces),
  };

  return cmocka_run_group_tests_name("Scanner", tests, NULL, NULL);
}
