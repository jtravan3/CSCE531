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

int line_num = 0;
%}

digit           [0-9]
int             {digit}+
var             [a-zA-Z]
wspace		[ \t]
newline 	[\n]
other		[^{var}{int}{wspace}{newline}]

%%

{var}			handle_var();

{int}			handle_digit();

{wspace}		handle_wspace();

{newline}		handle_new_line();

{other}			handle_other();

%%

int handle_digit(){
    yylval.y_int = atol(yytext);
    printf("Handle Digit: '%ld'\n", yylval.y_int);
    return CONST;
}

int handle_var(){
    yylval.y_int = toupper(*yytext); 
    printf("Handle Variable: '%c'\n",(char)yylval.y_int);
    return VAR;
}

int handle_new_line(){
    line_num++;
    printf("Handle Newline on line '%d'\n", line_num);
    int i = *yytext;
    return i;
}

int handle_wspace(){
    /* EAT IT UP */
}

int handle_other(){
    printf("Handle Other: '%c'\n", *yytext);
    int i = *yytext;
    return i;
}
