#ifndef ZAAL_FILE_UTIL_H
#define ZAAL_FILE_UTIL_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//extern FILE	*pOutFile;
#define ZAAL_MAX_STRING_SIZE 512
#define ZAAL_MAX_FILE_EXTENSION_SIZE 16

enum Z_ERROR {
  E_ZAAL_INFO,
  E_ZAAL_WARNING,
  E_ZAAL_ERROR,
  E_ZAAL_FATAL
};

/**
 * @brief transfer a pointer to an array with pre-defined size
 * @detail it does all the security checks to ensure the pointer points to a healthy memory.
 *
 * @param inputString 
 * @param outputString 
 * @param maxStringSize 
 * @return 
 */
bool charPointerToArray(const char * const inputString,
    char outputString[], uint32_t maxStringSize);

/**
 * @brief pass a string pointer, reverse it and put it back to outputString array
 *
 * @detail note that, array comes as refrence to this function.
 *          threre's no allocation on heap. we just modify the array and caller recive the change.
 *          and when caller goes out of scope, the array will delete automatically.
 *
 * @param inputString 
 * @param outputString 
 * @param maxStringSize 
 * @return 
 */
bool reverseString(const char * const inputString,
    char outputString[], uint32_t maxStringSize);

/**
 * @brief detect the extension of a file
 *
 * @param fileName 
 * @param extName 
 * @return 
 */
bool getExtensionOfFile(const char * const fileName,
   char extName[], uint32_t extNameSize);

/**
 * @brief remove sub-directories from a path
 *
 * @example subDirsToBeRemove = 2 -> "/mnt/D/workspace/project/zaal/build/tests" --> "/mnt/D/workspace/project/zaal"
 * @param path 
 * @param subDirsToBeRemove
 * @return true if opeation is successful, otherwise false
 */
bool removeSubDirectoryFromPath(char * path,
    uint32_t numbersOfSubDirsToRemove);

/**
 * @brief copy content of memory from dest to src
 *
 * @param dest 
 * @param destSize 
 * @param src 
 * @param srcSize 
 * @return 
 */
int zaalMemCopy(void* dest, size_t destSize,
  void* src, size_t srcSize);

/**
 * @brief return the string equivalent of error type
 *
 * @param type 
 * @return 
 */
char* getErrorType(int type);

#endif // ZAAL_FILE_UTIL_H
