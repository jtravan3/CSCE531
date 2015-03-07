/* Simple Expression Evaluator */

/* parse.y
 *
 * Grammer rules for bison.
 * Includes the lexical analyzer routine yylex().
 */


%{
#include <ctype.h>
#include "defs.h"
#include "eval.h"
#include "y.tab.h"
#define YYDEBUG 1

extern TN_Array exprs;
extern Array longVals;
extern int yylex();

int line_num = 1;
%}

%union {
    long y_int;
    TN   y_tree;
};

%type  <y_tree> expr 
%type  <y_tree> term
%type  <y_tree> factor
%type  <y_int>  assign
%type  <y_int>  line
%token <y_int>  CONST
%token <y_int>  VAR

%%

session
    : { print_welcome(); }
     eval			{ printf("\n"); }
    ;

eval
    : eval line			{ print_line_num(line_num); }	
    | /* empty */
    ;

line
    : assign '\n'		{ line_num++;  printf("%ld\n", $1); }
    ;

assign
    : VAR '=' expr		{ long eval = eval_expr($3); $$ = eval; set_val($1, eval); insertArray(&longVals, eval);  resetArray(&longVals);  insertTNArray(&exprs, $3); }
    | expr			{ long eval = eval_expr($1); $$ = eval; insertArray(&longVals, eval);  insertTNArray(&exprs, $1); }
    ;

expr
    : expr '+' term		{ $$ = make_bin_op_node($1, $3, B_ADD); }
    | expr '-' term		{ $$ = make_bin_op_node($1, $3, B_SUB); }
    | '+' term			{ $$ = make_un_op_node($2, U_ADD, 0); }
    | '-' term			{ $$ = make_un_op_node($2, U_SUB, 0); }
    | term
    ;

term
    : term '*' factor		{ $$ = make_bin_op_node($1, $3, B_MUL); }
    | term '/' factor		{ $$ = make_bin_op_node($1, $3, B_DIV); }
    | term '%' factor		{ $$ = make_bin_op_node($1, $3, B_MOD); }
    | factor
    ;

factor
    : '(' expr ')'		{ $$ = $2; }
    | '#' CONST			{ int index = $2-1; if(print_error_for_index(index)){ return; }$$ = make_un_op_node(getTNArrayVal(&exprs, index), U_HASHTAG, index); }
    | CONST			{ $$ = make_int_const_node($1); }
    | '#' VAR			{ fprintf(stderr, "Syntax error\n");}
    | VAR			{ $$ = make_var_node($1); }
    ;

%%

int yylex() {
    int c;

    /* read past whitespace first */
    while ((c = getchar()) == ' ' || c == '\t');

    if (isalpha(c))            /* if letter (variable name) */
    {
        yylval.y_int = toupper(c);   /* case insensitive */
        return VAR;
    }
    if (isdigit(c))
    {
        ungetc(c, stdin);
        scanf("%ld", &yylval.y_int);
        return CONST;
    }
    return c;

}

yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

print_welcome() {
    printf("Welcome to the Simple Expression Evaluator.\n");
    printf("Enter one expression per line, end with ^D\n\n");
    print_line_num(line_num);
}

print_line_num(int line) {

    if(line <= 9) {
	 printf("   %d: ", line_num);
    } else if (line > 9 && line <= 99) {
	 printf("  %d: ", line_num);
    } else if(line > 99 && line <= 999) {
	 printf(" %d: ", line_num);
    } else if(line > 999 && line <= 9999) {
	printf(" %d: ", line_num); 
    } else {
	printf("%d: ", line_num); 
    }

}
