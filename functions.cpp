#include <stdio.h>
#include <ctype.h>
#include <assert.h>

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
        if (!isalpha(*line1))
            ++line1;

        if (!isalpha(*line2))
            ++line2;
    }

    if (*line1 == '\n')
        return false;

    return true;
}

int countLines(FILE *inputFile)
{
    assert(inputFile != nullptr);

    size_t counter = 0;

    char *line = (char*) calloc(256, sizeof(char));
    while (fgets(line, 256, inputFile))
    {
        ++counter;
    }
    free(line);
    rewind(inputFile);

    return counter;
}

void readLines(char **arrayOfLines, FILE *inputFile, int numberOfLines)
{
    assert(arrayOfLines != NULL);
    assert(inputFile    != NULL);

    for (size_t i = 0; i < numberOfLines; ++i)
    {
        char *line = (char*) calloc(256, sizeof(char));

        fgets(line, 256, inputFile);

        arrayOfLines[i] = line;
    }


}

void swapLines(char* line1, char* line2)
{
    char* tmp = line1;
    line1 = line2;
    line2 = tmp;
}

void sortOnegin(char** arrayOfLines, int numberOfLines)
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

int readFileToArray(const char* fileName, char*** arrayOfLines)
{
    FILE *inputFile = fopen(fileName, "r");
    assert(inputFile != NULL);
    
    int numberOfLines = countLines(inputFile);
    printf("%d", numberOfLines);

    *arrayOfLines = (char**) calloc(numberOfLines, sizeof(char *));
    readLines(*arrayOfLines, inputFile, numberOfLines);

    fclose(inputFile);

    return numberOfLines;
}

void printArrayInFile(const char* outputFile, const char*** arrayOfLines, int numberOfLines)
{
    FILE* fileToPrint = fopen(outputFile, "w+");

    for (int i = 0; i < numberOfLines; ++i)
    {
        fprintf(stderr, "%d %s\n", i, (*arrayOfLines)[i]);
        fprintf(fileToPrint, "%s", (*arrayOfLines)[i]);
    }
    fclose(fileToPrint);
}
