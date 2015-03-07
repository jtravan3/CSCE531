#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "eval.h"

extern TN_Array exprs;
extern Array longVals;

int val_tab[26];

long eval_expr(TN expr) {
 
   if(expr == NULL) {
	return; 
   }

    if(expr->tag == INT_CONST) {
//	printf("Returning int constant: %ld\n",expr->u.int_const);
	return expr->u.int_const;
    }

    if(expr->tag == VAR_T) {
//	printf("Returning var: '%c' value: '%d'\n", expr->u.var, get_val(expr->u.var));
	return get_val(expr->u.var);
    }

    if(expr->tag == UN_OP) {
	if(expr->u.unop.op == U_ADD){
//	    printf("Evaluating unary operation of type: ADD\n");
	    return eval_expr(expr->u.unop.operand);
	} else if(expr->u.unop.op == U_HASHTAG) {
//          printf("Evaluating unary operation of type: HASHTAG\n");
	    long val = getArrayVal(&longVals, expr->u.unop.index);
	    if(val == 0) {
		 long eval = eval_expr(expr->u.unop.operand);
	   	 insertArrayAtIndex(&longVals, expr->u.unop.index, eval);
		 return eval;
	    } else {
		return val;
	    }
	} else {
//	    printf("Evaluating unary operation of type: SUB\n");
	    return -eval_expr(expr->u.unop.operand);
	}
    }

    if(expr->tag == BIN_OP){
	if(expr->u.binop.op == B_ADD) {
//	    printf("Evaluating binary operation of type: ADD\n");
	    return (eval_expr(expr->u.binop.l_operand) + eval_expr(expr->u.binop.r_operand));
	}

	if(expr->u.binop.op == B_SUB) {
//	    printf("Evaluating binary operation of type: SUB\n");
	    return (eval_expr(expr->u.binop.l_operand) - eval_expr(expr->u.binop.r_operand));
	}

	if(expr->u.binop.op == B_MUL) {
//	    printf("Evaluating binary operation of type: MUL\n");
	    return (eval_expr(expr->u.binop.l_operand) * eval_expr(expr->u.binop.r_operand));
	}

	if(expr->u.binop.op == B_DIV) {
//	    printf("Evaluating binary operation of type: DIV\n");
	    return (eval_expr(expr->u.binop.l_operand) / eval_expr(expr->u.binop.r_operand));
	}

	if(expr->u.binop.op == B_MOD) {
//	    printf("Evaluating binary operation of type: MOD\n");
	    return (eval_expr(expr->u.binop.l_operand) % eval_expr(expr->u.binop.r_operand));
	}
    }
}

int get_val(int v) {
//    printf("Get value called: v '%c'\n", (char)v);
    return val_tab[v - 'A'];
}

void set_val(int v, int val) {
//    printf("Set value called: v '%c' val: '%d'\n", (char)v, val);
    val_tab[v - 'A'] = val;
//    printf("Value Saved: %d\n", val_tab[v - 'A']);
}

boolean print_error_for_index(long index) {

  if(index >= longVals.size) {
    fprintf(stderr, "ArrayIndexOutOfBoundsException: index greater than size.\n");
    return TRUE;
  }

  if(index >= longVals.used) {
    fprintf(stderr, "ArrayIndexOutOfBoundsException: index greater than size.\n");
    return TRUE;
  }
 
  if(index < 0) {
    fprintf(stderr, "ArrayIndexOutOfBoundsException: index less than size.\n");
    return TRUE;
  }

  return FALSE;

}
