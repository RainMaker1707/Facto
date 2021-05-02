#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "ListTool.h"
#include "Primes.h"


int main(int argc, char* argv[]){
    double start = (double) time(NULL);
    // ********* BEGIN PARSE ARG **********
    int threadNumber = 4;
    char* inputFile = "";
    char* outputFile = "";
    // Case with to less arg
    if (argc < 3) {
        fprintf(stderr, "You should be use at least two file paths in argument\n");
        return EXIT_FAILURE;
    // Case without option
    }else if (argc == 3){
        inputFile = argv[1];
        outputFile = argv[2];
    // Case with option on thread number
    }else if (argc == 5){
        int found = 0;
        for (int i = 1; i < argc - 1; i++){ // Search for option '-N'
            if(strcmp(argv[i], "-N") == 0){
                threadNumber = strtol(argv[i+1], NULL, 10);
                if (threadNumber == 0) {
                    fprintf(stderr, "You should use at least 1 thread\n");
                    return EXIT_FAILURE;
                }
                found = 1;

                //setting input and output files
                if (i == 1){
                    inputFile = argv[3];
                    outputFile = argv[4];
                }else if (i == 2){
                    inputFile = argv[1];
                    outputFile = argv[4];
                }else if (i == 3){
                    inputFile = argv[1];
                    outputFile = argv[2];
                }
                break;
            }
        }
        // Case of too much arguments without '-N' option
        if(!found){
            fprintf(stderr, "ARGUMENTS ERROR!\n");
            return EXIT_FAILURE;
        }
    }else{
        printf("ARGUMENTS ERROR!\n");
        return EXIT_FAILURE;
    }
    fprintf(stderr, "INPUT FILE >>> %s\nOUTPUT FILE >>> %s\nTHREADS NUMBER >>> %d\n", inputFile, outputFile, threadNumber);
    factorFile(inputFile, outputFile, threadNumber);//COMPUTE HERE
    double end = (double) time(NULL);
    fprintf(stderr, "ELAPSED TIME >>> %f seconds\n", end-start);
    fprintf(stderr, ">>> EXIT <<<\n");
    return EXIT_SUCCESS;
}