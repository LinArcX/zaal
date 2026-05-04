#include <stdlib.h>

#include "scanner.h"
#include "parser.h"
#include "kutil.h"
#include "generator.h"

static const char * ASTOperators[] = { "+", "-", "*", "/" };
//                                 EOF  +   -    *   /  INTLIT
static int g_operatorsPrecedence[] = {0, 10,  10,  20, 20, 0 };

struct ASTnode* 
buildASTNode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue) 
{
  struct ASTnode *n = {0};

  n = (struct ASTnode *) malloc(sizeof(struct ASTnode));
  if (NULL == n) 
  {
    fprintf(stderr, "[%s, %s, %s(), %d] Unable to malloc ASTNode!\n", errorType(ERROR_PARSER), __FILE__, __func__, __LINE__);
    return NULL;
  }

  n->op = op;
  n->left = left;
  n->right = right;
  n->intvalue = intvalue;
  return (n);
}

struct ASTnode* 
buildASTLeaf(int op, int intvalue) 
{
  return (buildASTNode(op, NULL, NULL, intvalue));
}

struct ASTnode*
buildASTUnary(int op, struct ASTnode *left, int intvalue) 
{
  return (buildASTNode(op, left, NULL, intvalue));
}

int 
scannerTypeToParserType(int token) 
{
  if(TOKEN_PLUS == token)
  {
    return A_ADD;
  }
  else if(TOKEN_MINUS == token)
  {
    return A_SUBTRACT;
  }
  else if(TOKEN_STAR == token)
  {
    return A_MULTIPLY;
  }
  else if(TOKEN_SLASH == token)
  {
    return A_DIVIDE;
  }
  else if(TOKEN_INTEGER == token)
  {
    return A_INTLIT;
  }
  else
  {
    fprintf(stderr, "[%s, %s, %s(), %d] Unknown token: %d on line %d\n", errorType(ERROR_PARSER), __FILE__, __func__, __LINE__, token, line);
    return -2;
  }
}

// Parse a primary factor and return an AST node representing it.
static struct ASTnode*
primary(void) 
{
  // For an INTLIT token, make a leaf AST node for it and scan in the next token. Otherwise, a syntax error for any other token type.
  if(TOKEN_INTEGER == gToken.type)
  {
    struct ASTnode * n = buildASTLeaf(A_INTLIT, gToken.literal.integer);
    scan(&gToken);
    return n;
  }
  else
  {
    fprintf(stderr, "[%s, %s, %s(), %d] Syntax Error on line: %d\n", errorType(ERROR_PARSER), __FILE__, __func__, __LINE__, line);
  }
  return NULL;
}

static int 
operatorPrecedence(int tokenType) 
{
  int prec = g_operatorsPrecedence[tokenType];
  if (prec == 0) 
  {
    fprintf(stderr, "[%s, %s, %s(), %d] Syntax Error on line: %d, token: %d\n", errorType(ERROR_PARSER), __FILE__, __func__, __LINE__, line, tokenType);
  }
  return prec;
}

// Ensure that the current token is t, and fetch the next token. Otherwise throw an error 
void 
match(int t, char *what) 
{
  if (gToken.type == t)
  {
    scan(&gToken);
  }
  else
  {
    printf("%s expected on line %d\n", what, line);
    exit(1);
  }
}

void 
semi(void) 
{
  match(TOKEN_SEMICOLON, ";");
}

void 
ident(void)
{ 
  match(TOKEN_IDENTIFIER, "identifier"); 
}

// Parse the declaration of a variable
void 
var_declaration(void) 
{
  // Ensure we have an 'int' token followed by an identifier and a semicolon. Text now has the identifier's name. Add it as a known identifier
  match(TOKEN_INT, "int");
  ident();
  addGlob(Text);
  genglobsym(Text);
  semi();
}

void
print_statement(void)
{
  struct ASTnode *tree;
  int reg;

  // Match a 'print' as the first token
  match(TOKEN_PRINT, "print");

  // Parse the following expression and generate the assembly code
  tree = parseExpressions(0);
  reg = generateAST(tree);
  genprintint(reg);
  genfreeregs();

  // Match the following semicolon and stop if we are at EOF
  semi();
}

void 
assignment_statement(void) 
{
  struct ASTnode *left, *right, *tree;
  int id;

  // Ensure we have an identifier
  ident();

  // Check it's been defined then make a leaf node for it
  if ((id = findglob(Text)) == -1) {
    fatals("Undeclared variable", Text);
  }
  right = mkastleaf(A_LVIDENT, id);

  // Ensure we have an equals sign
  match(T_EQUALS, "=");

  // Parse the following expression
  left = binexpr(0);

  // Make an assignment AST tree
  tree = mkastnode(A_ASSIGN, left, right, 0);

  // Generate the assembly code for the assignment
  genAST(tree, -1);
  genfreeregs();

  // Match the following semicolon
  semi();
}

// Parse one or more statements
void 
statements(void) 
{
  struct ASTnode *tree;
  int reg;

  while (1) 
  {
    if(TOKEN_PRINT == gToken.type)
    {
      print_statement();
    }
    else if (TOKEN_INT == gToken.type)
    {
      var_declaration();
    }
    else if (TOKEN_IDENTIFIER == gToken.type)
    {
      assignment_statement();
    }
    else if (TOKEN_EOF == gToken.type)
    {
      return;
    }
    else
    {
      fatald("Syntax error, token", gToken.type);
    }
  }
}

// Return an AST tree whose root is a binary operator
struct ASTnode *
parseExpressions(int precedence) 
{
  int tokenType;
  struct ASTnode *left = {0};
  struct ASTnode *right = {0};

  // Get the integer literal on the left. Fetch the next token at the same time.
  left = primary();

  // If no tokens left, return just the left node
  tokenType = gToken.type;
  if (TOKEN_SEMICOLON == tokenType)
  {
    return left;
  }

  while(operatorPrecedence(tokenType) > precedence)
  {
    scan(&gToken);
    right = parseExpressions(g_operatorsPrecedence[tokenType]);
    left = buildASTNode(scannerTypeToParserType(tokenType), left, right, 0);
    tokenType = gToken.type;

    if (TOKEN_SEMICOLON == tokenType)
    {
      return left;
    }
  }
  return left;
}

int
interpretAST(struct ASTnode *n) 
{
  if(NULL != n)
  {
    int leftval, rightval;
    if (n->left)
    {
      leftval = interpretAST(n->left);
    }
    if (n->right)
    {
      rightval = interpretAST(n->right);
    }

    #ifdef PARSER_LOG
    if (n->op == A_INTLIT)
    {
      printf("int %d\n", n->intvalue);
    }
    else
    {
      printf("%d %s %d\n", leftval, ASTOperators[n->op], rightval);
    }
    #endif
    
    if(A_ADD == n->op)
    {
      return (leftval + rightval);
    }
    else if (A_SUBTRACT == n->op)
    {
      return (leftval - rightval);
    }
    else if (A_MULTIPLY == n->op)
    {
      return (leftval * rightval);
    }
    else if (A_DIVIDE == n->op)
    {
      return (leftval / rightval);
    }
    else if(A_INTLIT == n->op)
    {
      return (n->intvalue);
    }
    else
    {
      fprintf(stderr, "[%s, %s, %s(), %d] Unknown AST Operator: %d!\n", errorType(ERROR_PARSER), __FILE__, __func__, __LINE__, n->op);
    }
  }
  return 0;
}
