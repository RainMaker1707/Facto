#ifndef FACTO_PRIMES_H
#define FACTO_PRIMES_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ListTool.h"
#include "ArrayTool.h"
#include "FileTool.h"

typedef struct argThread{
    Array *id, *min;
    int currentThreadNumber;
    int value, threadNumber, flag;
    list* lst;
    divList* input;
} argThread;


int is_prime(unsigned long long int value, list* lst);

int much_wait(Array *id, int currentThreadNumber);

int speed_bump(Array *min, int value);

argThread* makeThreadArgs(divList* input, int value, int threadNumber, list* lst, Array* id,
                          int currentThreadNumber, Array* min, int flag);

void* threadOperation(void* t);

int getPrimes(divList* input, int threadNumber);

int factorFile(char* inputFile, char* outputFile, int threadNumber);

#endif //FACTO_PRIMES_H
