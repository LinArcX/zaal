#include <cmocka.h>

#include "../../src/util/zaalStrings.h"

// ---------------- charPointerToArray() ---------------- //
static void charPointerToArray_empty(void **state)
{
  // no-op. tells the compiler state is intentionally unused. It suppresses "unused parameter" 
  (void)state;

  const char * const inputString = "";
  char outputString[MAX_STRING_SIZE] = {0};

  assert_false(charPointerToArray(inputString, outputString, MAX_STRING_SIZE));
  assert_string_equal(inputString, "");
  assert_string_equal(outputString, "");
}

static void charPointerToArray_oneChar(void **state)
{
  const char * const inputString = "b";
  char outputString[MAX_STRING_SIZE] = {0};

  assert_true(charPointerToArray(inputString, outputString, MAX_STRING_SIZE));
  assert_string_equal(inputString, "b");
  assert_string_equal(outputString, "b");
}

static void charPointerToArray_normalString(void **state)
{
  const char * const inputString = "this is a normal string.";
  char outputString[MAX_STRING_SIZE] = {0};

  assert_true(charPointerToArray(inputString, outputString, MAX_STRING_SIZE));
  assert_string_equal(inputString, "this is a normal string.");
  assert_string_equal(outputString, "this is a normal string.");
}

static void charPointerToArray_normalStringWithStrangeChar(void **state)
{
  const char * const inputString = ">/?   such a !strange +-_@#~ string:))^~.";
  char outputString[MAX_STRING_SIZE] = {0};

  assert_true(charPointerToArray(inputString, outputString, MAX_STRING_SIZE));
  assert_string_equal(inputString, ">/?   such a !strange +-_@#~ string:))^~.");
  assert_string_equal(outputString, ">/?   such a !strange +-_@#~ string:))^~.");
}

static void charPointerToArray_veryBigString(void **state)
{
  const char * const verbigString = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    ";
  char outputString[MAX_STRING_SIZE] = {0};

  assert_false(charPointerToArray(verbigString, outputString, MAX_STRING_SIZE));
  assert_string_equal(verbigString, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    ");
  assert_string_equal(outputString, "");
}

// ---------------- reverseString() ---------------- //
static void reverseString_empty(void **state)
{
  const char * const inputString = "";
  char outputString[MAX_STRING_SIZE] = {0};

  assert_false(reverseString(inputString, outputString, MAX_STRING_SIZE));
  assert_string_equal(inputString, "");
  assert_string_equal(outputString, "");
}

static void reverseString_oneChar(void **state)
{
  const char * const inputString = "z";
  char outputString[MAX_STRING_SIZE] = {0};

  assert_true(reverseString(inputString, outputString, MAX_STRING_SIZE));
  assert_string_equal(inputString, "z");
  assert_string_equal(outputString, "z");
}

static void reverseString_normalString(void **state)
{
  const char * const inputString = "this is a normal string.";
  char outputString[MAX_STRING_SIZE] = {0};

  assert_true(reverseString(inputString, outputString, MAX_STRING_SIZE));
  assert_string_equal(inputString, "this is a normal string.");
  assert_string_equal(outputString, ".gnirts lamron a si siht");
}

static void reverseString_normalStringWithStrangeChars(void **state)
{
  const char * const inputString = ">/?   such a !strange +-_@#~ string:))^~.";
  char outputString[MAX_STRING_SIZE] = {0};

  assert_true(reverseString(inputString, outputString, MAX_STRING_SIZE));
  assert_string_equal(inputString, ">/?   such a !strange +-_@#~ string:))^~.");
  assert_string_equal(outputString, ".~^)):gnirts ~#@_-+ egnarts! a hcus   ?/>");
}

static void reverseString_veryBigString(void **state)
{
  const char * const verbigString = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    ";
  char outputString[MAX_STRING_SIZE] = {0};

  assert_false(reverseString(verbigString, outputString, MAX_STRING_SIZE));
  assert_string_equal(verbigString, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
                                    ");
  assert_string_equal(outputString, "");
}

// ---------------- getExtensionOfFile() ---------------- //
static void getExtensionOfFile_emptyFileName(void **state)
{
  char file[]= "";
  char ext[MAX_STRING_SIZE] = {0};

  assert_false(getExtensionOfFile(file, ext, MAX_FILE_EXTENSION_SIZE));
  assert_string_equal(file, "");
  assert_string_equal(ext, "");
}

static void getExtensionOfFile_withoutExtension(void **state)
{
  char file[]= "fileName";
  char ext[MAX_STRING_SIZE] = {0};

  assert_false(getExtensionOfFile(file, ext, MAX_FILE_EXTENSION_SIZE));
  assert_string_equal(file, "fileName");
  assert_string_equal(ext, "");
}

static void getExtensionOfFile_multipleDots(void **state)
{
  char file[] = "avatar.jpg.zip";
  char ext[MAX_STRING_SIZE] = {0};

  assert_true(getExtensionOfFile(file, ext, MAX_FILE_EXTENSION_SIZE));
  assert_string_equal(file, "avatar.jpg.zip");
  assert_string_equal(ext, "zip");
}

static void getExtensionOfFile_onlyOneDot(void **state)
{
  char file[]= "document.txt";
  char ext[MAX_STRING_SIZE] = {0};

  assert_true(getExtensionOfFile(file, ext, MAX_FILE_EXTENSION_SIZE));
  assert_string_equal(file, "document.txt");
  assert_string_equal(ext, "txt");
}

// ---------------- removeSubDirectoryFromPath() ---------------- //
static void removeSubDirectoryFromPath_normalPath(void **state)
{
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

int zaalStringsRunner(void)
{
  const struct CMUnitTest tests[] = {
    // ---------------- charPointerToArray() ---------------- //
    cmocka_unit_test(charPointerToArray_empty),
    cmocka_unit_test(charPointerToArray_oneChar),
    cmocka_unit_test(charPointerToArray_normalString),
    cmocka_unit_test(charPointerToArray_normalStringWithStrangeChar),
    cmocka_unit_test(charPointerToArray_veryBigString),
    
    // ---------------- reverseString() ---------------- //
    cmocka_unit_test(reverseString_empty),
    cmocka_unit_test(reverseString_oneChar),
    cmocka_unit_test(reverseString_normalString),
    cmocka_unit_test(reverseString_normalStringWithStrangeChars),
    cmocka_unit_test(reverseString_veryBigString),
 
    // ---------------- getExtensionOfFile() ---------------- //
    cmocka_unit_test(getExtensionOfFile_emptyFileName),
    cmocka_unit_test(getExtensionOfFile_withoutExtension),
    cmocka_unit_test(getExtensionOfFile_multipleDots),
    cmocka_unit_test(getExtensionOfFile_onlyOneDot),

    // ---------------- removeSubDirectoryFromPath() ---------------- //
    cmocka_unit_test(removeSubDirectoryFromPath_normalPath),
    cmocka_unit_test(removeSubDirectoryFromPath_slashAtEnd),
    cmocka_unit_test(removeSubDirectoryFromPath_justSlash),
    cmocka_unit_test(removeSubDirectoryFromPath_specialChars),
    cmocka_unit_test(removeSubDirectoryFromPath_highNumberForSubDirToRemove),
    cmocka_unit_test(removeSubDirectoryFromPath_negativeNumberForSubDirToRemove),
    cmocka_unit_test(removeSubDirectoryFromPath_zeroAsNumberForSubDirToRemove),
    cmocka_unit_test(removeSubDirectoryFromPath_emptyPath),
  };

  return cmocka_run_group_tests_name("StringTest", tests, NULL, NULL);
}
