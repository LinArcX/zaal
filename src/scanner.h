#ifndef ZAAL_SCANNER_H
#define ZAAL_SCANNER_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum compTimeConst {
  ETextLength = 513
};

typedef enum {
  TOKEN_EOF = 0,
  TOKEN_PLUS,       // +
  TOKEN_MINUS,      // -
  TOKEN_STAR,       // *
  TOKEN_SLASH,      // /
  TOKEN_EQUALS,     // =
  TOKEN_SEMICOLON,  // ;
  TOKEN_COLON,      // :
  TOKEN_INTEGER,
  TOKEN_FLOAT,
  TOKEN_IDENTIFIER,

  // temp
  TOKEN_INT,
  TOKEN_PRINT
} TokenTypes;

typedef struct {
  char oprator[2]; // 2 because one for operator and another for \0
  int integer;
} TokenLiteral;

typedef struct {
  TokenTypes type;
  TokenLiteral literal;
} Token;
extern Token gToken;

int scan(const FILE* pFile,
  Token    * const token,
  uint32_t * const line,
  uint32_t * const putBackChar,
  char (*Text) [ETextLength]);

#endif // ZAAL_SCANNER_H
