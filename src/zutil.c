#include "zutil.h"

#include <stdio.h>
#include <string.h>

int zmemcpy(void* dest, const void* src)
{
  size_t srcSize = sizeof(src);
  size_t destSize = sizeof(dest);

  if(destSize < srcSize) {
    fprintf(stderr, "[%s, %s, %s, %d] *dest > *src\n", errorType(ERROR), __FILE__, __func__, __LINE__);
    return 0;
  }
  else {
    if (dest < src && dest + srcSize > src) {
      memmove(dest, src, srcSize);
    }
    else if (src < dest && src + srcSize > dest) {
      memmove(dest, src, srcSize);
    }
    else {
      memcpy(dest, src, srcSize);
    }
    return 1;
  }
}

char* errorType(int error_type)
{
  if(INFO == error_type) {
    return (char*)"INFO";
  }
  else if(WARNING == error_type) {
    return (char*)"WARNING";
  }
  else if(ERROR == error_type) {
    return (char*)"ERROR";
  }
  else if(FATAL == error_type) {
    return (char*)"FATAL";
  }
  else {
    return (char*)"UKNOWN";
  }
}
