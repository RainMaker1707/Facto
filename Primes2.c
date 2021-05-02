#include "Primes2.h"

pthread_mutex_t inc_mutex = PTHREAD_MUTEX_INITIALIZER;

int is_prime2(unsigned long long int value, list* lst) {
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

void* threadOperation2(void* t){
    /*
     * Operation inside a thread
     * t is a structure which can import all variables we need in this functions casted in void*
     */
    arg_t* arg = (arg_t*) t;
    while(arg->input->max != 1){
        //check if is prime
        if(is_prime2(arg->value, arg->lst)){
            while(1){
                int counter = 0;
                for (int i = 0; i < arg->threadNumber; i++){
                    if (arg->value <= *arg->tab[i]) counter++;
                }
                if (counter == arg->threadNumber || arg->input->max == 1){
                    break;
                }else {
                    fprintf(stderr,"");
                    if(*arg->waiting <= 2) {
                        while(pthread_mutex_trylock(&inc_mutex) != 0){}
                        *(arg->waiting) += 1;
                        while(pthread_mutex_unlock(&inc_mutex) !=0){}
                        while(pthread_cond_wait(arg->cond, arg->mutex) != 0){}
                    }else{
                        while(pthread_cond_broadcast(arg->cond) != 0){}
                        while(pthread_mutex_trylock(&inc_mutex) != 0){}
                        *(arg->waiting) = 0;
                        while(pthread_mutex_unlock(&inc_mutex) != 0){}
                    }
                }
            }
            //append value in lst and divide all number in arg->input
            fprintf(stderr, "");
            while(pthread_mutex_unlock(arg->mutex) != 0){}
            usleep(42);
            while(pthread_mutex_trylock(arg->mutex) != 0){}
            appendPrimes(arg->value, arg->lst, arg->input);
            while(pthread_mutex_unlock(arg->mutex) != 0){}
            pthread_cond_broadcast(arg->cond);
        }
        //increase arg->value
        if (arg->threadNumber%2 == 0) arg->value += 3 * arg->threadNumber;
        else if ((arg->value+(3*arg->threadNumber)-1)%3 == 0) arg->value += (3 * arg->threadNumber) + 1;
        else arg->value += (3*arg->threadNumber) -1;
        //break;
    }
    if (arg->flag) pthread_exit(NULL);
    else return NULL;
}

int getPrimes2(divList* input, int threadNumber){
    /*
     * Input must be an initialized divList
     * ThreadNumber is the number of the thread you passer in argument -N
     * return 0 in case of error 1 else
     */
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

    //check pre condition like non empty file and threadNumber greater than 1
    if (input->size == 0 || threadNumber < 1) return 0;

    // Initialise the primeList
    list* primeList = createPrimesList(2, input);
    appendPrimes(3, primeList, input);
    appendPrimes(5, primeList, input);
    // init tab we need for init threads
    pthread_t threads[threadNumber -1];
    arg_t *threadArg[threadNumber];
    // init thread arguments
    unsigned long long int* tab[threadNumber];
    int waiting = 0;
    int index = 2;
    for(int i = 0; i < threadNumber; i++) {
        //arguments constructor
        arg_t *temp = malloc(sizeof(arg_t));
        if(!temp) return 0;
        threadArg[i] = temp;
        threadArg[i]->cond = &cond;
        threadArg[i]->mutex = &mutex;
        threadArg[i]->lst = primeList;
        threadArg[i]->input = input;
        threadArg[i]->waiting = &waiting;
        threadArg[i]->flag = 1;
        threadArg[i]->threadNumber = threadNumber;
        //increase and choose temp->value
        if ((3 + 2 * index) % 3 == 0) index++;
        threadArg[i]->value = (unsigned long long) 3 + 2 * index;
        tab[i] = &threadArg[i]->value;
        index++;
    }

    // setup link with others threads for each one
    for (int i = 0; i < threadNumber; i++) threadArg[i]->tab = tab;

    // flag to said if it's child thread or main thread set to main thread atcivity
    threadArg[threadNumber - 1]->flag = 0;
    // Build threads with setting function and void args
    for (int i = 0; i < threadNumber-1; i++) pthread_create(&threads[i], NULL, &threadOperation2, (void*) threadArg[i]);
    // Run main thread
    threadOperation2((void*) threadArg[threadNumber - 1]);
    // Join all thread and free linked args
    for (int i = 0; i < threadNumber-1; i++) pthread_join(threads[i], NULL);
    // free memory not more use
    freeList(primeList);
    for (int i = 0; i < threadNumber; i++) free(threadArg[i]);
    return 1;
}

int factorFile2(char* inputFile, char* outputFile, int threadNumber){
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
    if(!getPrimes2(final_lst, threadNumber)){
        printf("Error in compute primes list");
        return 0;
    }
    saveData(outputFile, final_lst);
    freeDivList(final_lst);
    return 1;
}
