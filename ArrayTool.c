#include <stdio.h>
#include <stdlib.h>
#include "ArrayTool.h"

Array* createArray(int size, int init) {
    // constructor of array
    Array* a = malloc(sizeof(Array));
    if (!a) return NULL;
    a->array = (unsigned long long int *) malloc(size * sizeof(unsigned long long int));
    for (int i = 0; i < size; i++) a->array[i] = init;
    a->size = size;
    return a;
}

void freeArray(Array *a) {
    free(a->array);
    free(a);
}
