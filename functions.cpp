#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#include "functions.h"

bool isBigger(const char* line1, const char* line2)
{
    assert(line1 != nullptr);
    assert(line2 != nullptr);

    for( ; *line1 && *line2 && *line1 != '\n' && *line2 != '\n'; ) 
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
        if (!isalpha(*line1)) // while
            ++line1;

        if (!isalpha(*line2)) // while
            ++line2;
    }

    if (*line1 == '\n')
        return false;

    return true;
}

int countLines(FILE *inputFile)
{
    assert(inputFile != nullptr); // ded assert

    size_t counter = 0;

    rewind(inputFile);

    char *line = (char*) calloc(256, sizeof(char)); // static
    while (fgets(line, 256, inputFile))
    {
        ++counter;
    }
    free(line);

    return counter;
}

void readLines(char **arrayOfLines, FILE *inputFile, int numberOfLines)
{
    assert(arrayOfLines != NULL);
    assert(inputFile    != NULL);

    rewind(inputFile);

    for (size_t i = 0; i < numberOfLines; ++i)
    {
        char *line = (char*) calloc(256, sizeof(char));

        fgets(line, 256, inputFile);

        arrayOfLines[i] = line;
    }
}

void sortOnegin(char** arrayOfLines, int numberOfLines) // size_t
{
    for (int i = 0; i < numberOfLines; ++i)
    {
        for (int j = i; j < numberOfLines; ++j) 
        {
            if (isBigger(arrayOfLines[i], arrayOfLines[j]))
            {
                char* tmp = arrayOfLines[i];
                arrayOfLines[i] = arrayOfLines[j];
                arrayOfLines[j] = tmp;
            }
        }
    }
}

void readFileToArray(InputFile* inputFile)
{
    FILE *openedFile = fopen(inputFile->fileName, "r");
    // check file
    
    inputFile->numberOfLines = countLines(openedFile);

    inputFile->arrayOfLines = (char**) calloc(inputFile->numberOfLines, sizeof(char *));
    // check ptr
    readLines(inputFile->arrayOfLines, openedFile, inputFile->numberOfLines);

    fclose(openedFile);
}

void printArrayInFile(const char* outputFile,InputFile* inputFile)
{
    FILE* fileToPrint = fopen(outputFile, "w+");
    // 

    for (size_t i = 0; i < inputFile->numberOfLines; ++i)
        fprintf(fileToPrint, "%s", (inputFile->arrayOfLines)[i]);

    fclose(fileToPrint);
}

