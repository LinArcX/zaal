#include <cmocka.h>
#include <unistd.h>

#include "../../src/scanner.c"
#include "../../src/util/zaalStrings.h"

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

// ---------------- getNextChar() ---------------- //
/**
 * @brief testing all characters
 *
 * @param state 
 */
static void getNextChar_allChars(void **state)
{
  // no-op. tells the compiler state is intentionally unused. It suppresses "unused parameter" 
  (void)state;
  FILE* pFile = NULL;
  uint32_t line = 0;
  uint32_t putBackChar = 0;

  // 1234567890  !@#$%^&*()-_=+[]{}\|'";:/?.>,<
  // abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ`~
  setup(&pFile, "tests/scanner/assets/allChars.txt");

  assert_int_equal(49, getNextChar(pFile, &line, &putBackChar)); // 49 = '1'
  assert_int_equal(50, getNextChar(pFile, &line, &putBackChar)); // 50 = '2'
  assert_int_equal(51, getNextChar(pFile, &line, &putBackChar)); // 51 = '3'
  assert_int_equal(52, getNextChar(pFile, &line, &putBackChar)); // 52 = '4'
  assert_int_equal(53, getNextChar(pFile, &line, &putBackChar)); // 53 = '5'
  assert_int_equal(54, getNextChar(pFile, &line, &putBackChar)); // 54 = '6'
  assert_int_equal(55, getNextChar(pFile, &line, &putBackChar)); // 55 = '7'
  assert_int_equal(56, getNextChar(pFile, &line, &putBackChar)); // 56 = '8'
  assert_int_equal(57, getNextChar(pFile, &line, &putBackChar)); // 57 = '9'
  assert_int_equal(48, getNextChar(pFile, &line, &putBackChar)); // 48 = '0'

  // in neovim, i rebind TAB to 2Space. that's why :)
  assert_int_equal(32, getNextChar(pFile, &line, &putBackChar)); // 9 = SPC
  assert_int_equal(32, getNextChar(pFile, &line, &putBackChar)); // 9 = SPC
                                                                 
  // we're still on line 0
  assert_int_equal(0, line);
  // and there's no putBackChar
  assert_int_equal(0, putBackChar);
                                                                
  assert_int_equal(33, getNextChar(pFile, &line, &putBackChar)); // 33 = !
  assert_int_equal(64, getNextChar(pFile, &line, &putBackChar)); // 64 = @
  assert_int_equal(35, getNextChar(pFile, &line, &putBackChar)); // 35 = #
  assert_int_equal(36, getNextChar(pFile, &line, &putBackChar)); // 36 = $
  assert_int_equal(37, getNextChar(pFile, &line, &putBackChar)); // 37 = %
  assert_int_equal(94, getNextChar(pFile, &line, &putBackChar)); // 94 = ^
  assert_int_equal(38, getNextChar(pFile, &line, &putBackChar)); // 38 = &
  assert_int_equal(42, getNextChar(pFile, &line, &putBackChar)); // 42 = *
  assert_int_equal(40, getNextChar(pFile, &line, &putBackChar)); // 40 = (
  assert_int_equal(41, getNextChar(pFile, &line, &putBackChar)); // 41 = )
  assert_int_equal(45, getNextChar(pFile, &line, &putBackChar)); // 45 = -
  assert_int_equal(95, getNextChar(pFile, &line, &putBackChar)); // 95 = _
  assert_int_equal(61, getNextChar(pFile, &line, &putBackChar)); // 61 = '='
  assert_int_equal(43, getNextChar(pFile, &line, &putBackChar)); // 43 = +
  assert_int_equal(91, getNextChar(pFile, &line, &putBackChar)); // 91 = [
  assert_int_equal(93, getNextChar(pFile, &line, &putBackChar)); // 93 = ]
  assert_int_equal(123, getNextChar(pFile, &line, &putBackChar)); // 123 = {
  assert_int_equal(125, getNextChar(pFile, &line, &putBackChar)); // 125 = }
  assert_int_equal(92, getNextChar(pFile, &line, &putBackChar)); // 92 = '\'
  assert_int_equal(124, getNextChar(pFile, &line, &putBackChar)); // 124 = |
  assert_int_equal(39, getNextChar(pFile, &line, &putBackChar)); // 39 = '
  assert_int_equal(34, getNextChar(pFile, &line, &putBackChar)); // 34 = "
  assert_int_equal(59, getNextChar(pFile, &line, &putBackChar)); // 59 = ;
  assert_int_equal(58, getNextChar(pFile, &line, &putBackChar)); // 58 = :
  assert_int_equal(47, getNextChar(pFile, &line, &putBackChar)); // 47 = /
  assert_int_equal(63, getNextChar(pFile, &line, &putBackChar)); // 63 = ?
  assert_int_equal(46, getNextChar(pFile, &line, &putBackChar)); // 46 = .
  assert_int_equal(62, getNextChar(pFile, &line, &putBackChar)); // 62 = >
  assert_int_equal(44, getNextChar(pFile, &line, &putBackChar)); // 44 = ,
  assert_int_equal(60, getNextChar(pFile, &line, &putBackChar)); // 60 = <
                                                                 
  assert_int_equal(10, getNextChar(pFile, &line, &putBackChar)); // 10 = LF
                                                                 
  // now we're on line 1
  assert_int_equal(1, line);
  // and there's no putBackChar
  assert_int_equal(0, putBackChar);

  assert_int_equal(97, getNextChar(pFile, &line, &putBackChar)); // 97 = a
  assert_int_equal(98, getNextChar(pFile, &line, &putBackChar)); // 98 = b
  assert_int_equal(99, getNextChar(pFile, &line, &putBackChar)); // 99 = c
  assert_int_equal(100, getNextChar(pFile, &line, &putBackChar)); // 100 = d
  assert_int_equal(101, getNextChar(pFile, &line, &putBackChar)); // 101 = e
  assert_int_equal(102, getNextChar(pFile, &line, &putBackChar)); // 102 = f
  assert_int_equal(103, getNextChar(pFile, &line, &putBackChar)); // 103 = g
  assert_int_equal(104, getNextChar(pFile, &line, &putBackChar)); // 104 = h
  assert_int_equal(105, getNextChar(pFile, &line, &putBackChar)); // 105 = i
  assert_int_equal(106, getNextChar(pFile, &line, &putBackChar)); // 106 = j
  assert_int_equal(107, getNextChar(pFile, &line, &putBackChar)); // 107 = k
  assert_int_equal(108, getNextChar(pFile, &line, &putBackChar)); // 108 = l
  assert_int_equal(109, getNextChar(pFile, &line, &putBackChar)); // 109 = m
  assert_int_equal(110, getNextChar(pFile, &line, &putBackChar)); // 110 = n
  assert_int_equal(111, getNextChar(pFile, &line, &putBackChar)); // 111 = o
  assert_int_equal(112, getNextChar(pFile, &line, &putBackChar)); // 112 = p
  assert_int_equal(113, getNextChar(pFile, &line, &putBackChar)); // 113 = q
  assert_int_equal(114, getNextChar(pFile, &line, &putBackChar)); // 114 = r
  assert_int_equal(115, getNextChar(pFile, &line, &putBackChar)); // 115 = s
  assert_int_equal(116, getNextChar(pFile, &line, &putBackChar)); // 116 = t
  assert_int_equal(117, getNextChar(pFile, &line, &putBackChar)); // 117 = u
  assert_int_equal(118, getNextChar(pFile, &line, &putBackChar)); // 118 = v
  assert_int_equal(119, getNextChar(pFile, &line, &putBackChar)); // 119 = w
  assert_int_equal(120, getNextChar(pFile, &line, &putBackChar)); // 120 = x
  assert_int_equal(121, getNextChar(pFile, &line, &putBackChar)); // 121 = y
  assert_int_equal(122, getNextChar(pFile, &line, &putBackChar)); // 122 = z
                                                                  
  assert_int_equal(32, getNextChar(pFile, &line, &putBackChar)); // 9 = SPC
   // we're still on line 1
  assert_int_equal(1, line);
  // and there's no putBackChar
  assert_int_equal(0, putBackChar);

  assert_int_equal(65, getNextChar(pFile, &line, &putBackChar)); // 65 = A
  assert_int_equal(66, getNextChar(pFile, &line, &putBackChar)); // 66 = B
  assert_int_equal(67, getNextChar(pFile, &line, &putBackChar)); // 67 = C
  assert_int_equal(68, getNextChar(pFile, &line, &putBackChar)); // 68 = D
  assert_int_equal(69, getNextChar(pFile, &line, &putBackChar)); // 69 = E
  assert_int_equal(70, getNextChar(pFile, &line, &putBackChar)); // 70 = F
  assert_int_equal(71, getNextChar(pFile, &line, &putBackChar)); // 71 = G
  assert_int_equal(72, getNextChar(pFile, &line, &putBackChar)); // 72 = H
  assert_int_equal(73, getNextChar(pFile, &line, &putBackChar)); // 73 = I
  assert_int_equal(74, getNextChar(pFile, &line, &putBackChar)); // 74 = J
  assert_int_equal(75, getNextChar(pFile, &line, &putBackChar)); // 75 = K
  assert_int_equal(76, getNextChar(pFile, &line, &putBackChar)); // 76 = L
  assert_int_equal(77, getNextChar(pFile, &line, &putBackChar)); // 77 = M
  assert_int_equal(78, getNextChar(pFile, &line, &putBackChar)); // 78 = N
  assert_int_equal(79, getNextChar(pFile, &line, &putBackChar)); // 79 = O
  assert_int_equal(80, getNextChar(pFile, &line, &putBackChar)); // 80 = P
  assert_int_equal(81, getNextChar(pFile, &line, &putBackChar)); // 81 = Q
  assert_int_equal(82, getNextChar(pFile, &line, &putBackChar)); // 82 = R
  assert_int_equal(83, getNextChar(pFile, &line, &putBackChar)); // 83 = S
  assert_int_equal(84, getNextChar(pFile, &line, &putBackChar)); // 84 = T
  assert_int_equal(85, getNextChar(pFile, &line, &putBackChar)); // 85 = U
  assert_int_equal(86, getNextChar(pFile, &line, &putBackChar)); // 86 = V
  assert_int_equal(87, getNextChar(pFile, &line, &putBackChar)); // 87 = W
  assert_int_equal(88, getNextChar(pFile, &line, &putBackChar)); // 88 = X
  assert_int_equal(89, getNextChar(pFile, &line, &putBackChar)); // 89 = Y
  assert_int_equal(90, getNextChar(pFile, &line, &putBackChar)); // 90 = Z
                                                                 
  assert_int_equal(96, getNextChar(pFile, &line, &putBackChar)); // 96 = `
  assert_int_equal(126, getNextChar(pFile, &line, &putBackChar)); // 126 = ~
                                                                  
  assert_int_equal(10, getNextChar(pFile, &line, &putBackChar)); // 10 = LF
  assert_int_equal(-1, getNextChar(pFile, &line, &putBackChar)); // -1 = EOF
  assert_int_equal(-1, getNextChar(pFile, &line, &putBackChar)); // -1 = EOF
 
  tearDown(pFile);
}

/**
 * @brief testing putBackChar
 *
 * @param state 
 */
static void getNextChar_putBackChar(void **state)
{
  (void)state;
  FILE* pFile = NULL;
  uint32_t line = 0;
  uint32_t putBackChar = 'a';

  // 1234567890  !@#$%^&*()-_=+[]{}\|'";:/?.>,<
  // abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ`~
  setup(&pFile, "tests/scanner/assets/allChars.txt");

  assert_int_equal(97, getNextChar(pFile, &line, &putBackChar)); // 97 = a
                                                                 
  // we're still on line 0
  assert_int_equal(0, line);
  // since we consumed putBackChar, it should be 0
  assert_int_equal(0, putBackChar);

  putBackChar = '(';
  assert_int_equal(40, getNextChar(pFile, &line, &putBackChar)); // 40 = (
  assert_int_equal(0, putBackChar);

  tearDown(pFile);
}

// ---------------- skipWihteSpaces() ---------------- //
/**
 * @brief testing skipWihteSpaces
 *
 * @param state 
 */
static void skipWhiteSpacesTest(void **state)
{
  (void)state;
  FILE* pFile = NULL;
  uint32_t line = 0;
  uint32_t putBackChar = 0;

  setup(&pFile, "tests/scanner/assets/whiteSpaces.txt");

  assert_int_equal(116, skipWhiteSpaces(pFile, &line, &putBackChar)); // 116 = t
  assert_int_equal(97, skipWhiteSpaces(pFile, &line, &putBackChar)); // 97 = a
  assert_int_equal(59, skipWhiteSpaces(pFile, &line, &putBackChar)); // 59 = ;
  assert_int_equal(0, line);
  assert_int_equal(0, putBackChar);
                                                                     
  // passing a random putBackChar to see if skipWhiteSpaces() can fetch it or no
  putBackChar = '(';
  assert_int_equal(40, skipWhiteSpaces(pFile, &line, &putBackChar)); // 40 = (
  assert_int_equal(0, putBackChar);

  assert_int_equal(38, skipWhiteSpaces(pFile, &line, &putBackChar)); // 38 = &
  assert_int_equal(1, line);
  assert_int_equal(0, putBackChar);
                                                                 
  assert_int_equal(48, skipWhiteSpaces(pFile, &line, &putBackChar)); // 48 = 0
  assert_int_equal(5, line);
  assert_int_equal(0, putBackChar);
                                                                 
  assert_int_equal(56, skipWhiteSpaces(pFile, &line, &putBackChar)); // 56 = 8
  assert_int_equal(7, line);
  assert_int_equal(0, putBackChar);
                                                                 
  assert_int_equal(-1, skipWhiteSpaces(pFile, &line, &putBackChar)); // -1 = EOF
                                                                 
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
      // ---------------- getNextChar() ---------------- //
      cmocka_unit_test(getNextChar_allChars),
      cmocka_unit_test(getNextChar_putBackChar),

      // ---------------- skipWihteSpaces() ---------------- //
      cmocka_unit_test(skipWhiteSpacesTest),
  };

  return cmocka_run_group_tests_name("Scanner", tests, NULL, NULL);
}
