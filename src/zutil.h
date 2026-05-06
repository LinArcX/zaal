#ifndef ZAAL_UTIL_H
#define ZAAL_UTIL_H

#include <stdio.h>

enum Z_ERROR {
  INFO,
  WARNING,
  ERROR,
  FATAL
};

extern FILE	*pOutFile;

int zmemcpy(void *dest, const void *src);
char* errorType(int error_type);

#endif
