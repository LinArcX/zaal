#include <cmocka.h>

#include "../../src/util/zaalMemMap.h"

// ---------------- mapFileToMemory() ---------------- //
static void mapFileToMemory_emptyFileName(void **state)
{
  const char * const fileName = "";
  int* fd = NULL;
  struct stat* st = NULL;
  char* mapped = NULL;

  assert_false(mapFileToMemory(fileName, fd, st, mapped));
  assert_null(fd);
  assert_null(st);
  assert_null(mapped);

  // release the resources
  assert_false(unmapFileFromMemory(mapped, fd, st));
  assert_null(fd);
  assert_null(st);
  assert_null(mapped);
}

static void mapFileToMemory_emptyFileContent(void **state)
{
  const char * const fileName = "tests/assets/empty.txt";
  int* fd = NULL;
  struct stat* st = NULL;
  char* mapped = NULL;

  assert_false(mapFileToMemory(fileName, fd, st, mapped));
  assert_null(fd);
  assert_null(st);
  assert_null(mapped);

  // release the resources
  assert_false(unmapFileFromMemory(mapped, fd, st));
  assert_null(fd);
  assert_null(st);
  assert_null(mapped);
}

static void mapFileToMemory_wrongFileName(void **state)
{
  const char * const fileName = "tests/assets/agaghvagagh.txt";
  int* fd = NULL;
  struct stat* st = NULL;
  char* mapped = NULL;

  assert_false(mapFileToMemory(fileName, fd, st, mapped));
  assert_null(fd);
  assert_null(st);
  assert_null(mapped);

  // release the resources
  assert_false(unmapFileFromMemory(mapped, fd, st));
  assert_null(fd);
  assert_null(st);
  assert_null(mapped);
}

static void mapFileToMemory_normalFile(void **state)
{
  const char * const fileName = "tests/assets/normalFile.txt";
  int* fd = NULL;
  struct stat* st = NULL;
  char* mapped = NULL;

  assert_false(mapFileToMemory(fileName, fd, st, mapped));
  assert_non_null(fd);
  assert_non_null(st);
  assert_non_null(mapped);

  // read some chars inside file
  assert_int_equal(52, mapped[0]);            // 52 = '4'
  assert_int_equal(52, mapped[st->st_size]);  // 52 = '4'

  // release the resources
  assert_false(unmapFileFromMemory(mapped, fd, st));
  assert_null(fd);
  assert_null(st);
  assert_null(mapped);
}

// ---------------- unmapFileFromMemory() ---------------- //
static void unmapFileToMemory_withoutMappingFile(void **state)
{
  int* fd = NULL;
  struct stat* st = NULL;
  char* mapped = NULL;

  // release the resources
  assert_false(unmapFileFromMemory(mapped, fd, st));
  assert_null(fd);
  assert_null(st);
  assert_null(mapped);
}

// ---------------- getNextCharFromMemMap() ---------------- //
static void getNextCharFromMemMap_firstAndLastChars(void **state)
{
  const char * const fileName = "tests/assets/normalFile.txt";
  int* fd = NULL;
  struct stat* st = NULL;
  char* mapped = NULL;

  assert_false(mapFileToMemory(fileName, fd, st, mapped));
  assert_non_null(fd);
  assert_non_null(st);
  assert_non_null(mapped);

  // read some chars inside file
  assert_int_equal(52, mapped[0]);            // 52 = '4'
  assert_int_equal(52, mapped[st->st_size]);  // 52 = '4'


  // release the resources
  assert_false(unmapFileFromMemory(mapped, fd, st));
  assert_null(fd);
  assert_null(st);
  assert_null(mapped);
}

static void getNextCharFromMemMap_RandomAccess(void **state)
{
  const char * const fileName = "tests/assets/normalFile.txt";
  int* fd = NULL;
  struct stat* st = NULL;
  char* mapped = NULL;

  assert_false(mapFileToMemory(fileName, fd, st, mapped));
  assert_non_null(fd);
  assert_non_null(st);
  assert_non_null(mapped);

  // read some chars inside file
  assert_int_equal(52, mapped[st->st_size / 2] + 7);     // 52 = '4'
  assert_int_equal(52, mapped[4]);  // 52 = '4'


  // release the resources
  assert_false(unmapFileFromMemory(mapped, fd, st));
  assert_null(fd);
  assert_null(st);
  assert_null(mapped);
}

static void getNextCharFromMemMap_outOfRangeAccess(void **state)
{
  const char * const fileName = "tests/assets/normalFile.txt";
  int* fd = NULL;
  struct stat* st = NULL;
  char* mapped = NULL;
  char ch = 0;

  assert_false(mapFileToMemory(fileName, fd, st, mapped));
  assert_non_null(fd);
  assert_non_null(st);
  assert_non_null(mapped);

  // read some chars out of range
  assert_true(getNextCharFromMemMap(mapped, st, &ch));
  assert_int_equal('a', ch);

  // release the resources
  assert_false(unmapFileFromMemory(mapped, fd, st));
  assert_null(fd);
  assert_null(st);
  assert_null(mapped);
}

int zaalMemMapRunner(void)
{
  const struct CMUnitTest tests[] = {
    // ---------------- mapFileToMemory() ---------------- //
    cmocka_unit_test(mapFileToMemory_emptyFileName),
    cmocka_unit_test(mapFileToMemory_emptyFileContent),
    cmocka_unit_test(mapFileToMemory_wrongFileName),
    cmocka_unit_test(mapFileToMemory_normalFile),

    // ---------------- unmapFileFromMemory() ---------------- //
    cmocka_unit_test(unmapFileToMemory_withoutMappingFile),

    // ---------------- getNextCharFromMemMap() ---------------- //
    cmocka_unit_test(getNextCharFromMemMap_firstAndLastChars),
    cmocka_unit_test(getNextCharFromMemMap_RandomAccess),
    cmocka_unit_test(getNextCharFromMemMap_outOfRangeAccess),
  };

  return cmocka_run_group_tests_name("MemMap", tests, NULL, NULL);
}
