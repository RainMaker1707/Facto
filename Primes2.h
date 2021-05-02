#ifndef FACTO_PRIMES2_H
#define FACTO_PRIMES2_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <zconf.h>

#include "ListTool.h"
#include "ArrayTool.h"
#include "FileTool.h"

typedef struct arguments{
    unsigned long long int value;
    int threadNumber, flag;
    int* waiting;
    unsigned long long int **tab;
    list* lst;
    divList* input;
    pthread_cond_t* cond;
    pthread_mutex_t* mutex;
}arg_t;


int is_prime2(unsigned long long int value, list* lst);

void* threadOperation2(void* t);

int getPrimes2(divList* input, int threadNumber);

int factorFile2(char* inputFile, char* outputFile, int threadNumber);

#endif //FACTO_PRIMES2_H
