/* Simple Expression Evaluator */

/* parse.y
 *
 * Grammer rules for bison.
 * Includes the lexical analyzer routine yylex().
 */


%{
#include <ctype.h>
#include "defs.h"
#define YYDEBUG 1

int  get_val(int);
void set_val(int, int);
%}

%union {
    long y_int;
    TN   y_tree;
};

%type  <y_tree> expr term factor;
%type  <y_int> assign;
%token <y_int> CONST VAR;

%%

session
    : { print_welcome(); }
      eval
    ;

eval
    : eval line
    | /* empty */
    ;

line
    : assign '\n'		{ printf("%d", atol($1)); }
    ;

assign
    : VAR '=' expr		{ set_val($1, 0);  $$ = 0; /*evalutate here */}
    | expr			{ $$ = 0; /* evaluate here */ }
    ;

expr
    : expr '+' term		{ $$ = make_bin_op_node($1, $3, B_ADD); }
    | expr '-' term		{ $$ = make_bin_op_node($1, $3, B_SUB); }
    | '-' term			{ $$ = make_un_op_node($2, U_SUB); }
    | '+' term			{ $$ = $2; }
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
    | '#' CONST			{}
    | CONST			{ $$ = make_int_const_node($1); }
    | VAR			{ $$ = make_var_node($1); }
    ;

%%

yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

print_welcome() {
    printf("Welcome to the Simple Expression Evaluator.\n");
    printf("Enter one expression per line, end with ^D\n\n");
}

static int val_tab[26];

int get_val(int v) {
    return val_tab[v - 'A'];
}

void set_val(int v, int val) {
    val_tab[v - 'A'] = val;
}
