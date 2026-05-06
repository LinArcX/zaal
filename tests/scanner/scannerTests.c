#include <cmocka.h>
#include <unistd.h>

#include "../../src/scanner.c"
#include "../../src/util/fileUtil.h"

/**
 *    ASCII tables in hex and decimal.
      EOF=-1

          2 3 4 5 6 7        0    10  20   30  40  50  60  70  80  90  100  110  120
        -------------     -- ------------------------------------------------------
       0:   0 @ P ` p     0: NULL LF  DC4  RS  (   2   <   F   P   Z    d    n    x
       1: ! 1 A Q a q     1: SOH  VT  NAK  US  )   3   =   G   Q   [    e    o    y
       2: " 2 B R b r     2: STX  FF  SYN  SPC *   4   >   H   R   \    f    p    z
       3: # 3 C S c s     3: ETX  CR  ETB  !   +   5   ?   I   S   ]    g    q    {
       4: $ 4 D T d t     4: EQT  SO  CAN  "   ,   6   @   J   T   ^    h    r    |
       5: % 5 E U e u     5: ENQ  SI  EM   #   -   7   A   K   U   _    i    s    }
       6: & 6 F V f v     6: ACK  DEL SUB  $   .   8   B   L   V   `    j    t    ~
       7: ' 7 G W g w     7: BEL  DC1 ESC  %   /   9   C   M   W   a    k    u   DEL
       8: ( 8 H X h x     8: BS   DC2 FS   &   0   :   D   N   X   b    l    v
       9: ) 9 I Y i y     9: TAB  DC3 GS   '   1   ;   E   O   Y   c    m    w   EOF=-1
       A: * : J Z j z
       B: + ; K [ k {
       C: , < L \ l |
       D: - = M ] m }
       E: . > N ^ n ~
       F: / ? O _ o DEL
 */

/**
 * @brief setup pFile according to path
 *
 * @param pFile 
 * @param path 
 */
void setup(FILE** pFile, char* path)
{
  char abs[4096];
  char cwd[4096];
  getcwd(cwd, sizeof cwd);
  if(removeSubDirectoryFromPath(cwd, 2)) {
    snprintf(abs, sizeof abs, "%s/%s", cwd, path);

    *pFile = fopen(abs, "r");
    if (NULL == *pFile) {
      fprintf(stderr, "[%s: <%s> | %s() | %d] -> pFile is NULL\n",
        errorType(INFO), __FILE__, __func__, __LINE__);
      pFile = NULL;
    }
  }
}

/**
 * @brief release the memory allocated by pFile
 *
 * @param pFile 
 */
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
 * @brief getNextChar sinle line test
 *
 * @param state 
 */
static void getNextChar_singleLine(void **state)
{
  // no-op. tells the compiler state is intentionally unused. It suppresses "unused parameter" 
  (void)state;
  FILE* pFile = NULL;
  uint32_t line = 0;
  uint32_t putBackChar = 0;

  // 2 + 3 *5-8/ 3
  setup(&pFile, "tests/scanner/assets/singleLine.txt");

  assert_int_equal(50, getNextChar(pFile, &line, &putBackChar)); // 50 = '2'
  assert_int_equal(32, getNextChar(pFile, &line, &putBackChar)); // 32 = SPACE
  assert_int_equal(43, getNextChar(pFile, &line, &putBackChar)); // 43 = +
  assert_int_equal(32, getNextChar(pFile, &line, &putBackChar)); // 32 = SPACE
  assert_int_equal(51, getNextChar(pFile, &line, &putBackChar)); // 51 = '3'
  assert_int_equal(32, getNextChar(pFile, &line, &putBackChar)); // 32 = SPACE
  assert_int_equal(42, getNextChar(pFile, &line, &putBackChar)); // 42 = *
  assert_int_equal(53, getNextChar(pFile, &line, &putBackChar)); // 55 = 5
  assert_int_equal(45, getNextChar(pFile, &line, &putBackChar)); // 55 = -
  assert_int_equal(56, getNextChar(pFile, &line, &putBackChar)); // 56 = 8
  assert_int_equal(47, getNextChar(pFile, &line, &putBackChar)); // 47 = /
  assert_int_equal(32, getNextChar(pFile, &line, &putBackChar)); // 32 = SPACE
  assert_int_equal(51, getNextChar(pFile, &line, &putBackChar)); // 51 = '3'
  assert_int_equal(10, getNextChar(pFile, &line, &putBackChar)); // 10 = LF
  assert_int_equal(-1, getNextChar(pFile, &line, &putBackChar)); // -1 = EOF
  assert_int_equal(-1, getNextChar(pFile, &line, &putBackChar)); // -1 = EOF
 
  tearDown(pFile);
}

/**
 * @brief entry point to register and run scanner TCs
 *
 * @return number of failed TCs
 */
int scannerRunner(void)
{
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(getNextChar_singleLine),
  };

  return cmocka_run_group_tests_name("Scanner", tests, NULL, NULL);
}
