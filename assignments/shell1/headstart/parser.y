%{
#include <stdio.h>
#include <stdarg.h>
#include "bash.h"

/* some internal files generated by bison */
int yylex();
void yyerror(const char *s,...);
void yywarn(const char *s,...);

struct args {
    char *arg;
    struct args *next;
};


/* include debugging code, in case we want it */
#define YYDEBUG 1

int lines = 1;
static int synerrors = 0;


%}


%union	{ /* the types that we use in the tokens */
    char *string;
    struct command *pcmd;
    struct args *pargs;
    int number;
}



%token EOLN PIPE INPUT
%token <number> OUTPUT OUTPUT_APPEND
%token <string> WORD

%type <pcmd> line 
  

%% 	/* beginning of the parsing rules	*/
input	: lines
	|
  	;

lines	: oneline
	| oneline lines
	;

oneline : line
		{ doline($1); }
	  eoln
 	| eoln	/* blank line, do nothing */
	| error eoln
	/* if we got an error on the line, don't call the C program */
	;

eoln	: EOLN
		{ ++lines; }
	;

/* you need to finish the rest of this... */
line	: WORD line
		{ $$ = NULL; }
  	| WORD
		{ $$ = NULL; }	
  	;
%%

void
yyerror(const char *error_string, ...)
{
    va_list ap;
    int line_nmb(void);

    FILE *f = stdout;

    va_start(ap,error_string);

    ++synerrors;

    fprintf(f,"Error on line %d: ", lines);
    vfprintf(f,error_string,ap);
    fprintf(f,"\n");
    va_end(ap);
}
