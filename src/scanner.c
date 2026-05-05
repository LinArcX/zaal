#include <stdbool.h>

#include "scanner.h"
#include "zutil.h"

static int getNextChar(const FILE* pFile,
  uint32_t * const line,
  uint32_t * const putBackChar)
{
  int ch = 0;

  if (0 != *putBackChar) {
    // if we already put back a character, just return it.
    ch = *putBackChar;	
    *putBackChar = 0;
  }
  else {
    // read next char from pFile stream
    ch = fgetc(pFile);
    if ('\n' == ch) {
      *line += 1;
    }
  }
  return ch;
}

static int skipWhiteSpaces(const FILE* pFile,
  uint32_t * const line,
  uint32_t * const putBackChar)
{
  int ch = getNextChar(pFile, line, putBackChar);
  // \f: form-feed character (ASCII 12, U+000C). It's a control character originally used to advance printers to the start of the next page. 
  // \r: carriage return control character (ASCII 13, U+000D).
  //    It moves the cursor to the start of the current line without advancing to the next line.
  while (' ' == ch || '\t' == ch || '\n' == ch || '\r' == ch || '\f' == ch) {
    ch = getNextChar(pFile, line, putBackChar);
  }
  return ch;
}

static int charPositionInString(const char* str, int ch)
{
  int result = -1;

  const char* position = strchr(str, ch);
  if(NULL != position)
  {
    result = position - str;
  }
  
  return result;
}

static int scanInteger(const FILE* pFile,
  int ch,
  uint32_t * const line,
  uint32_t * const putBackChar)
{
  int position;
  int intValue = 0;

  // Convert each character into an int value
  while ((position = charPositionInString("0123456789", ch)) >= 0) {
    intValue = intValue * 10 + position;
    ch = getNextChar(pFile, line, putBackChar);
  }

  // We hit a non-integer character, put it back.
  *putBackChar = ch;
  return intValue;
}

static int scanIdentifier(const FILE* pFile,
  int c,
  char* buf,
  int lim,
  uint32_t * const line,
  uint32_t * const putBackChar)
{
  int i = 0;

  while (isalpha(c) || isdigit(c) || '_' == c) {
    // Error if we hit the identifier length limit, else append to buf[] and get next character
    if (lim - 1 == i) {
      fprintf(stderr, "[%s, %s, %s(), %d] identifier too long on line %d\n", errorType(ERROR_SCANNER), __FILE__, __func__, __LINE__, line);
      //return 0;
    } 
    else if (i < lim - 1) {
      buf[i++] = c;
    }
    c = getNextChar(pFile, line, putBackChar);
  }

  // We hit a non-valid character, put it back. NUL-terminate the buf[] and return the length
  *putBackChar = c;
  buf[i] = '\0';
  return (i);
}

// Given a word from the input, return the matching keyword token number or 0 if it's not a keyword.
// Switch on the first letter so that we don't have to waste time strcmp()ing against all the keywords.
static int keyword(char *s) 
{
  switch (*s) 
  {
  case 'p':
    if (!strcmp(s, "print"))
    {
      return (TOKEN_PRINT);
    }
    break;
  case 'i':
    if (!strcmp(s, "int"))
    {
      return (TOKEN_INT);
    }
    break;
  }
  return (0);
}

int scan(const FILE* pFile,
  Token    * const token,
  uint32_t * const line,
  uint32_t * const putBackChar,
  char (*Text) [ETextLength])
{
  bool result = false;
  if (NULL == token) {
    fprintf(stderr, "[%s, %s, %s(), %d] token is NULL!\n", errorType(ERROR_SCANNER), __FILE__, __func__, __LINE__);
  }
  else {
    memset(token, 0, sizeof(Token));
    int ch = skipWhiteSpaces(pFile, line, putBackChar);

    if(EOF == ch) {
      token->type = TOKEN_EOF;
      return result;
    }
    else if('+' == ch) {
      token->type = TOKEN_PLUS;
      if(!zmemcpy(token->literal.oprator, "+")) {
        fprintf(stderr, "[%s, %s, %s(), %d]\n", errorType(ERROR_ZAAL), __FILE__, __func__, __LINE__);
        return result;
      }
    }
    else if('-' == ch) {
      token->type = TOKEN_MINUS;
      if(!zmemcpy(token->literal.oprator, "-")) {
        fprintf(stderr, "[%s, %s, %s(), %d]\n", errorType(ERROR_ZAAL), __FILE__, __func__, __LINE__);
        return result;
      }
    }
    else if('*' == ch) {
      token->type = TOKEN_STAR;
      if(!zmemcpy(token->literal.oprator, "*")) {
        fprintf(stderr, "[%s, %s, %s(), %d]\n", errorType(ERROR_ZAAL), __FILE__, __func__, __LINE__);
        return result;
      } 
    }
    else if('/' == ch) {
      token->type = TOKEN_SLASH;
      if(!zmemcpy(token->literal.oprator, "/")) {
        fprintf(stderr, "[%s, %s, %s(), %d]\n", errorType(ERROR_ZAAL), __FILE__, __func__, __LINE__);
        return result;
      }
    }
    else if(';' == ch) {
      token->type = TOKEN_SEMICOLON;
    }
    else if('=' == ch) {
      token->type = TOKEN_EQUALS;
    }
    else {
      if (isdigit(ch)) {
        token->type = TOKEN_INTEGER;
        token->literal.integer = scanInteger(pFile, ch, line, putBackChar);
      }
      else if (isalpha(ch) || '_' == ch) {
        // Read in a keyword or identifier
        scanIdentifier(pFile, ch, *Text, ETextLength, line, putBackChar);

        int tokenType = keyword(*Text);
        if (tokenType) {
          token->type = tokenType;
        }
        else {
          token->type = TOKEN_IDENTIFIER;
        }
        //fprintf(stderr, "[%s, %s, %s(), %d] Unrecognised symbol %S on line %d\n", errorType(ERROR_SCANNER), __FILE__, __func__, __LINE__, Text, line);
        //exit(1);
      }
      else {
        fprintf(stderr, "[%s, %s, %s(), %d] Unrecognised character %c on line %d\n",
          errorType(ERROR_SCANNER), __FILE__, __func__, __LINE__, ch, line);
      }
    }
    result = true;
  }
  return result;
}
