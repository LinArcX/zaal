#include <errno.h>
#include <stdbool.h>

#include "scanner.h"
//#include "parser.h"
//#include "generator.h"

int main(int argc, const char* argv[])
{
  int result = -1;

  if (2 != argc) {
    fprintf(stderr, "Usage: %s <sourceFile>\n", argv[0]);
  }
  else {
    const FILE* pSourceFile = fopen(argv[1], "r");
    if (NULL == pSourceFile) {
      fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
      pSourceFile = NULL;
    }
    else {
      Token token = {0};
      uint32_t line = 1;

      char Text[ETextLength] = {0};

      // sometimes we need to "put back" a character if we have already read too far ahead in the input stream. 0 in ASCII mean NULL
      uint32_t putBackChar = 0;  

      if(true == scan(pSourceFile, &token, &line, &putBackChar, &Text)) {
        FILE* pOutFile = fopen("out.s", "w");
        if (NULL == pOutFile) {
          fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
          pOutFile = NULL;
        }
        else {
          //genpreamble();                
          //statements();
          //genpostamble();               
          //struct ASTnode *node = {0};
          //node = parseExpressions(0);		
          //if(NULL != node)
          //{
          //  printf("%d\n", interpretAST(node));
          //  generateCode(node);
          //  fclose(pOutFile);
          //  return 0;
          //}

          if (fclose(pOutFile) != 0) {
            perror("fclose");
          }
          pOutFile = NULL;
          result = 0;
        }
      }
      if (fclose(pSourceFile) != 0) {
        perror("ERROR! fclose: pSourceFile");
      }
      pSourceFile = NULL;
    }
  }
  return result;
}
