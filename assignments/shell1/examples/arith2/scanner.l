%{
/*
 * Simple example lex input file
 *
 * Shawn Ostermann -- Wed Feb  7, 1996
 *
 */

#include <string.h>
#include "parser.h"

/* Everything up to the funny characters on the next line */
/* goes directly into the lex.yy.c file */
%}

/* shorthand definitions for later */
DIGIT		[0123456789]
LETTER		[a-zA-Z]
WHITESPACE	[ \t]


/* The rest of this after the '%%' is lex rules */
%%

{WHITESPACE}+	{ }  /* Just ignore white space */

"\n" 	        { return(EOLN); } 
";" 	        { return(SEMI); }
"+" 	        { return(PLUS); }
"-" 	        { return(MINUS); }
"*" 	        { return(TIMES); }
"/" 	        { return(DIVIDE); }
"=" 	        { return(ASSIGN); }


{LETTER}({LETTER}|{DIGIT})*	{
    /* a variable is a letter followed by letters and/or numbers */
    yylval.string = strdup(yytext);  /* make a copy of the string */
    return(VARIABLE);
}


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
