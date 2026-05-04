#include <errno.h>

#include "scanner.h"
//#include "parser.h"
//#include "generator.h"

FILE	*pOutFile;

int main(int argc, char *argv[])
{
  if (2 != argc) {
    fprintf(stderr, "Usage: %s <sourceFile>\n", argv[0]);
    return -1;
  }

  pSourceFile = fopen(argv[1], "r");
  if (NULL == pSourceFile) {
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    return -1;
  }

  if(true == scan(&gToken)) {
    pOutFile = fopen("out.s", "w");
    if (NULL == pOutFile) {
      fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
      return -1;
    }
    //genpreamble();                
    //statements();
    //genpostamble();               
    fclose(pOutFile);              
    return 0;

    //struct ASTnode *node = {0};
    //node = parseExpressions(0);		
    //if(NULL != node)
    //{
    //  printf("%d\n", interpretAST(node));
    //  generateCode(node);
    //  fclose(pOutFile);
    //  return 0;
    //}
  }
  return -1;
}
