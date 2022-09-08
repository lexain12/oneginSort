#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

bool isBigger(const char* line1, const char* line2)
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

    if (*line1 == '\n')
        return false;

    return true;
}

char* readFile(InputFile *inputFile)
{
    FILE* openedFile = fopen(inputFile->fileName, "r");

    fseek(openedFile, 0l, 2);

    size_t numberOfChars = ftell(openedFile);

    printf("ok");
    fseek(openedFile, 0l, 0);
    char* fileArray = (char*) calloc(numberOfChars - 1, sizeof(char));
    printf("%li", fread((void*) fileArray, sizeof(char), numberOfChars-1, openedFile));

    int i = 0;
    for (;fileArray[i] != '\0'; i++) 
    {
        if (fileArray[i] == '\n')
        {
            fileArray[i] = '\0';
        }
    }

    fileArray[i] = '\n';

    fclose(openedFile);

    return fileArray;
}

void splitIntoLines(char* fileArray, InputFile *inputFile)
{
    FILE* openedFile = fopen(inputFile->fileName, "r");
    inputFile->numberOfLines = countLines(openedFile);
    inputFile->arrayOfLines = (char**) calloc(inputFile->numberOfLines-1, sizeof(char*));
    fclose(openedFile);
    
    int line = 0;

    inputFile->arrayOfLines[line] = fileArray;
    line++;

    int i = 1;
    for (; fileArray[i+1] != '\n'; i++)
    {
        if (fileArray[i] == '\0')
        {
           inputFile->arrayOfLines[line++] =  &fileArray[i+1];
        }
    }

    inputFile->arrayOfLines[line++] =  &fileArray[i+1];
    printf("%d\n", line);
}

int countLines(FILE *inputFile)
{
    ASSERT(inputFile != nullptr); 

    size_t counter = 0;

    rewind(inputFile);

    char line[256] = "";
    while (fgets(line, 256, inputFile))
    {
        ++counter;
    }

    return counter;
}

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
    for (int i = 0; i < inputFile->numberOfLines; ++i)
    {
        for (int j = i; j < inputFile->numberOfLines; ++j) 
        {
            if (strcmp(inputFile->arrayOfLines[i], inputFile->arrayOfLines[j]) > 0)
            {
                char* tmp = inputFile->arrayOfLines[i];
                inputFile->arrayOfLines[i] = inputFile->arrayOfLines[j];
                inputFile->arrayOfLines[j] = tmp;
            }
        }
    }
}

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
    FILE* fileToPrint = fopen(outputFile, "w+");
    ASSERT(fileToPrint != nullptr);

    for (size_t i = 0; i < inputFile->numberOfLines; ++i)
        fprintf(fileToPrint, "%s\n", (inputFile->arrayOfLines)[i]);

    fclose(fileToPrint);
}

