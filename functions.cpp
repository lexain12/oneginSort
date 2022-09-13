#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "../MyFunctions/QsortFunc.h"


#include "functions.h"

int isBigger(const char* line1, const char* line2)
{
    assert(line1 != nullptr);
    assert(line2 != nullptr);

    while (*line1 && *line2 && *line1 != '\n' && *line2 != '\n') 
    {
        if (isalpha(*line1) && isalpha(*line2))
        {
            if (toupper(*line1) != toupper(*line2))
            {
                return toupper(*line1) > toupper(*line2);
            }
            ++line1;
            ++line2;
        }
        while (!isalpha(*line1) && *line1 != '\n') 
            ++line1;

        while (!isalpha(*line2) && *line2 != '\n')
            ++line2;
    }

    return *line1 - *line2;
}

char* readFile(InputFile *inputFile)
{
    FILE* openedFile = fopen(inputFile->fileName, "r");

    fseek(openedFile, 0l, 2);

    size_t numberOfChars = ftell(openedFile);

    fseek(openedFile, 0l, 0);
    char* fileArray = (char*) calloc(numberOfChars, sizeof(char));
    assert(fread((void*) fileArray, sizeof(char), numberOfChars, openedFile) != 0); // GOvno

    int i = 0;
    for (;fileArray[i] != '\0'; i++) 
    {
        if (fileArray[i] == '\n')
        {
            inputFile->numberOfLines += 1;
            fileArray[i] = '\0';
        }
    }
//    fprintf(stderr, "%s", fileArray);
//    fprintf(stderr, "%d", inputFile->numberOfLines);

    fileArray[i] = '\n';

    fclose(openedFile);

    return fileArray;
}

void splitIntoLines(char* fileArray, InputFile *inputFile)
{
    assert(fileArray != NULL);
    assert(inputFile != NULL);

    inputFile->arrayOfLines = (Line*) calloc(inputFile->numberOfLines, sizeof(Line));
    assert(inputFile->arrayOfLines != NULL);
    
    int line = 0;

//    fprintf(stderr, "%s", ((inputFile->arrayOfLines)[line]).charArray);
    
    ((inputFile->arrayOfLines)[line]).charArray = fileArray;

//    fprintf(stderr, "%s", ((inputFile->arrayOfLines)[line]).charArray);

    line++;

    int i = 1;
    for (; fileArray[i+1] != '\n'; i++)
    {
        if (fileArray[i] == '\0')
        {
           ((inputFile->arrayOfLines)[line - 1]).length = &fileArray[i] - ((inputFile->arrayOfLines)[line - 1]).charArray;
//           fprintf(stderr, "%d %d\n", &fileArray[i], ((inputFile->arrayOfLines)[line - 1]).charArray);
           (inputFile->arrayOfLines[line]).charArray =  &fileArray[i+1];
//           fprintf(stderr, "%s\n", ((inputFile->arrayOfLines)[line]).charArray);
//           fprintf(stderr, "%d\n", ((inputFile->arrayOfLines)[line - 1]).length);
           line++;
        }
    }

    ((inputFile->arrayOfLines)[line - 1]).length = &fileArray[i] - ((inputFile->arrayOfLines)[line - 1]).charArray;
    (inputFile->arrayOfLines[line++]).charArray =  &fileArray[i+1];
}

//int countLines(FILE *inputFile)
//{
//    ASSERT(inputFile != nullptr); 
//
//    size_t counter = 0;
//
//    rewind(inputFile);
//
//    char line[256] = "";
//    while (fgets(line, 256, inputFile))
//    {
//        ++counter;
//    }
//
//    return counter;
//}

//void readLines(char **arrayOfLines, FILE *inputFile, size_t numberOfLines)
//{
//    ASSERT(arrayOfLines != NULL);
//    ASSERT(inputFile    != NULL);
//
//    rewind(inputFile);
//
//    for (size_t index = 0; index < numberOfLines; ++index)
//    {
//        char *line = (char*) calloc(256, sizeof(char));
//
//        fgets(line, 256, inputFile);
//
//        arrayOfLines[index] = line;
//    }
//}

void sortOnegin(InputFile* inputFile) // size_t
{

//    fprintf(stderr, "%d\n", inputFile->numberOfLines);
    Qsort(inputFile->arrayOfLines, inputFile->numberOfLines, sizeof(Line), cmpstruct);
//
//    for (int i = 0; i < inputFile->numberOfLines; ++i)
//    {
//        for (int j = i; j < inputFile->numberOfLines; ++j) 
//        {
//            if (strcmp(inputFile->arrayOfLines[i], inputFile->arrayOfLines[j]) > 0)
//            {
//                char* tmp = inputFile->arrayOfLines[i];
//                inputFile->arrayOfLines[i] = inputFile->arrayOfLines[j];
//                inputFile->arrayOfLines[j] = tmp;
//            }
//        }
//    }
}
//
//void readFileToArray(InputFile* inputFile)
//{
//    FILE *openedFile = fopen(inputFile->fileName, "r");
//    ASSERT(openedFile != nullptr);
//    
//    inputFile->numberOfLines = countLines(openedFile);
//
//    inputFile->arrayOfLines = (char**) calloc(inputFile->numberOfLines, sizeof(char *));
//    ASSERT(inputFile->arrayOfLines != nullptr);
//
//    readLines(inputFile->arrayOfLines, openedFile, inputFile->numberOfLines);
//
//    fclose(openedFile);
//}

void printArrayInFile(const char* outputFile,InputFile* inputFile)
{
    FILE* fileToPrint = fopen(outputFile, "a");
    ASSERT(fileToPrint != nullptr);
    fseek(fileToPrint, 0l, 2);

    for (size_t i = 0; i < inputFile->numberOfLines; ++i)
        fprintf(fileToPrint, "%s\n", ((inputFile->arrayOfLines)[i]).charArray);

    fclose(fileToPrint);
}

