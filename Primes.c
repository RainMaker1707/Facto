#include "Primes.h"
pthread_mutex_t inc_mutex = PTHREAD_MUTEX_INITIALIZER;

int is_prime(unsigned long long int value, list* lst) {
    /*
    * value -> int
    * lst -> the prime list
    * return 0 if value is prime else 1
    */
    node* parser = lst->head;
    for(int i = 0; i < lst->size; i++){
        if (value % parser->value == 0) return 0;
        if (parser->value > sqrt(value)) break;
        parser = parser->next;
    }
    return 1;
}

argThread* makeThreadArgs(divList* input, int value, int threadNumber, list* lst, Array* id,
        int currentThreadNumber, Array* min, int flag) {
    /*
     * constructor function of argThread
     */
    argThread* arg = malloc(sizeof(argThread));
    if (!lst) return NULL;
    arg->lst = lst;
    arg->input = input;
    arg->threadNumber = threadNumber;
    arg->value = value;
    arg->id = id;
    arg->currentThreadNumber = currentThreadNumber;
    arg->min = min;
    arg->flag = flag;
    return arg;
}

int much_wait(Array *id, int currentThreadNumber) {
    /*
     * lock at the thread id to avoid that two threads append at the same time
     */
    int out = 1;
    for (int i = currentThreadNumber+1; i < id->size; i++) if (id->array[currentThreadNumber] > id->array[i]) {out = 0;}
    for (int i = 0; i < currentThreadNumber; i++) if (id->array[currentThreadNumber] >= id->array[i]) {out = 0;}
    return out;
}

int speed_bump(Array *min, int value) {
    /*
     * to slow down if a thread gone to fast
     */
    int out = 1;//flag true
    for (int i = 0; i < min->size; i++) if (min->array[i] < sqrt(value)) {out = 0;}
    return out;
}

void* threadOperation(void* t) {
    /*
    * the operation of thread
    * t -> argThread casted on void
    */
    argThread* arg = (argThread*) t;

    while (arg->input->max != 1) {
        arg->min->array[arg->currentThreadNumber] = arg->value;
        //wait until signal from another thread
        while (speed_bump(arg->min, arg->value) == 0) {}
        if (is_prime(arg->value, arg->lst)) {
            while (much_wait(arg->id, arg->currentThreadNumber) == 0) {
                if (arg->input->max == 1) break;
            }
            appendPrimes(arg->value, arg->lst, arg->input);
        }
        arg->id->array[arg->currentThreadNumber]++;
        //increase arg->value
        if (arg->threadNumber%2 == 0) arg->value += 3 * arg->threadNumber;
        else if ((arg->value+(3*arg->threadNumber)-1)%3 == 0) arg->value += (3 * arg->threadNumber) + 1;
        else arg->value += (3*arg->threadNumber) -1;
    }
    arg->min->array[arg->currentThreadNumber] = __LONG_LONG_MAX__; // to be sure
    if (arg->flag) pthread_exit(NULL);
    else return NULL;
}

int getPrimes(divList* input, int threadNumber) {
    /*
     * input must be an initialised listDivList (cf. makeListDivList and getData)
     * threadNumber (int) the number of thread (must be greater or equal than 1)
     * return 1 if error else 0
    */

    if(input->size == 0) {
      return 1;
    }
    if (threadNumber < 1) return 0;
    list *lst = createPrimesList(2, input);
    appendPrimes(3, lst, input);
    appendPrimes(5, lst, input);
    pthread_t threads[threadNumber-1];
    argThread *threadArgs[threadNumber];
    int index = 2;
    Array *id = createArray(threadNumber, 0);
    Array *min = createArray(threadNumber, 3);
    //Build threads arguments
    for (int i = 0; i < threadNumber-1; i++) {
        if ((3 + 2 * index) % 3 == 0) index++;
        threadArgs[i] = makeThreadArgs(input, 3 + 2 * index, threadNumber, lst, id, i+1, min, 1);
        index++;
    }

    // Build main thread arg
    argThread *arg = makeThreadArgs(input, 5, threadNumber, lst, id, 0, min, 0);

    //Build threads with setting function and void args
    for (int i = 0; i < threadNumber-1; i++) pthread_create(&threads[i], NULL, &threadOperation, (void*) threadArgs[i]);

    // Run main thread
    threadOperation((void*) arg); // launch on main thread

    //Join all thread and free linked args
    for (int i = 0; i < threadNumber-1; i++) pthread_join(threads[i], NULL);
    for (int i = 0; i < threadNumber-1; i++) free(threadArgs[i]);

    //free memory not more use
    free(arg);
    freeArray(id);
    freeArray(min);
    freeList(lst);
    return 1;
}

int factorFile(char* inputFile, char* outputFile, int threadNumber){
    /*
     * Open and getData from the inputFile,
     * generate a list of primes number from 2 to max/2,
     * clear or create the outputFile,
     * Finally saveData in the OutputFile
     * Free all malloced struct
     */

    divList* final_lst = createDivList();
    if(!getData(inputFile, final_lst)) {
        printf("FILE %s doesn't not exist\n", inputFile);
        return 0;
    }
    if(!getPrimes(final_lst, threadNumber)){
        printf("Error in compute primes list");
        return 0;
    }
    saveData(outputFile, final_lst);
    freeDivList(final_lst);
    return 1;
}

