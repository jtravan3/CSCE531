/*  Homework 2                         */
/*  Assignment to build a .lex file to */
/*  process tokens	               */
/*  Author: jravan                     */
/*  Date:   02/21/2015                 */
/*{newline}		handle_new_line();*/
/*{other}			handle_other();*/
/*{digit}			handle_all();  handle_digit(); */
/*{wspace}		handle_all();  handle_wspace(); */
/*{var}			handle_all();   handle_var(); */

%{
#include <math.h>
//#include <ctype.h>
#include "defs.h"
#include "eval.h"
#include "y.tab.h"

extern int yylex();
//int line_num = 0;
int c;
%}

digit           [0-9]
int             {digit}+
var             [a-zA-Z]
wspace		[ \t]
newline 	[\n]
other		[^{var}{int}{wspace}{newline}]

%%




.			handle_all();

%%

int handle_digit(){
    yylval.y_int = atol(yytext);
//    printf("Handle Digit: '%ld'\n", yylval.y_int);
    return CONST;
}

int handle_var(){
    char* tmp = (char *) malloc(strlen(yytext)+1);
    strcpy(tmp, yytext);
    yylval.y_int = toupper(*tmp); 
//    printf("Handle Variable: '%ld'\n",yylval.y_int);
    return VAR;
}

//int handle_new_line(){
//    line_num++;
//    printf("Handle Newline on line '%d'\n", line_num);
//    int i = *yytext;
//    return i;
//}

int handle_wspace(){
    /* EAT IT UP */
}

int handle_other(){
//    printf("Handle Other: '%c'\n", *yytext);
    char* tmp = (char *) malloc(strlen(yytext)+1);
    strcpy(tmp, yytext);
    return *tmp;
}

int handle_all() {
    int c;

    char* tmp = (char *) malloc(strlen(yytext)+1);
    strcpy(tmp, yytext);

    /* read past whitespace first */
//    while ((c = *tmp) == ' ' || c == '\t');
    if(c == ' ' || c == '\t') {
	/*blah */
    } 
    else if (isalpha(c))            /* if letter (variable name) */    
    {
        yylval.y_int = toupper(c);   /* case insensitive */
        return VAR;
    } 
    else if (isdigit(c))
    {
//        ungetc(c, stdin);
//        scanf("%ld", &yylval.y_int);
	yylval.y_int = c;
        return CONST;
    }
    else 
    {
    return c;
    }
}

