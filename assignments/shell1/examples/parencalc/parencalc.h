/*
 * Simple lex/yacc example
 *
 */


/* This is the definition of the "assignment" structure */
struct exprtree {
    int operator;
    struct exprtree *left;
    struct exprtree *right;
    int number;  /* if left and right are NULL, then there's
		    a number here */
};


/* externals */
extern int yydebug;

/* routine decls */
void doline(struct exprtree *pexpr);
int yyparse(void);

