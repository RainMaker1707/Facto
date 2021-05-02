#include "ListTool.h"

list* createList(uint64_t value) {
    /*
     * constructor function of list
     */
    list * lst = malloc(sizeof(list));
    node* n = malloc(sizeof(node));
    if (!lst || !n) return NULL;
    lst->size = 1;
    n->next = NULL;
    n->value = value;
    lst->head = n;
    lst->tail = n;
    return lst;
}


int append(uint64_t value, list* lst){
    /*
     * appends at the tail of a list a node which contains value;
     * return 0 in case of malloc error, 1 else
     */
    node* to_add = malloc(sizeof(node));
    if(!to_add) return 0;
    to_add->next = NULL;
    to_add->value = value;
    if(!lst->head){
        lst->head = to_add;
        lst->tail = to_add;
        lst->size = 1;
    }else{
        lst->tail->next = to_add;
        lst->tail = lst->tail->next;
        lst->size ++;
    }
    return 1;
}


divList* createDivList() {
    /*
     * constructor function of listDivList
     */
    divList* out = malloc(sizeof(divList));
    if(!out) return NULL;
    out->max = 0;
    out->root = NULL;
    out->size = 0;
    return out;
}

int appendDivNode(divList *lst, uint64_t value) {
    /*
    * append value to divList
    * value (uint64_t) -> int from the file
    */
    divNode* new = malloc(sizeof(divNode));
    if (!new) return -1;
    new->value = value;
    new->copy = value;
    new->divisors = NULL;
    if (!lst->root) { // empty root
        new->next = NULL;
        lst->root = new;
    } else {
        new->next = lst->root;
        lst->root = new;
    }
    lst->size++;
    if (value > lst->max) lst->max = value;
    return 0;
}

uint64_t getMax(divList* input) {
    /*
     * return the max int of the input list
     */
    uint64_t max = 0;
    divNode* parser = input->root;
    for (int i = 0; i < input->size; i++) {
        if (parser->copy > max) max = parser->copy;
        parser = parser->next;
    }
    return max;
}

list* createPrimesList(int value, divList* input) {
    /*
    * init the list of primes number
    *  value (int) -> by default it's 2 but i let the possibility to change it
    *  input -> divList (see doc at the structure declaration)
    */
    list* lst = createList(value);
    divNode *parser = input->root;
    for (int i = 0; i < input->size; i++) {
        if (parser->copy % value == 0) {
            int must_change = 0;
            if(value != parser->value) {
                if (!(parser->divisors)) parser->divisors = createList(value);
                else append(value, parser->divisors);
            }
            if (parser->copy == input->max)
                must_change = 1;
            while (parser->copy % value == 0) parser->copy = parser->copy / value;
            if (must_change == 1) input->max = getMax(input);
        }
        parser = parser->next;
    }
    return lst;
}

int appendPrimes(uint64_t value, list *lst, divList* input) {
    /*
     * appends at the tail of a list a node which contains value;
     *  value (uint64_t) -> the prime number to append
     *  lst -> the list of prime numbers
     *  input -> listDivList (see doc at the structure declaration)
     * return -1 in case of malloc error,  else 0
     */
    append(value, lst);
    // try to divide all number in listDivList
    divNode *parser = input->root;
    for (int i = 0; i < input->size; i++) {
        int must_change = 0;
        if (parser->copy % value == 0) {
            if(value != parser->value) {
                if (!(parser->divisors)) parser->divisors = createList(value);
                else append(value, parser->divisors);
            }
            if (parser->copy == input->max)
                must_change = 1;
            while (parser->copy % value == 0) parser->copy = parser->copy / value;
        }
        if (value > sqrt(parser->copy) && parser->copy != 1) {
            if (parser->divisors) append(parser->copy, parser->divisors);
            if (parser->copy == input->max) must_change = 1;
            parser->copy = 1;
        }
        if (must_change == 1) input->max = getMax(input);
        parser = parser->next;
    }
    return 0;
}


void freeList(list* lst){
    /*
     * function to free memory of all nodes in a list structure
     */
    node* toFree = lst->head;
    while(lst->head != lst->tail){
        lst->head = lst->head->next;
        free(toFree);
        toFree = lst->head;
    }
    free(toFree);
    free(lst);
}

void printList(list* lst){
    /*
     * print a list
     */
    node* toPrint = lst->head;
    printf("[");
    for(int i = 0; i < lst->size - 1; i++) {
        printf("%llu, ", toPrint->value);
        toPrint = toPrint->next;
    }
    printf("%llu]\n", toPrint->value);
}

void freeDivList(divList* lst){
    /*
     * free all the memory allocated for a divList
     */
    divNode* toFree = lst->root;
    for(int i = 0; i < lst->size; i++){
        divNode* next = toFree->next;
        if(toFree->divisors) freeList(toFree->divisors);
        free(toFree);
        toFree = next;
    }
    free(lst);
}


void printDivList(divList* l) {
    /*
    * print all number as number -> [prime factors]
    */
    divNode* parser = l->root;
    for (int i = 0; i < l->size; i++) {
        printf("%llu ->", parser->value);
        if (!parser->divisors) printf("[]\n");
        else printList(parser->divisors);
        parser = parser->next;
    }
}
