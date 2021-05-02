#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>

#include "Primes.h"

//Lists tests
void testCreateList(){
    list* lst = malloc(sizeof(list));
    node* n = malloc(sizeof(node));
    if (!lst || !n) return;
    lst->size = 1;
    n->next = NULL;
    n->value = 10;
    lst->head = n;
    lst->tail = n;

    list* toTest = createList(10);
    CU_ASSERT(lst->size == toTest->size);
    CU_ASSERT(lst->head->value == toTest->head->value);
    CU_ASSERT(lst->tail->value == toTest->tail->value);
    CU_ASSERT(lst->head->next == toTest->head->next);
    CU_ASSERT(lst->tail->next == toTest->tail->next);

    freeList(lst);
    freeList(toTest);
}

void testAppend(){
    list* lst = malloc(sizeof(list));
    if(!lst) return;
    lst->head = NULL;
    lst->size = 0;
    lst->tail = NULL;
    for(int i = 0; i < 100; i++){
        append(i, lst);
    }
    CU_ASSERT(lst->size == 100);

    node* toTest = lst->head;
    for(int i = 0; i < 100; i++){
        CU_ASSERT(toTest->value == i);
        toTest = toTest->next;
    }

    freeList(lst);
}

//DivLists tests
void testCreateDivList(){
    divList* temp = malloc(sizeof(divList));
    if(!temp) return;
    temp->size = 0;
    temp->max = 0;
    temp->root = NULL;
    divList* toTest = createDivList();
    CU_ASSERT(temp->size == toTest->size);
    CU_ASSERT(temp->max == toTest->max);
    CU_ASSERT(temp->root == toTest->root);
    freeDivList(temp);
    freeDivList(toTest);
}

void testAppendDivNode(){
    divList* temp = malloc(sizeof(divList));
    if(!temp) return;
    temp->size = 0;
    temp->root = NULL;
    temp->max = 0;
    for(int i = 0; i < 100; i++){
        divNode* toAdd = malloc(sizeof(divNode));
        toAdd->next = temp->root;
        toAdd->copy = i;
        toAdd->value = i;
        toAdd->divisors = NULL;
        temp->root = toAdd;
        if(i > temp->max) temp->max = i;
        temp->size++;
    }

    divList* toTest = createDivList();
    for(int i = 0; i < 100; i++){
        appendDivNode(toTest, i);
    }

    CU_ASSERT(temp->size == toTest->size);
    CU_ASSERT(temp->max == toTest->max);
    divNode* expected = temp->root;
    divNode* test = toTest->root;
    for(int i = 0; i < 100; i++){
        CU_ASSERT(expected->value == test->value);
        CU_ASSERT(expected->copy == test->copy);
        CU_ASSERT(expected->divisors == test->divisors);
        expected = expected->next;
        test = test->next;
    }

    freeDivList(temp);
    freeDivList(toTest);
}

//Other test for ListTool
void testGetMax(){
    divList* lst = createDivList();
    int end = 10;
    for(int j = 1; j < 10; j++) {
        for (int i = 0; i < end * j; i++) {
            appendDivNode(lst, i);
        }
        CU_ASSERT(lst->max == end * j - 1);
    }
    freeDivList(lst);
}

void testCreatePrimeList(){
    int size = 100;
    divList* temp = createDivList();
    for(int i = 2; i < size; i++){
        appendDivNode(temp, i);
    }
    list* primes = createPrimesList(2, temp);
    CU_ASSERT(temp->size == size - 2);
    CU_ASSERT(primes->head->value == 2);
    CU_ASSERT(primes->size == 1);
    CU_ASSERT(primes->tail->value == 2);

    divNode* test = temp->root;
    for(int i = 0; i < temp->size; i++){
        if(test->value % 2 == 0){
            if(test->divisors)CU_ASSERT(test->divisors->head->value == 2);
        }
        if(test->next) test = test->next;
    }
    freeList(primes);
    freeDivList(temp);
}

void testAppendPrimes(){
    int size = 100;
    divList* temp = createDivList();
    for(int i = 2; i < size; i++){
        appendDivNode(temp, i);
    }

    list* primes = createPrimesList(2, temp);
    for(int i = 0; i < 30; i++) {
        if (i == 3 || i == 5 || i == 7) appendPrimes(i, primes, temp);
        else if (i == 11 || i == 13 || i == 17) appendPrimes(i, primes, temp);
        else if (i == 19 || i == 23 || i == 29) appendPrimes(i, primes, temp);
    }

    divNode* test = temp->root;
    node* prime = primes->head;
    for(int i = 0; i < temp->size; i++){
        for(int j = 0; j < primes->size; j++){
            if(test->value % prime->value == 0){
                if(test->divisors) {
                    int found = 0;
                    node* div = test->divisors->head;
                    for(int k = 0; k < test->divisors->size; k++){
                        if(div->value == prime->value){
                            found = 1;
                            break;
                        }
                        if(div->next) div = div->next;
                    }
                    CU_ASSERT(found);
                }
            }
            if(prime->next) prime = prime->next;
        }
        test = test->next;
    }
    freeList(primes);
    freeDivList(temp);
}


//Tests primes functions
void testIsPrime(){
    int array[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                   31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                   73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
                   127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
                   179, 181, 191, 193, 197, 199, 211, 223, 227, 229};

    list* primes = createList(2);
    for(int i = 3; i < 230; i++){
        if (is_prime(i, primes)) append(i, primes);
    }
    CU_ASSERT(primes->size == 50);
    node* test = primes->head;
    for(int i = 0; i < 50; i++){
        CU_ASSERT(array[i] == test->value);
        if(test->next) test = test->next;
    }
    freeList(primes);
}

void testGetPrimeList(){
    divList* lst = createDivList();
    appendDivNode(lst, 230);
    appendDivNode(lst, 666);
    appendDivNode(lst, 42);
    getPrimes(lst, 4);
    divNode* div = lst->root;
    int array42[] = {2, 3, 7};
    int array666[] = {2, 3, 37};
    int array230[] = {2, 5, 23};

    for(int j = 0; j < lst->size; j++) {
        int *array;
        if (div->value == 42) array = (int*)array42;
        else if(div->value == 230) array = (int*)array230;
        else array = (int*) array666;
        node* temp = div->divisors->head;
        for (int i = 0; i < div->divisors->size; i++) {
            CU_ASSERT(temp->value == array[i]);
            if (temp->next) temp = temp->next;
        }
        if(div->next) div = div->next;
    }
    freeDivList(lst);
}

int main(int argc, char* argv[]){

    if(CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    CU_pSuite listSuite = CU_add_suite("List tools tests",  NULL, NULL);
    if(!listSuite){
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }
    if(!CU_add_test(listSuite, "Test createList()", testCreateList)){
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }
    if(!CU_add_test(listSuite, "Test append()", testAppend)){
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }


    CU_pSuite divListSuite = CU_add_suite("DivList tools tests", NULL, NULL);
    if(!divListSuite){
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }

    if(!CU_add_test(divListSuite, "Test createDivList()", testCreateDivList)){
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }

    if(!CU_add_test(divListSuite, "Test appendDivNode()", testAppendDivNode)){
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }

    CU_pSuite basicSuite = CU_add_suite("Basic tools tests", NULL, NULL);
    if(!basicSuite){
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }

    if(!CU_add_test(basicSuite, "Test getMax()", testGetMax)){
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }

    if(!CU_add_test(basicSuite, "Test CreatePrimeList()", testCreatePrimeList)){
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }

    if(!CU_add_test(basicSuite, "Test AppendPrimes()", testAppendPrimes)){
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }

    CU_pSuite primeSuite = CU_add_suite("Primes tools tests", NULL, NULL);
    if(!primeSuite){
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }

    if(!CU_add_test(primeSuite, "Test is_prime()", testIsPrime)){
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }

    if(!CU_add_test(primeSuite, "Test GetPrime()", testGetPrimeList)){
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }

    if(argc > 1) {
        if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--verbose")) {
            CU_basic_run_tests();
            CU_basic_show_failures(CU_get_failure_list());
        }
    }
    CU_automated_run_tests();

    return EXIT_SUCCESS;
}