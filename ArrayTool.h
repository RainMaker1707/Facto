#ifndef FACTO_ARRAYTOOL_H
#define FACTO_ARRAYTOOL_H

typedef struct arr{
    unsigned long long int *array;
    int size;
} Array;


Array* createArray(int size, int init);

void freeArray(Array *a);

#endif //FACTO_ARRAYTOOL_H
