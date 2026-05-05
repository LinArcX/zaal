#include <unistd.h>
#include <libgen.h>
#include <cmocka.h>
#include "../../src/scanner.c"

/**
 * @brief Test that example_main() correctly processes a valid expression
 *        and produces expected output.
 *
 * This integration test verifies the complete application behavior including
 * output formatting.
 */
static void testScannerGetNextChar(void **state)
{
  // no-op. tells the compiler state is intentionally unused. It suppresses "unused parameter" 
  (void)state;

  // open the file
  char currentFile[512];
  strncpy(currentFile, __FILE__, sizeof currentFile);
  char *currentDir = dirname(currentFile);

  char relativePath[512];
  snprintf(relativePath, sizeof relativePath, "%s/%s", currentDir, "expressions/input00.txt");

  char cwdArray[4096];
  char* cwd = getcwd(cwdArray, sizeof cwdArray);
  assert_non_null(cwd);

  //const char *rel = "relative/file.txt";
  char abs[4096];
  snprintf(abs, sizeof abs, "%s/%s", cwd, relativePath);
  printf("Absolute (not resolved): %s\n", abs);

  //char resolved[PATH_MAX];
  //char* absolutPath = realpath(path, resolved);
  //assert_non_null(absolutPath);

  const FILE* pFile = fopen(abs, "r");
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

int scannerRunner(void)
{
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(testScannerGetNextChar),
  };

  return cmocka_run_group_tests_name("Scanner", tests, NULL, NULL);
}
