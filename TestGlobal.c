#define DOING_UNIT_TESTS
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "Primes.c"
#include "ListTool.c"
#include "ArrayTool.c"
#include "FileTool.c"


void TestingOddX2Result(){
  char* input_filename = "./Ressources/TestFiles/Input_TestODDX2.txt";
  char* good_output_filename = "./Ressources/TestFiles/Output_TestODDX2.txt";
  char* output_filename = "./Ressources/TestFiles/OutputReturn_TestODDX2.txt";
  char *l1, *l2;
  factorFile(input_filename, output_filename, 4);
  int verif = 0;
  int verif2 = 0;
  char good_output_line[256] = "";
  char output_to_test_line[256] = "";
  FILE* good_output = fopen(good_output_filename, "r");
  FILE* output_to_test = fopen(output_filename, "r");
  while ((l2=fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test)),
  l2!=NULL) {
    verif++;
  }
  rewind(output_to_test);
  while ( (l1 = fgets(good_output_line, sizeof(good_output_line), good_output)),
          l1 != NULL)
          {
            l1[strlen(l1)-1] = '\0';
            verif2++;
            l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
            l2[strlen(l2)-1] = '\0';
            while (strcmp(l1,l2)) {
              l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
              if (l2==NULL) {
                break;
              }
              l2[strlen(l2)-1] = '\0';
            }
            if (l2!=NULL) {
              CU_ASSERT(!strcmp(good_output_line, output_to_test_line));
            }
            else {
              CU_ASSERT(0);
            }
            rewind(output_to_test);
  }
  printf("Finished1\n");
  CU_ASSERT(l1 == NULL && verif==verif2);
}

void TestingCourseExampleResult(){
  char* input_filename = "./Ressources/TestFiles/Input_TestCourseExample.txt";
  char* good_output_filename = "./Ressources/TestFiles/Output_TestCourseExample.txt";
  char* output_filename = "./Ressources/TestFiles/OutputReturn_TestCourseExample.txt";
  char *l1, *l2;
  factorFile(input_filename, output_filename, 4);
  int verif = 0;
  int verif2 = 0;
  char good_output_line[256] = "";
  char output_to_test_line[256] = "";
  FILE* good_output = fopen(good_output_filename, "r");
  FILE* output_to_test = fopen(output_filename, "r");
  while ((l2=fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test)),
  l2!=NULL) {
    verif++;
  }
  rewind(output_to_test);
  while ( (l1 = fgets(good_output_line, sizeof(good_output_line), good_output)),
          l1 != NULL)
          {
            l1[strlen(l1)-1] = '\0';
            verif2++;
            l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
            l2[strlen(l2)-1] = '\0';
            while (strcmp(l1,l2)) {
              l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
              if (l2==NULL) {
                break;
              }
              l2[strlen(l2)-1] = '\0';
            }
            if (l2!=NULL) {
              CU_ASSERT(!strcmp(good_output_line, output_to_test_line));
            }
            else {
              CU_ASSERT(0);
            }
            rewind(output_to_test);
  }
  printf("Finished2\n");
  CU_ASSERT(l1 == NULL && verif==verif2);
}

void TestingFullOfOddResult(){
  char* input_filename = "./Ressources/TestFiles/Input_TestFullOdd.txt";
  char* good_output_filename = "./Ressources/TestFiles/Output_TestFullOdd.txt";
  char* output_filename = "./Ressources/TestFiles/OutputReturn_TestFullOdd.txt";
  char *l1, *l2;
  factorFile(input_filename, output_filename, 4);
  int verif = 0;
  int verif2 = 0;
  char good_output_line[256] = "";
  char output_to_test_line[256] = "";
  FILE* good_output = fopen(good_output_filename, "r");
  FILE* output_to_test = fopen(output_filename, "r");
  while ((l2=fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test)),
  l2!=NULL) {
    verif++;
  }
  rewind(output_to_test);
  while ( (l1 = fgets(good_output_line, sizeof(good_output_line), good_output)),
          l1 != NULL)
          {
            l1[strlen(l1)-1] = '\0';
            verif2++;
            l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
            l2[strlen(l2)-1] = '\0';
            while (strcmp(l1,l2)) {
              l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
              if (l2==NULL) {
                break;
              }
              l2[strlen(l2)-1] = '\0';
            }
            if (l2!=NULL) {
              CU_ASSERT(!strcmp(good_output_line, output_to_test_line));
            }
            else {
              CU_ASSERT(0);
            }
            rewind(output_to_test);
  }
  printf("Finished3\n");
  CU_ASSERT(l1 == NULL && verif==verif2);
}

void test_small_primes(){
    char* input_filename = "./Ressources/TestFiles/small_primes_input.txt";
    char* good_output_filename = "./Ressources/TestFiles/small_primes_output.txt";
    char* output_filename = "./Ressources/TestFiles/output_small_primes_test.txt";
    char *l1, *l2;
  factorFile(input_filename, output_filename, 4);
  int verif = 0;
  int verif2 = 0;
  char good_output_line[256] = "";
  char output_to_test_line[256] = "";
  FILE* good_output = fopen(good_output_filename, "r");
  FILE* output_to_test = fopen(output_filename, "r");
  while ((l2=fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test)),
  l2!=NULL) {
    verif++;
  }
  rewind(output_to_test);
  while ( (l1 = fgets(good_output_line, sizeof(good_output_line), good_output)),
          l1 != NULL)
          {
            l1[strlen(l1)-1] = '\0';
            verif2++;
            l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
            l2[strlen(l2)-1] = '\0';
            while (strcmp(l1,l2)) {
              l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
              if (l2==NULL) {
                break;
              }
              l2[strlen(l2)-1] = '\0';
            }
            if (l2!=NULL) {
              CU_ASSERT(!strcmp(good_output_line, output_to_test_line));
            }
            else {
              CU_ASSERT(0);
            }
            rewind(output_to_test);
  }
  printf("Finished6\n");
  CU_ASSERT(l1 == NULL && verif==verif2);
}

void test_empty_file(){
    char* input_filename = "./Ressources/TestFiles/input_empty_file.txt";
    char* good_output_filename = "./Ressources/TestFiles/output_empty_file.txt";
    char* output_filename = "./Ressources/TestFiles/output_empty_files_tests.txt";
    char *l1, *l2;
  factorFile(input_filename, output_filename, 4);
  int verif = 0;
  int verif2 = 0;
  char good_output_line[256] = "";
  char output_to_test_line[256] = "";
  FILE* good_output = fopen(good_output_filename, "r");
  FILE* output_to_test = fopen(output_filename, "r");
  while ((l2=fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test)),
  l2!=NULL) {
    verif++;
  }
  rewind(output_to_test);
  while ( (l1 = fgets(good_output_line, sizeof(good_output_line), good_output)),
          l1 != NULL)
          {
            l1[strlen(l1)-2] = '\0';
            verif2++;
            l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
            l2[strlen(l2)-1] = '\0';
            while (strcmp(l1,l2)) {
              l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
              if (l2==NULL) {
                break;
              }
              l2[strlen(l2)-1] = '\0';
            }
            if (l2!=NULL) {
              CU_ASSERT(!strcmp(good_output_line, output_to_test_line));
            }
            else {
              CU_ASSERT(0);
            }
            rewind(output_to_test);
  }
  printf("Finished4\n");
  CU_ASSERT(l1 == NULL && verif==verif2);
}

void test_one_line_file(){
    char* input_filename = "./Ressources/TestFiles/one_line_test.txt";
    char* good_output_filename = "./Ressources/TestFiles/one_line_output.txt";
    char* output_filename = "./Ressources/TestFiles/output_managing_files_tests.txt";
    char *l1, *l2;
  factorFile(input_filename, output_filename, 4);
  int verif = 0;
  int verif2 = 0;
  char good_output_line[256] = "";
  char output_to_test_line[256] = "";
  FILE* good_output = fopen(good_output_filename, "r");
  FILE* output_to_test = fopen(output_filename, "r");
  while ((l2=fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test)),
  l2!=NULL) {
    verif++;
  }
  rewind(output_to_test);
  while ( (l1 = fgets(good_output_line, sizeof(good_output_line), good_output)),
          l1 != NULL)
          {
            l1[strlen(l1)-2] = '\0';
            verif2++;
            l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
            l2[strlen(l2)-1] = '\0';
            while (strcmp(l1,l2)) {
              l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
              if (l2==NULL) {
                break;
              }
              l2[strlen(l2)-1] = '\0';
            }
            if (l2!=NULL) {
              CU_ASSERT(!strcmp(good_output_line, output_to_test_line));
            }
            else {
              CU_ASSERT(0);
            }
            rewind(output_to_test);
  }
  printf("Finished5\n");
  CU_ASSERT(l1 == NULL && verif==verif2);
}

void test_big_numbers(){
    char* input_filename = "./Ressources/TestFiles/big_numbers_input.txt";
    char* good_output_filename = "./Ressources/TestFiles/big_numbers_output.txt";
    char* output_filename = "./Ressources/TestFiles/output_big_numbers_test.txt";
    char *l1, *l2;
  factorFile(input_filename, output_filename, 4);
  int verif = 0;
  int verif2 = 0;
  char good_output_line[256] = "";
  char output_to_test_line[256] = "";
  FILE* good_output = fopen(good_output_filename, "r");
  FILE* output_to_test = fopen(output_filename, "r");
  while ((l2=fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test)),
  l2!=NULL) {
    verif++;
  }
  rewind(output_to_test);
  while ( (l1 = fgets(good_output_line, sizeof(good_output_line), good_output)),
          l1 != NULL)
          {
            l1[strlen(l1)-2] = '\0';
            verif2++;
            l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
            l2[strlen(l2)-1] = '\0';
            while (strcmp(l1,l2)) {
              l2 = fgets(output_to_test_line, sizeof(output_to_test_line), output_to_test);
              if (l2==NULL) {
                break;
              }
              l2[strlen(l2)-1] = '\0';
            }
            if (l2!=NULL) {
              CU_ASSERT(!strcmp(good_output_line, output_to_test_line));
            }
            else {
              CU_ASSERT(0);
            }
            rewind(output_to_test);
  }
  printf("Finished6\n");
  CU_ASSERT(l1 == NULL && verif==verif2);
}

int main(){
  if(CUE_SUCCESS != CU_initialize_registry()){
    return CU_get_error();
  }

  CU_pSuite pSuite = NULL;
  CU_pSuite fileManagingSuite = NULL;
  CU_pSuite pSuite2 = NULL;
  pSuite = CU_add_suite("TestProjet3", NULL, NULL);
  fileManagingSuite = CU_add_suite("Test suite for file managing", NULL, NULL);
  pSuite2 = CU_add_suite("TestProjet3(2)", NULL, NULL);
  if (pSuite == NULL || fileManagingSuite == NULL || pSuite2 == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if ((NULL == CU_add_test(pSuite, "TestODDX2", TestingOddX2Result)) ||
        (NULL == CU_add_test(pSuite,"TestCourseExample", TestingCourseExampleResult)) ||
        (NULL == CU_add_test(pSuite,"TestFullOdd", TestingFullOfOddResult)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if ((NULL == CU_add_test(fileManagingSuite, "Test with empty file", test_empty_file) ||
      (NULL == CU_add_test(fileManagingSuite, "Test with one line file", test_one_line_file)))){
        CU_cleanup_registry();
        return CU_get_error();
  }

  if (((NULL == CU_add_test(pSuite2, "Test with small primes", test_small_primes)))){
        CU_cleanup_registry();
        return CU_get_error();
    }

  CU_basic_run_tests();
}
