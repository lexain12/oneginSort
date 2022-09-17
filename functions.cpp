#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <cstddef>
#include "../MyFunctions/QsortFunc.h"

#include "functions.h"

int checkArg(int argc, const char* argv[], InputFile* inputFile, char** outputFilePtr)
{
    if (argc == 1)
    {
        printf("To change: -r for file to read, -w for file to write to\n");
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            if (argv[i - 1][0] == '-')
            {
                if (argv[i - 1][1] == 'r')
                {
                    inputFile->fileName = (char*) argv[i];
                }
                else if (argv[i - 1][1] == 'w')
                {
                    *outputFilePtr = (char*) argv[i];
                }
                else
                {
                    printf("Undefined argument\n");
                    return inputError;
                }
                
            }
        }
    }

    return noErrors;
}

size_t fileSize (FILE* file)
{
    fseek(file, 0l, SEEK_END); 
    size_t size = ftell(file); 
    fseek(file, 0l, SEEK_SET);

    return size;
}

int readFile(FILE* openedFile, char** dest)
{
    ASSERT(openedFile != nullptr);

    size_t numberOfChars = fileSize(openedFile);

    printf("filesize = %lu\n", numberOfChars);

    *dest = (char*) calloc(numberOfChars + 1, sizeof(char));

    size_t charsReaded = fread((void*) *dest, sizeof(char), numberOfChars, openedFile); // 
    if (charsReaded != numberOfChars)
        return readingError;
    
    return noErrors;
}

int textToStr(char* text, size_t* numberOfLines)
{
    ASSERT(text != nullptr);

    size_t i = 0; 
    for (; text[i] != '\0'; i++) 
    {
        if (text[i] == '\n')
        {
            *numberOfLines += 1;
            text[i] = '\0';
        }
    }
    
    text[i] = '\n';
    fprintf(stderr, "number of lines = %lu\n", *numberOfLines);

    return noErrors;
}

int splitIntoLines(InputFile *inputFile)
{
    ASSERT(inputFile != nullptr);
   
    char *text           =  inputFile->text;
    size_t numberOfLines =  inputFile->numberOfLines;
    Line **Lines         = &inputFile->arrayOfLines;

    ASSERT(text != NULL);

    *Lines = (Line*) calloc(numberOfLines, sizeof(Line));
    Line* arrayOfLines = *Lines;
    ASSERT(arrayOfLines != NULL);
    
    size_t line = 0;

//    fprintf(stderr, "%s", ((inputFile->arrayOfLines)[line]).charArray);
//    fprintf(stderr, "%s\n", ((arrayOfLines)[line]).charArray);
    arrayOfLines[line].charArray = text;
//    fprintf(stderr, "%s", ((inputFile->arrayOfLines)[line]).charArray);

    line++;

    size_t i = 0;
    for (; text[i + 1] != '\n'; i++)
    {
        if (text[i] == '\0')
        {
           fprintf(stderr, "line number is %lu\n", line);
           
           arrayOfLines[line - 1].length    = &(text)[i] - arrayOfLines[line - 1].charArray;
           arrayOfLines[line]    .charArray = &(text)[i + 1];
           
        // fprintf(stderr, "%s\n", ((arrayOfLines)[line]).charArray);           
           fprintf(stderr, "length = %lu\n", arrayOfLines[line - 1].length);
           
           line++;
        }
    }

    arrayOfLines[line - 1].length = &text[i] - arrayOfLines[line - 1].charArray;
   
    fprintf(stderr, "line number is %lu\n", line);
    
    return noErrors;
}

int readFileToLinesStruct(FILE* openedFile, InputFile* inputFile)
{
    ASSERT(openedFile != nullptr);
    
    Status err = noErrors;
    if (!err) err = (Status) readFile(openedFile, &(inputFile->text));
    if (!err) err = (Status) textToStr(inputFile->text, &(inputFile->numberOfLines));
    if (!err) err = (Status) splitIntoLines(inputFile);
    
    return err;
}

Status printArrayInFile(FILE* fileToPrint, InputFile* inputFile)
{
    if (!fileToPrint)
        return printError;
    // fseek(fileToPrint, 0l, SEEK_SET);

    for (size_t i = 0; i < inputFile->numberOfLines; ++i)
        fprintf(fileToPrint, "%s\n", ((inputFile->arrayOfLines)[i]).charArray);

    return noErrors;
}

Status printOrig(FILE* fileToPrint, char* buf)
{
    size_t i = 0;
    for (;buf[i] != '\n'; i++) 
    {
        if (buf[i] == '\0') 
        {
            buf[i] = '\n';
        }
    }

    buf[i] = '\0';
    fprintf(fileToPrint, "%s", buf);
    return noErrors;
}

