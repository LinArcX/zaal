#include <cmocka.h>

#include "../../src/util/fileUtil.h"

static void removeSubDirectoryFromPath_normalPath(void **state)
{
  // no-op. tells the compiler state is intentionally unused. It suppresses "unused parameter" 
  (void)state;

  // don't use "char * path", since it's string literal and string literals are read-only in c!
  // use char path[] instead :)
  char path[]= "/mnt/D/workspace/project/zaal/build/tests";
  assert_true(removeSubDirectoryFromPath(path, 2));
  assert_string_equal(path, "/mnt/D/workspace/project/zaal");

  char pathTwo[]= "/mnt/workspace/zaal/build/";
  assert_true(removeSubDirectoryFromPath(pathTwo, 3));
  assert_string_equal(pathTwo, "/mnt");
}

static void removeSubDirectoryFromPath_slashAtEnd(void **state)
{
  char path[]= "/mnt/D/";
  assert_true(removeSubDirectoryFromPath(path, 1));
  assert_string_equal(path, "/mnt");

  char pathTwo[]= "/mnt/D/test////";
  assert_true(removeSubDirectoryFromPath(pathTwo, 1));
  assert_string_equal(pathTwo, "/mnt/D");

  char pathThree[]= "/mnt/workspace/zaal/build/////";
  assert_true(removeSubDirectoryFromPath(pathThree, 2));
  assert_string_equal(pathThree, "/mnt/workspace");
}

static void removeSubDirectoryFromPath_justSlash(void **state)
{
  char path[]= "/";
  assert_false(removeSubDirectoryFromPath(path, 1));
  assert_string_equal(path, "/");

  char pathTwo[]= "////";
  assert_false(removeSubDirectoryFromPath(pathTwo, 1));
  assert_string_equal(pathTwo, "////");
}

static void removeSubDirectoryFromPath_specialChars(void **state)
{
  char path[]= "/mnt/workspace/zaal/build/+prefix/";
  assert_true(removeSubDirectoryFromPath(path, 2));
  assert_string_equal(path, "/mnt/workspace/zaal");

  char pathTwo[]= "/mnt/workspace/zaal/build/ha ha a b/";
  assert_true(removeSubDirectoryFromPath(pathTwo, 3));
  assert_string_equal(pathTwo, "/mnt/workspace");

  char pathThree[]= "/mnt/workspace/zaal/build/special_/";
  assert_true(removeSubDirectoryFromPath(pathThree, 3));
  assert_string_equal(pathThree, "/mnt/workspace");

  char pathFour[]= "/mnt/workspace/zaal/build/_-special_ a/";
  assert_true(removeSubDirectoryFromPath(pathFour, 2));
  assert_string_equal(pathFour, "/mnt/workspace/zaal");
}

static void removeSubDirectoryFromPath_highNumberForSubDirToRemove(void **state)
{
  char path[]= "/mnt/D/workspace/";
  assert_false(removeSubDirectoryFromPath(path, 4));
  assert_string_equal(path, "");
}

static void removeSubDirectoryFromPath_negativeNumberForSubDirToRemove(void **state)
{
  char path[]= "/mnt/D/workspace/";
  assert_false(removeSubDirectoryFromPath(path, -1));
  assert_string_equal(path, "");
}

static void removeSubDirectoryFromPath_zeroAsNumberForSubDirToRemove(void **state)
{
  char path[]= "/mnt/D/workspace/";
  assert_true(removeSubDirectoryFromPath(path, 0));
  assert_string_equal(path, "/mnt/D/workspace/");
}

static void removeSubDirectoryFromPath_emptyPath(void **state)
{
  char path[]= "";
  assert_false(removeSubDirectoryFromPath(path, 2));
  assert_string_equal(path, "");

  char pathTwo[]= "    ";
  assert_false(removeSubDirectoryFromPath(pathTwo, 2));
  assert_string_equal(pathTwo, "");
}

int fileUtilRunner(void)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(removeSubDirectoryFromPath_normalPath),
    cmocka_unit_test(removeSubDirectoryFromPath_slashAtEnd),
    cmocka_unit_test(removeSubDirectoryFromPath_justSlash),
    cmocka_unit_test(removeSubDirectoryFromPath_specialChars),
    cmocka_unit_test(removeSubDirectoryFromPath_highNumberForSubDirToRemove),
    cmocka_unit_test(removeSubDirectoryFromPath_negativeNumberForSubDirToRemove),
    cmocka_unit_test(removeSubDirectoryFromPath_zeroAsNumberForSubDirToRemove),
    cmocka_unit_test(removeSubDirectoryFromPath_emptyPath),
  };

  return cmocka_run_group_tests_name("FileUtil", tests, NULL, NULL);
}
