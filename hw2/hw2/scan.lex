/*  Homework 2                         */
/*  Assignment to build a .lex file to */
/*  process tokens	               */
/*  Author: jravan                     */
/*  Date:   02/21/2015                 */

%{
#include <math.h>
#include "defs.h"

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

main( int argc, char **argv ){

    ++argv, --argc;
    if( argc > 0 )
	yyin = fopen( argv[0], "r");
    else
	yyin = stdin;
    yylex();

}


handle_wspace() {

  /* EAT IT UP */

}

handle_digit(){

}

handle_var(){

}

handle_new_line(){

    line_num++;

}

handle_other(){

}
