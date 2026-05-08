#include "zaalMemMap.h"
#include "zaalStrings.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

bool mapFileToMemory(const char * const fileName,
    int* fd,
    struct stat* st)
{
  bool result = false;

  // 1. Open the file read-only
  *fd = open(fileName, O_RDONLY);
  if (*fd >= 0) {
    // 2. Get the file size
    if (fstat(*fd, st) >= 0) {
      if (NULL != st) {
        if (st->st_size > 0) {
          // 3. Memory map the file (read-only)
          char* mapped = (char*)mmap(NULL, st->st_size, 
                                     PROT_READ,          // Read only
                                     MAP_PRIVATE,        // Private mapping (copy-on-write)
                                     *fd, 0);
          if (MAP_FAILED != mapped) {
            result = true;
            //// 4. Use the mapped memory like a normal array/buffer
            //// Example: print first 100 bytes
            //for(size_t i = 0; i < 100 && i < (size_t)st->st_size; i++) {
            //    putchar(mapped[i]);
            //    result = true;
            //}
          }
          else {
            fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d | errno: %s] -> file is empty!\n",
              getErrorType(E_ZAAL_INFO), __FILE__, __func__, __LINE__, strerror(errno));
            close(*fd);
          }
        }
        else {
          fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d | errno: %s] -> file is empty!\n",
            getErrorType(E_ZAAL_INFO), __FILE__, __func__, __LINE__, strerror(errno));
          close(*fd);
        }
      }
      else {
        fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d | errno: %s] -> file is empty!\n",
          getErrorType(E_ZAAL_INFO), __FILE__, __func__, __LINE__, strerror(errno));
        close(*fd);
      }
    }
    else {
      fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d | errno: %s]\n",
        getErrorType(E_ZAAL_INFO), __FILE__, __func__, __LINE__, strerror(errno));
      close(*fd);
    }
  }
  else {
    fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d | errno: %s]\n",
        getErrorType(E_ZAAL_INFO), __FILE__, __func__, __LINE__, strerror(errno));
  }
  return result;
}

bool unmapFileFromMemory(char* mapped,
    struct stat* st,
    int* fd)
{
  bool result = false;
  if (NULL != mapped) {
    if (NULL != st) {
      munmap(mapped, st->st_size);
      if (NULL != fd) {
        close(*fd);
        result = true;
      }
      else {
        fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d | errno: %s]\n",
          getErrorType(E_ZAAL_INFO), __FILE__, __func__, __LINE__, strerror(errno));
      }
    }
    else {
      fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d | errno: %s]\n",
        getErrorType(E_ZAAL_INFO), __FILE__, __func__, __LINE__, strerror(errno));
    }
  }
  else {
    fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d | errno: %s]\n",
      getErrorType(E_ZAAL_INFO), __FILE__, __func__, __LINE__, strerror(errno));
  }
  return result;
}

bool getCharFromMemMap(char* mapped,
  struct stat* st,
  char* ch)
{
  bool result = false;

  if (NULL != mapped) {
    // Current position
    char* current = mapped;              

    if (NULL != st) {
      // End of mapped area
      char* end = mapped + st->st_size;
      if (current >= end) {
        *ch = EOF;
        result = true;
      }
      else {
        *ch = *current++;
        result = true;
      }
    }
    else {
      fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d | errno: %s]\n",
        getErrorType(E_ZAAL_INFO), __FILE__, __func__, __LINE__, strerror(errno));
    }
  }
  else {
    fprintf(stderr, "[*********** %s file: %s | func: %s() | line: %d | errno: %s]\n",
      getErrorType(E_ZAAL_INFO), __FILE__, __func__, __LINE__, strerror(errno));
  }

  return result;
}
