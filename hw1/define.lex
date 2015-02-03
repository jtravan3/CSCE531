/*  Homework 1                         */
/*  Assignment to build a .lex file to */
/*  process #define directives         */
/*  Author: jravan                     */
/*  Date:   02/02/2015                 */

%{
#include <math.h>
#include "my_defs.h"

boolean isKeyExpected = FALSE; 
boolean isValueExpected = FALSE;
%}

digit           [0-9]
int             {digit}+
id              [A-Za-z][A-Za-z0-9]*
optwspace	[ \t]*
wspace		[ \t]+
define		{optwspace}"#define"{wspace}

%%

{define}	 isKeyExpected = TRUE;	

{id}             handleNewDefine();

{int}		 handleNewDefine();

{wspace}   	 /* eat it up */

%%

main( int argc, char **argv ){

    ++argv, --argc;     /* skip over program name */
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;

    yylex();

}

void handleNewDefine() {

   if(isKeyExpected){
      printf("Key: %s\n", yytext);
      isKeyExpected = FALSE;
      isValueExpected = TRUE;
   } else {
      if(isValueExpected){
	 printf("Value: %s\n", yytext);
	 isValueExpected = FALSE;
      }
   }

}
