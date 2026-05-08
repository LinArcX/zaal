#ifndef ZAAL_MEM_MAP_H
#define ZAAL_MEM_MAP_H

#include <stdbool.h>
#include <sys/stat.h>

/**
 * @brief map a file content as read-only to memory area
 *
 * @param fileName 
 * @param fd 
 * @param st 
 * @return 
 */
bool mapFileToMemory(const char * const fileName,
    int* fd,
    struct stat* st,
    char* mapped);

/**
 * @brief unmap memory area
 *
 * @param mapped 
 * @param st 
 * @param fd 
 * @return 
 */
bool unmapFileFromMemory(char* mapped,
    int* fd,
    struct stat* st);
 
/**
 * @brief get next character from memory-mapped space
 *
 * @param mapped 
 * @param st 
 * @param ch 
 * @return 
 */
bool getNextCharFromMemMap(char* mapped,
  struct stat* st,
  char* ch);

#endif // ZAAL_MEM_MAP_H
