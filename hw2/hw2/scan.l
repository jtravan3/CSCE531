/*  Homework 2                         */
/*  Assignment to build a .lex file to */
/*  process tokens	               */
/*  Author: jravan                     */
/*  Date:   02/21/2015                 */

%{
#include <math.h>
#include "defs.h"
#include "y.tab.h"

int line_num = 1;
%}

digit           [0-9]
int             [-+]*{digit}+
var             [a-z]
optwspace	[ \t]*
wspace		[ \t]+
newline 	[\n]
other		[^a-z0-9]

%%

{wspace}		handle_wspace();

{digit}			handle_digit();

{var}			handle_var();

{newline}		handle_new_line();

{other}			handle_other();

%%


handle_wspace() {
  /* EAT IT UP */
}

handle_digit(){
    yylval.y_int = atol(yytext);
    return CONST;
}

handle_var(){
    yylval.y_int = toupper(yytext); 
    return VAR;
}

handle_new_line(){
    line_num++;
}

handle_other(){
    return atoi(yytext);
}
