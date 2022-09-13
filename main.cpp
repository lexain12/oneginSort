#include <stdio.h>
#include <assert.h>

#include "functions.h"

int cmpstruct(const void* arg1, const void* arg2);
void Qsort(void* array, size_t n, size_t size, int (*cmp)(const void*, const void*));
int cmpstructReverse(const void* arg1, const void* arg2);

int main()
{
  InputFile inputFile = {"HamletOrig.txt"};

  splitIntoLines (readFile (&inputFile), &inputFile);
   
  sortOnegin(&inputFile);

  printArrayInFile("HamletOutput.txt", &inputFile);

  Qsort(inputFile.arrayOfLines, inputFile.numberOfLines, sizeof(Line), cmpstructReverse);

  printArrayInFile("HamletOutput.txt", &inputFile);

  return 0;
}


