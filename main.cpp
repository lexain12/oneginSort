#include <stdio.h>
#include <assert.h>

#include "functions.h"

int main() 
{
    InputFile inputFile = {"HamletOrig.txt"};

    splitIntoLines(readFile(&inputFile), &inputFile);
    printf("Ok\n");
    printf("%i\n", inputFile.numberOfLines);

    sortOnegin(&inputFile);

    for (int i = 0; i < inputFile.numberOfLines; i++)
    {
        printf("%s\n", inputFile.arrayOfLines[i]);
    }

    printArrayInFile("HamletOutput.txt", &inputFile);

    return 0;
}


