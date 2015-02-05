/*  Homework 1                         */
/*  Assignment to build a .lex file to */
/*  process #define directives         */
/*  Author: jravan                     */
/*  Date:   02/02/2015                 */

%{
#include <math.h>
#include "my_defs.h"

int lineNumber = 1; 
boolean isInt = FALSE;
boolean isId = FALSE;
boolean isStrConst = FALSE;
boolean isKeyExpected = FALSE;
boolean isValExpected = FALSE;
%}

digit           [0-9]
int             [-+]*{digit}+
id              [A-Za-z][A-Za-z0-9]*
strconst	["][^\n]*["]
optwspace	[ \t]*
wspace		[ \t]+
define		{optwspace}"#define"{wspace}
newline 	[\n]

%%

{define}	 isKeyExpected = TRUE;	

{id}             isId = TRUE; processDefine();

{int}		 isInt = TRUE; processDefine();

{strconst}	 isStrConst = TRUE; processDefine();

{newline}	 lineNumber++;

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

processDefine() {

   if(isKeyExpected){
      if(isId){
	 printf("Key: '%s'\n", yytext);
	 isKeyExpected = FALSE;
	 isValExpected = TRUE;
	 isId = FALSE;
      } else {
	 fprintf(stderr, "Invalid ID received at l. %d\n", lineNumber);
	 isKeyExpected = FALSE;
	 isValExpected = TRUE;
      }
   } else {
      if(isValExpected){
         if(isId){
	    printf("Value: '%s' of type ID\n", yytext);
	    isId = FALSE;
         }

         if(isInt){
	    printf("Value: '%s' of type INT\n", yytext);
	    isInt = FALSE;
	 }

	 if(isStrConst){
	    printf("Value: '%s' of type STR_CONST\n", yytext);
	    isStrConst = FALSE;
	 }
	 
	 isValExpected = FALSE;
      } 
   }
}
