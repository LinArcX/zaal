#ifndef ZAAL_SCANNER_H
#define ZAAL_SCANNER_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum compTimeConst {
  // max 2 for operator + 1 for end of string ('\0')
  E_CONST_OP_SIZE = 3,
  E_CONST_TEXT_LENGTH = 513,
};

typedef enum {
  E_TOKEN_EOF = -1,             // EOF
  E_TOKEN_PLUS = 0,             // +
  E_TOKEN_MINUS,                // -
  E_TOKEN_STAR,                 // *
  E_TOKEN_SLASH,                // /
  E_TOKEN_EQUALS,               // =
  E_TOKEN_SEMICOLON,            // ;
  E_TOKEN_ASSIGN,               // :
  E_TOKEN_LT,                   // <
  E_TOKEN_LTE,                  // <=
  E_TOKEN_GT,                   // >
  E_TOKEN_GTH,                  // >=
  E_TOKEN_DOT,                  // .
  E_TOKEN_DISCARD,              // _
  E_TOKEN_NOT,                  // !
  E_TOKEN_OPEN_PAR,             // (
  E_TOKEN_CLOSE_PAR,            // )
  E_TOKEN_OPEN_CUR_BRACKET,     // {
  E_TOKEN_CLOSE_CUR_BRACKET,    // }
  E_TOKEN_OPEN_SQR_BRACKET,     // [
  E_TOKEN_CLOSE_SQR_BRACKET,    // ]
  E_TOKEN_OPEN_ANGLE_BRACKET,   // <
  E_TOKEN_CLOSE_ANGLE_BRACKET,  // >

  E_TOKEN_INTEGER,              // ex: 1, 231, -21
  E_TOKEN_FLOAT,                // ex: 1.2, 1231.001, -23.90800
  E_TOKEN_IDENTIFIER,           // ex: myData, variable,

  // temp
  E_TOKEN_INT,
  E_TOKEN_PRINT
} TokenTypes;

typedef struct {
  char oprator[E_CONST_OP_SIZE]; 
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
  char (*Text) [E_CONST_TEXT_LENGTH]);

#endif // ZAAL_SCANNER_H
