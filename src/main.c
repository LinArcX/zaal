#include <errno.h>
#include <stdbool.h>
#include <magic.h>
#include "scanner.h"
#include "util/zaalStrings.h"

//#include "parser.h"
//#include "generator.h"

int main(int argc, const char* argv[])
{
  int result = -1;

  if (2 != argc) {
    fprintf(stderr, "Usage: %s <sourceFile>.zl\n", argv[0]);
  }
  else {
    // detect the mime-type of file. just accept "text/x-c++" and "text/plain" for the moment.
    magic_t magic = magic_open(MAGIC_MIME_TYPE);
    if (NULL != magic) {
      if (0 == magic_load(magic, NULL)) {
        const char *mime = magic_file(magic, argv[1]);
        if (mime) {
          // zaal files detecting as "text/x-c++"!
          // TODO: search for a way to set mimetype of .zl files as "text/zaal"
          if(0 == strcmp(mime, "text/x-c++") || 0 == strcmp(mime, "text/plain")) {
            printf("%s mimetype is: %s\n", argv[1], mime);

            char ext[ZAAL_MAX_STRING_SIZE] = {0};
            if (getExtensionOfFile(argv[1], ext, ZAAL_MAX_FILE_EXTENSION_SIZE)) {
              if (0 == strcmp(ext, "zl")) {
                const FILE* pSourceFile = fopen(argv[1], "r");
                if (NULL == pSourceFile) {
                  fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
                  pSourceFile = NULL;
                }
                else {
                  Token token = {0};
                  uint32_t line = 1;

                  char Text[E_CONST_TEXT_LENGTH] = {0};

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
              else {
                fprintf(stderr, "Wrong extension. please provide a file with .zl extension.\n");
              }
            }
            else {
              fprintf(stderr, "%s has no extension. please provide a file with .zl extension.\n", argv[1]);
            }
          }
          else {
            fprintf(stderr, "Unsupported mimetype: %s\n", mime);
          }
        }
      }
      magic_close(magic);
    }
    else {
      fprintf(stderr, "Error: magic_open() reurned NULL!\n");
    }
  }
  return result;
}
