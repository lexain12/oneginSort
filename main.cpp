#include <stdio.h>
#include <assert.h>

#include "functions.h"

int main() 
{
    InputFile inputFile = {"HamletOrig.txt"};

    readFileToArray(&inputFile);

    sortOnegin(&inputFile);

    printArrayInFile("HamletOutput.txt", &inputFile);

    return 0;
}


