#ifndef ZAAL_FILE_UTIL_H
#define ZAAL_FILE_UTIL_H

#include <stdbool.h>
#include <stdint.h>

bool removeSubDirectoryFromPath(char * path,
    uint32_t numbersOfSubDirsToRemove);

const char * const getProjectRootPath();

#endif // ZAAL_ASM_GENERATOR_H


