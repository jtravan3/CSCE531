/*  Homework 2                         */
/*  Assignment to build a .lex file to */
/*  process tokens	               */
/*  Author: jravan                     */
/*  Date:   02/21/2015                 */

%{
#include <math.h>
#include <ctype.h>
#include "defs.h"
#include "eval.h"
#include "y.tab.h"

int line_num = 1;
%}

digit           [0-9]
int             {digit}+
var             [a-zA-Z]
optwspace	[ \t]*
wspace		[ \t]+
newline 	[\n]
other		[^a-zA-Z0-9]*

%%

{wspace}		handle_wspace();

{int}			handle_digit();

{var}			handle_var();

{other}			handle_other();

%%


handle_wspace() {
  /* EAT IT UP */
}

handle_digit(){
    yylval.y_int = atol(yytext);
    printf("Handle Digit: '%ld'\n", yylval.y_int);
    return CONST;
}

handle_var(){
    yylval.y_int = toupper(*yytext); 
    printf("Handle Variable: '%c'\n", (char)yylval.y_int);
    return VAR;
}

handle_new_line(){
    line_num++;
    return *yytext;
}

handle_other(){
    printf("Handle Other: '%s'\n", yytext);
    return *yytext;
}
