#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>

// Change this to 1 for debugging output (hitting newline to continue)
#define DEBUG 0

#define debug(s)      if (DEBUG) fprintf(stderr,s),getchar()
#define debug1(s,t)   if (DEBUG) fprintf(stderr,s,t),getchar()
#define debug2(s,t,u) if (DEBUG) fprintf(stderr,s,t,u),getchar()

typedef int boolean;
#define FALSE 0
#define TRUE 1

typedef enum {
    UN_OP, BIN_OP, INT_CONST, VAR_T
} TAG_TYPE;

typedef enum {
   U_ADD, U_SUB
} UN_OP_TYPE;

typedef enum {
   B_ADD, B_SUB, B_MUL, B_DIV, B_MOD
} BIN_OP_TYPE;

typedef struct tn {
    TAG_TYPE tag;
    union {
	struct {
	    UN_OP_TYPE op;
	    struct tn *operand;
	} unop;
	struct {
	    BIN_OP_TYPE op;
	    struct tn *l_operand;
	    struct tn *r_operand;
	} binop;
	long int_const;
	char var;
    } u;
} TREE_NODE, *TN;

TN make_bin_op_node(TN l_operand, TN r_operand, BIN_OP_TYPE op);
TN make_un_op_node(TN operand, UN_OP_TYPE op);
TN make_int_const_node(long i);
TN make_var_node(char c);

#endif
