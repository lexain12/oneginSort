#include <stdio.h>
#include <assert.h>
#include "functions.h"
#include "../MyFunctions/QsortFunc.h"


int main()
{
  InputFile inputFile = {"HamletOrig.txt"};

  splitIntoLines (readFile (&inputFile), &inputFile);
   
  sortOnegin(&inputFile);

  printArrayInFile("HamletOutput.txt", &inputFile);

  Qsort(inputFile.arrayOfLines, inputFile.numberOfLines, sizeof(Line), cmpstructReverse);

  addArrayInFile("HamletOutput.txt", &inputFile);

  return 0;
}


