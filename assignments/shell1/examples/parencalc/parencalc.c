/*
 * Simple arithmetic program as a lex/yacc example
 *
 * Shawn Ostermann -- Wed Feb  7, 1996
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "parencalc.h"

/* globals */


/* local routines */
static int doexpr(struct exprtree *pass);
static void printexpr(struct exprtree *pass);



int
main(
     int argc,
     char *argv[])
{
    if ((argc == 2) && (strcmp(argv[1],"-d") == 0))
	yydebug = 1;  /* turn on ugly YACC debugging */
    else
	yydebug = 0;  /* turn off ugly YACC debugging */

    /* parse the input file */
    yyparse();

    exit(0);
}


static void
printexpr(struct exprtree *pexpr)
{
    if (pexpr->left == NULL) {
	printf("%d", pexpr->number);
	return;
    }

    printf("(");
    printexpr(pexpr->left);
    switch(pexpr->operator) {
      case PLUS:    printf("+"); break;
      case MINUS:   printf("-"); break;
      case TIMES:   printf("*"); break;
      case DIVIDE:  printf("/"); break;
    }
    printexpr(pexpr->right);
    printf(")");
}


static void
printexpr_rpn(struct exprtree *pexpr)
{
    if (pexpr->left == NULL) {
	printf(" %d ", pexpr->number);
	return;
    }

    printexpr_rpn(pexpr->left);
    printexpr_rpn(pexpr->right);
    switch(pexpr->operator) {
      case PLUS:    printf("+"); break;
      case MINUS:   printf("-"); break;
      case TIMES:   printf("*"); break;
      case DIVIDE:  printf("/"); break;
    }
}


static int
doexpr(struct exprtree *pexpr)
{
    if (pexpr->left == NULL)
	return(pexpr->number);

    switch(pexpr->operator) {
      case PLUS:    return(doexpr(pexpr->left)+doexpr(pexpr->right));
      case MINUS:   return(doexpr(pexpr->left)-doexpr(pexpr->right));
      case TIMES:   return(doexpr(pexpr->left)*doexpr(pexpr->right));
      case DIVIDE:  return(doexpr(pexpr->left)/doexpr(pexpr->right));
      default:  printf("? "); exit(1);
    }
}


void
doline(struct exprtree *pexpr)
{
    printf("Read a line:\n");

    printf("  The question is:  ");
    printexpr(pexpr);
    printf("\n");

    printf("  In RPN form:     ");
    printexpr_rpn(pexpr);
    printf("\n");

    printf("  The answer is %d\n", doexpr(pexpr));
}
