/*  Homework 1                         */
/*  Assignment to build a .lex file to */
/*  process #define directives         */
/*  Author: jravan                     */
/*  Date:   02/02/2015                 */

%{
#include <math.h>
#include "defs.h"

int line_num = 1;
boolean isInt = FALSE;
boolean isId = FALSE;
boolean isStrConst = FALSE;
boolean isKeyExpected = FALSE;
boolean isValExpected = FALSE;
%}

digit           [0-9]
int             [-+]*{digit}+
id              [_A-Za-z][_A-Za-z0-9]*
strconst	["][^\n]*["]
optwspace	[ \t]*
wspace		[ \t]+
define		{optwspace}"#define"{wspace}
newline 	[\n]

%%

{define}	 isKeyExpected = TRUE;	

{id}             isId = TRUE; processDefine(yytext);

{int}		 isInt = TRUE; processDefine(yytext);

{strconst}	 isStrConst = TRUE; processDefine(yytext);

{newline}	 line_num++;

{wspace}   	 /* eat it up */

%%

/* Empty utils section */
