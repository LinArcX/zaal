#include "fileUtil.h"
#include "../zutil.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <libgen.h>

/**
 * @brief remove sub-directories from a path
 *
 * @example numbersOfSubDirsToRemove = 2 -> "/mnt/D/workspace/project/zaal/build/tests" --> "/mnt/D/workspace/project/zaal"
 * @param path 
 * @param numbersOfSubDirsToRemove
 * @return true if opeation is successful, otherwise false
 */
bool removeSubDirectoryFromPath(char * path,
    uint32_t subDirsToBeRemove)
{
  bool result = false;
  if(NULL != path) {
    uint32_t length = strlen(path);
    if(length > 0) {
      // skip '\0'
      ssize_t i = (ssize_t)length - 1;

      // skip trailing slashes
      while (i >= 0 && path[i] == '/') --i;

      uint32_t removedSubDirs = 0;
      while (i >= 0) {
        if(isalnum(path[i])) {
          // shrink the string by putting string NUL terminator at path[i]
          path[i] = '\0';
          --i;
        }
        else if (path[i] == '/') {
          path[i] = '\0';
          --i;
          removedSubDirs++;
          if (removedSubDirs == subDirsToBeRemove) {
            result = true;
            break;
          }
        }
        else {
          fprintf(stderr, "ERROR --> [%s, %s, %s(), %d], unknown cahr\n",
            errorType(ERROR_ZAAL), __FILE__, __func__, __LINE__);
        }
      }
    }
    else {
      fprintf(stderr, "ERROR --> [%s, %s, %s(), %d], length < 0\n",
        errorType(ERROR_ZAAL), __FILE__, __func__, __LINE__);
    }
  }
  else {
    fprintf(stderr, "ERROR --> [%s, %s, %s(), %d], path is NULL\n",
      errorType(ERROR_ZAAL), __FILE__, __func__, __LINE__);
  }
  return result;
}

const char * const getProjectRootPath()
{
  // open the file
  char currentFile[512];
  strncpy(currentFile, __FILE__, sizeof currentFile);

  // "./src/util"
  char *currentDir = dirname(currentFile);

  //char relativePath[512];
  //snprintf(relativePath, sizeof relativePath, "%s/%s", currentDir, "expressions/input00.txt");

  char cwdArray[4096];
  // "/mnt/D/workspace/c/active/zaal/build/tests" 
  char* cwd = getcwd(cwdArray, sizeof cwdArray);
  //assert_non_null(cwd);

  //const char *rel = "relative/file.txt";
  //char abs[4096];
  //snprintf(abs, sizeof abs, "%s/%s", cwd, relativePath);
  //printf("Absolute (not resolved): %s\n", abs);

  ////char resolved[PATH_MAX];
  ////char* absolutPath = realpath(path, resolved);
  ////assert_non_null(absolutPath);

  //const FILE* pFile = fopen(abs, "r");
  ////assert_non_null(pFile);
}


//   if (!path || numbersOfSubDirsToRemove == 0) return false;
//    size_t len = strlen(path);
//    if (len == 0) return false;
//
//    // start at last character
//    ssize_t i = (ssize_t)len - 1;
//
//    // skip trailing slashes
//    while (i >= 0 && path[i] == '/') --i;
//
//    // remove up to n components
//    uint32_t removed = 0;
//    while (i >= 0 && removed < numbersOfSubDirsToRemove) {
//        // move back to previous slash
//        while (i >= 0 && path[i] != '/') {
//            --i;
//        }
//        // if we found a slash, terminate the string there (removes the component)
//        if (i >= 0 && path[i] == '/') {
//            path[i] = '\0';
//            --i;           // continue searching before this slash
//            ++removed;
//            // skip any additional consecutive slashes before next component
//            while (i >= 0 && path[i] == '/') --i;
//        }
//    }
//
//    return removed > 0;
//
      ////for (size_t i = length;; i--) {
      //  if (path[i] == '\0') {
      //    continue;
      //  }
      //  
      ////}
      ///
      ///  //   // remove trailing / if there's one
 //    else if (path[length - 1] == '\\') {
  //      // we shrink the string by putting string NUL terminator
  //      path[length - 1] = '\0';
  //      // length should be reduce also
  //      length--;
  //    }
  //    else {

  //    }
  //  }
  // 
  //}


