#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <libgen.h>

#include "zaalStrings.h"
#include "../zutil.h"

bool charPointerToArray(const char * const inputString,
    char outputString[], uint32_t maxStringSize)
{
  bool result = false;
  (void)memset(outputString, 0, maxStringSize);

  if(NULL != inputString) {
    ssize_t length = strlen(inputString);
    if(length > 0) {
      if(length < maxStringSize) {
        uint32_t index = 0;
        while (inputString[index] != '\0') {
          outputString[index] = inputString[index];
          index++;
        }
        // put '\0' to denot end of string
        outputString[index] = '\0';
        result = true;
      }
      else {
        fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> length >= maxStringSize\n",
          errorType(INFO), __FILE__, __func__, __LINE__);
      }
    }
    else {
      fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> length <= 0\n",
        errorType(INFO), __FILE__, __func__, __LINE__);
    }
  }
  else {
    fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> inputString is NULL\n",
      errorType(INFO), __FILE__, __func__, __LINE__);
  }
  return result;
}
 
bool reverseString(const char * const inputString,
    char outputString[], uint32_t maxStringSize)
{
  bool result = false;
  (void)memset(outputString, 0, maxStringSize);

  if(NULL != inputString) {
    ssize_t inputStringLength = strlen(inputString);
    if(inputStringLength > 0) {
      // if there's '\0' at the end, just skip it.
      if(inputString[inputStringLength] == '\0') {
        inputStringLength--;
      }
      if(inputStringLength < maxStringSize) {
        uint32_t outputStringIndex = 0U;
        while (inputStringLength >= 0) {
          outputString[outputStringIndex] = inputString[inputStringLength];
          inputStringLength--;
          outputStringIndex++;
        }
        // put '\0' to denot end of string
        outputString[outputStringIndex] = '\0';
        result = true;
      }
      else {
        fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> inputStringLength >= maxStringSize\n",
          errorType(INFO), __FILE__, __func__, __LINE__);
      }
    }
    else {
      fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> inputStringLength <= 0\n",
        errorType(INFO), __FILE__, __func__, __LINE__);
    }
  }
  else {
    fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> inputString is NULL\n",
      errorType(INFO), __FILE__, __func__, __LINE__);
  }
  return result;
}

bool getExtensionOfFile(const char * const fileName,
   char extName[], uint32_t extNameSize)
{
  bool result = false;
  (void)memset(extName, 0, extNameSize);

  if(NULL != fileName) {
    uint32_t length = strlen(fileName);
    if(length > 0) {
      char* tempExtName = strrchr(fileName, '.');
      if(NULL != tempExtName) {
        if(strlen(tempExtName) > 1) {
          ++tempExtName;
          if(true == charPointerToArray(tempExtName, extName, extNameSize)) {
            result = true;
          }
        }
      }
    }
    else if (0 == length) {
      fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> path is empty\n",
        errorType(INFO), __FILE__, __func__, __LINE__);
    }
    else {
      fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> length < 0\n",
        errorType(INFO), __FILE__, __func__, __LINE__);
    }
  }
  return result;
}

bool removeSubDirectoryFromPath(char * path,
    uint32_t subDirsToBeRemove)
{
  bool result = false;
  if(subDirsToBeRemove > 0) {
    if(NULL != path) {
      uint32_t length = strlen(path);
      if(length > 0) {
        // skip '\0'
        ssize_t i = (ssize_t)length - 1;

        // skip trailing slashes
        while (i >= 0 && path[i] == '/') --i;

        uint32_t removedSubDirs = 0;
        while (i >= 0) {
          if (path[i] == '/') {
            path[i] = '\0';
            --i;
            removedSubDirs++;
            if (removedSubDirs == subDirsToBeRemove) {
              result = true;
              break;
            }
          }
          else {
            // shrink the string by putting string NUL terminator at path[i]
            path[i] = '\0';
            --i;
          }
        }
      }
      else if (0 == length) {
        fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> path is empty\n",
          errorType(INFO), __FILE__, __func__, __LINE__);
      }
      else {
        fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> length < 0\n",
          errorType(INFO), __FILE__, __func__, __LINE__);
      }
    }
    else {
      fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> path is NULL\n",
        errorType(INFO), __FILE__, __func__, __LINE__);
    }
  }
  else {
    result = true;
  }
  
  return result;
}
