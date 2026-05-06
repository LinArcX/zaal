#include <cmocka.h>
#include <unistd.h>

#include "../../src/scanner.c"
#include "../../src/util/fileUtil.h"

void setup(FILE** pFile, char* path)
{
  char abs[4096];
  char cwd[4096];
  getcwd(cwd, sizeof cwd);
  if(removeSubDirectoryFromPath(cwd, 2)) {
    snprintf(abs, sizeof abs, "%s/%s", cwd, path);
  }

  *pFile = fopen(abs, "r");
  if (NULL == *pFile) {
    fprintf(stderr, "[%s: <%s> | %s() | %d] -> pFile is NULL\n",
      errorType(INFO), __FILE__, __func__, __LINE__);
    pFile = NULL;
  }
  else {
  }
}

void tearDown(FILE* pFile)
{
  if (NULL != pFile) {
    if (fclose(pFile) != 0) {
      fprintf(stderr, "[%s: <%s> | %s() | %d] -> can't close the file\n",
        errorType(INFO), __FILE__, __func__, __LINE__);
      //perror("fclose");
    }
    pFile = NULL;
  }
}
/**
 * @brief testing getNextChar() function
 *
 * @param state 
 */
static void getNextChar_normal(void **state)
{
  // no-op. tells the compiler state is intentionally unused. It suppresses "unused parameter" 
  (void)state;
  FILE* pFile = NULL;
  uint32_t line = 0;
  uint32_t putBackChar = 0;
  setup(&pFile, "tests/scanner/expressions/input00.txt"); // contains: 2 + 3

  assert_int_equal(50, getNextChar(pFile, &line, &putBackChar)); // 50 = '2'
  assert_int_equal(32, getNextChar(pFile, &line, &putBackChar)); // 32 = SPACE
  assert_int_equal(43, getNextChar(pFile, &line, &putBackChar)); // 43 = +
  assert_int_equal(32, getNextChar(pFile, &line, &putBackChar)); // 32 = SPACE
  assert_int_equal(51, getNextChar(pFile, &line, &putBackChar)); // 51 = '3'
  assert_int_equal(10, getNextChar(pFile, &line, &putBackChar)); // 10 = LF
  assert_int_equal(-1, getNextChar(pFile, &line, &putBackChar)); // -1 = EOF
  assert_int_equal(-1, getNextChar(pFile, &line, &putBackChar)); // -1 = EOF
 
  tearDown(pFile);
}

int scannerRunner(void)
{
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(getNextChar_normal),
  };

  return cmocka_run_group_tests_name("Scanner", tests, NULL, NULL);
}
