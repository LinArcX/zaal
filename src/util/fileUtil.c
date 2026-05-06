#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <libgen.h>

#include "fileUtil.h"
#include "../zutil.h"

/**
 * @brief remove sub-directories from a path
 *
 * @example subDirsToBeRemove = 2 -> "/mnt/D/workspace/project/zaal/build/tests" --> "/mnt/D/workspace/project/zaal"
 * @param path 
 * @param subDirsToBeRemove
 * @return true if opeation is successful, otherwise false
 */
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
        fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> path is empty\n\n",
          errorType(INFO), __FILE__, __func__, __LINE__);
      }
      else {
        fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> length < 0\n\n",
          errorType(INFO), __FILE__, __func__, __LINE__);
      }
    }
    else {
      fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d] -> path is NULL\n\n",
        errorType(INFO), __FILE__, __func__, __LINE__);
    }
  }
  else {
    result = true;
  }
  
  return result;
}
