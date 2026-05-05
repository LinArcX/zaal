#include <errno.h>

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
    FILE* pSourceFile = fopen(argv[1], "r");
    if (NULL == pSourceFile) {
      fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
      pSourceFile = NULL;
    }
    else {
      if(true == scan(&gToken)) {
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
        perror("fclose");
      }
      pSourceFile = NULL;
    }
  }
  return result;
}
