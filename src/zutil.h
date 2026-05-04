#ifndef ZAAL_UTIL_H
#define ZAAL_UTIL_H

#include <stdio.h>

enum Z_ERROR {
  ERROR_PARSER,
  ERROR_SCANNER,
  ERROR_GENERATOR,
  ERROR_ZAAL,
  WARNING
};

extern FILE	*pOutFile;

int zmemcpy(void *dest, const void *src);
char* errorType(int error_type);

#endif
