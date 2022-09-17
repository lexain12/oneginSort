#include <stdio.h>
#include <assert.h>
#include <cstddef>
#include "functions.h"
#include "../MyFunctions/QsortFunc.h"

int main(int argc, const char *argv[])
{
    char* outputFile = "HamletOutput.txt";

    InputFile inputFile = {"HamletOrig.txt"};
    checkArg(argc, argv, &inputFile, &outputFile);

    // fileInput
    FILE* openedFile = fopen(inputFile.fileName, "r");
    Status status = (Status) readFileToLinesStruct(openedFile, &inputFile);

    qsort(inputFile.arrayOfLines, inputFile.numberOfLines, sizeof(Line), cmpstruct);

    FILE* fileOut = fopen(outputFile, "w");

    status = (Status) printArrayInFile(fileOut, &inputFile);
    fprintf(fileOut, "-------------------------------------------\n");

    Qsort(inputFile.arrayOfLines, inputFile.numberOfLines, sizeof(Line), cmpstructReverse);

    status = (Status) printArrayInFile(fileOut, &inputFile);
    fprintf(fileOut, "-------------------------------------------\n");

    printOrig(fileOut, inputFile.text);
    
    fclose(fileOut);

    return status;
}


