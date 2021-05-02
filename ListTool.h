#ifndef FACTO_LISTTOOL_H
#define FACTO_LISTTOOL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

typedef struct node{
    unsigned long long int value;
    struct node* next;
}node;

typedef struct list{
    int size;
    node *head;
    node *tail;
}list;

typedef struct divNode{
    unsigned long long int value, copy;
    list *divisors;      // the list of prime divisor of the value
    struct divNode* next;
}divNode;

typedef struct divList{
    divNode* root;
    int size;
    unsigned long long int max;
}divList;


list* createList(uint64_t value);

int append(uint64_t value, list* lst);

divList* createDivList();

int appendDivNode(divList *lst, uint64_t value);

uint64_t getMax(divList* input);

list* createPrimesList(int value, divList* input);

int appendPrimes(uint64_t value, list *lst, divList* input);

void printList(list* lst);

void freeList(list* lst);

void freeDivList(divList* lst);

void printDivList(divList* l);

#endif //FACTO_LISTTOOL_H
