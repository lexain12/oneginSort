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
                return toupper(*line1) - toupper(*line2);
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

size_t fileSize (FILE* file)
{
    fseek(file, 0l, SEEK_END); 
    size_t size = ftell(file); 
    fseek(file, 0l, SEEK_SET);

    return size;
}

void readFile(InputFile *inputFile)
{
    assert(inputFile != NULL);

    FILE* openedFile = fopen(inputFile->fileName, "r");
    assert(openedFile != NULL);

    size_t numberOfChars = fileSize(openedFile);

    inputFile->text= (char*) calloc(numberOfChars, sizeof(char));
    size_t charsReaded = fread((void*) inputFile->text, sizeof(char), numberOfChars, openedFile); // 
    assert(charsReaded == numberOfChars); 

    size_t i = 0; 
    for (;inputFile->text[i] != '\0'; i++) 
    {
        if (inputFile->text[i] == '\n')
        {
            inputFile->numberOfLines += 1;
            inputFile->text[i] = '\0';
        }
    }
//    fprintf(stderr, "%s", fileArray);
//    fprintf(stderr, "%d", inputFile->numberOfLines);

    inputFile->text[i] = '\n';

    fclose(openedFile);
}

void splitIntoLines(InputFile *inputFile)
{
    assert(inputFile->text != NULL);
    assert(inputFile       != NULL);

    inputFile->arrayOfLines = (Line*) calloc(inputFile->numberOfLines, sizeof(Line));
    assert(inputFile->arrayOfLines != NULL);
    
    size_t line = 0;

//    fprintf(stderr, "%s", ((inputFile->arrayOfLines)[line]).charArray);
    
    ((inputFile->arrayOfLines)[line]).charArray = inputFile->text;

//    fprintf(stderr, "%s", ((inputFile->arrayOfLines)[line]).charArray);

    line++;

    size_t i = 0;
    for (; inputFile->text[i+1] != '\n'; i++)
    {
        if (inputFile->text[i] == '\0')
        {
           inputFile->arrayOfLines[line - 1].length = &(inputFile->text)[i] - inputFile->arrayOfLines[line - 1].charArray;// govno
//           fprintf(stderr, "%d %d\n", &fileArray[i], ((inputFile->arrayOfLines)[line - 1]).charArray);
           inputFile->arrayOfLines[line].charArray =  &(inputFile->text)[i + 1];
//           fprintf(stderr, "%s\n", ((inputFile->arrayOfLines)[line]).charArray);
//           fprintf(stderr, "%d\n", ((inputFile->arrayOfLines)[line - 1]).length);
           line++;
        }
    }

    inputFile->arrayOfLines[line - 1].length = &(inputFile->text)[i] - inputFile->arrayOfLines[line - 1].charArray;
    inputFile->arrayOfLines[line++].charArray =  &(inputFile->text)[i+1];
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
    assert(inputFile != nullptr);

//    fprintf(stderr, "%d\n", inputFile->numberOfLines);
    Qsort(inputFile->arrayOfLines, inputFile->numberOfLines, sizeof(Line), cmpstruct);
}
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

void printArrayInFile(const char* outputFile,InputFile* inputFile, int printArg)
{
    switch (printArg)
    {
        case sortedArray:
        {
            FILE* fileToPrint = fopen(outputFile, "w");
            ASSERT(fileToPrint != nullptr);
            // fseek(fileToPrint, 0l, SEEK_SET);

            for (size_t i = 0; i < inputFile->numberOfLines; ++i)
                fprintf(fileToPrint, "%s\n", ((inputFile->arrayOfLines)[i]).charArray);

            fclose(fileToPrint);
            return;
        }
        case reversedArray:
        {
            FILE* fileToPrint = fopen(outputFile, "a");
            ASSERT(fileToPrint != nullptr);
            // fseek(fileToPrint, 0l, SEEK_END);

            fprintf(fileToPrint, "-------------------------------------------------------\n");

            for (size_t i = 0; i < inputFile->numberOfLines; ++i)
                fprintf(fileToPrint, "%s\n", ((inputFile->arrayOfLines)[i]).charArray);

            fclose(fileToPrint);
            return;
        }
        case origArray:
        {
            FILE* fileToPrint = fopen(outputFile, "a");
            fprintf(fileToPrint, "------------------------------------------------------\n");

            size_t i = 0;
            for (;inputFile->text[i] != '\n'; i++) 
            {
                if (inputFile->text[i] == '\0') 
                {
                    inputFile->numberOfLines += 1;
                    inputFile->text[i] = '\n';
                }
            }
        //    fprintf(stderr, "%s", fileArray);
        //    fprintf(stderr, "%d", inputFile->numberOfLines);

            inputFile->text[i] = '\0';
            fprintf(fileToPrint, "%s", inputFile->text);
        }
    }
}

