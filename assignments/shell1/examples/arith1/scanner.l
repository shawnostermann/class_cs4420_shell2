%{
/*
 * Simple example lex input file
 *
 * Shawn Ostermann -- Fri Sep 25, 1998
 *
 */

#include <string.h>
#include "parser.h"

/* Everything up to the funny characters on the next line */
/* goes directly into the lex.yy.c file */
%}

/* shorthand definitions for later */
DIGIT		[0123456789]
WHITESPACE	[ \t]


/* The rest of this after the '%%' is lex rules */
%%

{WHITESPACE}+	{ }  /* Just ignore white space */

"\n" 	        { return(EOLN); } 
"+" 	        { return(PLUS); }
"-" 	        { return(MINUS); }
"*" 	        { return(TIMES); }
"/" 	        { return(DIVIDE); }


{DIGIT}+	{
    /* a number is a sequence of digits */
    yylval.number = atoi(yytext);  /* convert the string to binary */
    return(NUMBER);
}

.		{
    /* if we haven't matched anything yet, then it's illegal */
    fprintf(stderr, "arith: Bad character '%c'\n", *yytext);
}

%%
