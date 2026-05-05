#ifndef KAVEH_SCANNER_H
#define KAVEH_SCANNER_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Length of symbols in input
#define TEXTLEN     512             

extern uint32_t line;
extern uint32_t lastChar;
//extern FILE* pSourceFile;

// Last identifier scanned
extern char Text[TEXTLEN + 1];         

typedef enum
{
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

typedef struct
{
  char oprator[2]; // 2 because one for operator and another for \0
  int integer;
} TokenLiteral;

typedef struct
{
  TokenTypes type;
  TokenLiteral literal;
} Token;
extern Token gToken;

int scan(Token* token);

#endif
