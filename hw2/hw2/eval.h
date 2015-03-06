#ifndef EVAL_H
#define EVAL_H

#include <stdio.h>

long eval_expr(TN expr);
int get_val(int v);
void set_val(int v, int val);
TN getTNArrayVal(TN_Array *a, int index);

#endif
