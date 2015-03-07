/* Simple Expression Evaluator */

/* main.c */

#include <stdlib.h>
#include <stdio.h>
#include "defs.h"

int yyparse();
TN_Array exprs;
Array longVals;

int main()
{
    initTNArray(&exprs, 50);
    initArray(&longVals, 50);
    extern int yydebug;
    yydebug = 0;         /* change to 1 to see debugging info */
    yyparse();
    return 0;
}
