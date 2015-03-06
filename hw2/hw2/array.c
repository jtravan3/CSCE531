#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "defs.h"

void initArray(Array *a, size_t initialSize) {
  a->array = (long *)malloc(initialSize * sizeof(long));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, long element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (long *)realloc(a->array, a->size * sizeof(long));
  }
  a->array[a->used++] = element;
}

long getArrayVal(Array *a, int index) {
    return a->array[index];
}

int getArraySize(Array *a) {
    return a->used;
}

void freeArray(Array *a) {
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
