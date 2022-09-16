#include <stdio.h>
#include <assert.h>
#include "functions.h"
#include "../MyFunctions/QsortFunc.h"

int main()
{
  InputFile inputFile = {"HamletOrig.txt"};
  readFile (&inputFile);
  splitIntoLines (&inputFile);
   
  sortOnegin(&inputFile);

  printArrayInFile("HamletOutput.txt", &inputFile, sortedArray);

  Qsort(inputFile.arrayOfLines, inputFile.numberOfLines, sizeof(Line), cmpstructReverse);

  printArrayInFile("HamletOutput.txt", &inputFile, reversedArray);

  printArrayInFile("HamletOutput.txt", &inputFile, origArray);

  return 0;
}


