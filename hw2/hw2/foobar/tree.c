#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "eval.h"
#include "y.tab.h"

TN make_bin_op_node(TN l_operand, TN r_operand, BIN_OP_TYPE op) {
    TN n = (TN) malloc(sizeof(TREE_NODE));
    n->tag = BIN_OP;
    n->u.binop.op = op;
    n->u.binop.l_operand = l_operand;
    n->u.binop.r_operand = r_operand;

//    printf("TREE NODE CREATED\n");
//    printf("Tag: 'BIN_OP'\n");

    return n;
}

TN make_un_op_node(TN operand, UN_OP_TYPE op, long index) {
    TN n = (TN) malloc(sizeof(TREE_NODE));
    n->tag = UN_OP;
    n->u.unop.op = op;
    n->u.unop.operand = operand;
    n->u.unop.index = index;

//    printf("TREE NODE CREATED\n");
//    printf("Tag: 'UN_OP'\n");

    return n;
}

TN make_int_const_node(long i) {
    TN n = (TN) malloc(sizeof(TREE_NODE));
    n->tag = INT_CONST;
    n->u.int_const = i;

//    printf("TREE NODE CREATED\n");
//    printf("Tag:   'INT_CONST'\n");
//    printf("Value: '%ld'\n", i);

    return n;
}

TN make_var_node(char c) {
    TN n = (TN) malloc(sizeof(TREE_NODE));
    n->tag = VAR_T;
    n->u.var = c;

//    printf("TREE NODE CREATED\n");
//    printf("Tag: 'VAR_T'\n");
//    printf("Var: '%c'\n", c);

    return n;
}

