#include <cmocka.h>

#include "../../src/util/fileUtil.h"

static void testFileUtilRemoveSubDirectoryFromPath(void **state)
{
  // no-op. tells the compiler state is intentionally unused. It suppresses "unused parameter" 
  (void)state;

  // don't use char * path, since it's string literal and string literals are read-only in c!
  char path[]= "/mnt/D/workspace/project/zaal/build/tests";
  assert_true(removeSubDirectoryFromPath(path, 2));
  assert_string_equal(path, "/mnt/D/workspace/project/zaal");

  char pathTwo[]= "/mnt/D/";
  assert_true(removeSubDirectoryFromPath(pathTwo, 1));
  assert_string_equal(pathTwo, "/mnt");

  char pathThree[]= "/mnt/workspace/zaal/build/";
  assert_true(removeSubDirectoryFromPath(pathThree, 3));
  assert_string_equal(pathThree, "/mnt");

  char pathFour[]= "/mnt/workspace/zaal/build/////";
  assert_true(removeSubDirectoryFromPath(pathFour, 2));
  assert_string_equal(pathFour, "/mnt/workspace");
}

int fileUtilRunner(void)
{
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(testFileUtilRemoveSubDirectoryFromPath),
  };

  return cmocka_run_group_tests_name("FileUtil", tests, NULL, NULL);
}
