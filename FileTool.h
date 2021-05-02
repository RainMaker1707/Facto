#ifndef FACTO_FILETOOL_H
#define FACTO_FILETOOL_H

#include <stdio.h>
#include <stdlib.h>

#include "ListTool.h"

int getData(char* filename, divList* lst);

void clearFile(char* filename);

void saveData(char *file, divList* lst);

#endif //FACTO_FILETOOL_H
