#include "scanner.h"
#include "zutil.h"

uint32_t line = 1;
uint32_t lastChar = 0;
Token gToken = {0};
FILE* pSourceFile = NULL;
char Text[TEXTLEN + 1] = {0};

static int getNextChar(void)
{
  uint32_t ch = 0;

  if (0 != lastChar) {
    // if we already put back a character, just return it.
    ch = lastChar;	
    lastChar = 0;
  }
  else {
    // read next char from pSourceFile stream
    ch = fgetc(pSourceFile);
    if ('\n' == ch) {
      line++;
    }
  }
  return ch;
}

static int skipWhiteSpaces(void)
{
  int ch = getNextChar();
  // \f: form-feed character (ASCII 12, U+000C). It's a control character originally used to advance printers to the start of the next page. 
  // \r: carriage return control character (ASCII 13, U+000D).
  //    It moves the cursor to the start of the current line without advancing to the next line.
  while (' ' == ch || '\t' == ch || '\n' == ch || '\r' == ch || '\f' == ch) {
    ch = getNextChar();
  }
  return (ch);
}

static int charPositionInString(const char* str, int ch)
{
  const char* position = strchr(str, ch);
  if(NULL != position)
  {
    return position - str;
  }
  return -1;
}

static int scanInteger(int ch)
{
  int k;
  int val = 0;

  // Convert each character into an int value
  while ((k = charPositionInString("0123456789", ch)) >= 0) {
    val = val * 10 + k;
    ch = getNextChar();
  }

  // We hit a non-integer character, put it back.
  lastChar = ch;
  return val;
}

static int scanIdentifier(int c, char *buf, int lim)
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
    c = getNextChar();
  }
  // We hit a non-valid character, put it back. NUL-terminate the buf[] and return the length
  lastChar = c;
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

int scan(Token* token)
{
  bool result = false;
  if (NULL == token) {
    fprintf(stderr, "[%s, %s, %s(), %d] token is NULL!\n", errorType(ERROR_SCANNER), __FILE__, __func__, __LINE__);
  }
  else {
    memset(token, 0, sizeof(Token));
    int ch = skipWhiteSpaces();

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
        token->literal.integer = scanInteger(ch);
      }
      else if (isalpha(ch) || '_' == ch) {
        // Read in a keyword or identifier
        scanIdentifier(ch, Text, TEXTLEN);

        int tokenType = keyword(Text);
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
        fprintf(stderr, "[%s, %s, %s(), %d] Unrecognised character %c on line %d\n", errorType(ERROR_SCANNER), __FILE__, __func__, __LINE__, ch, line);
      }
    }
    result = true;
  }
  return result;
}
