#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "eval.h"

void initTNArray(TN_Array *a, size_t initialSize) {
  a->array = (TN *)malloc(initialSize * sizeof(TREE_NODE));
  a->used = 0;
  a->size = initialSize;
}

void insertTNArray(TN_Array *a, TN element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (TN *)realloc(a->array, a->size * sizeof(TREE_NODE));
  }
  a->array[a->used++] = element;
}

TN getTNArrayVal(TN_Array *a, int index) {
    return a->array[index];
}

int getTNArraySize(TN_Array *a) {
    return a->used;
}

void freeTNArray(TN_Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

//int main() {
//    Array a;
//    int i;

//    initArray(&a, 5);  // initially 5 elements
//    for (i = 0; i < 100; i++)
//  	insertArray(&a, i);  // automatically resizes as necessary
//    printf("%ld\n", getArrayVal(&a, 9));  // print 10th element
//    printf("%d\n", getArraySize(&a));  // print number of elements
//    freeArray(&a);
//}
