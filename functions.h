struct InputFile 
{
    char*  fileName      = nullptr;
    size_t numberOfLines = 0;
    char** arrayOfLines  = nullptr;
};

bool isBigger(const char* line1, const char* line2);

int countLines(FILE *intputFile);

void sortOnegin(char** arrayOfLines, int numberOfLines);

void swapLines(char* line1, char* line2);

void readLines(char **arrayOfLines, FILE *inputFile, int numberOfLines);

void printArrayInFile(const char* outputFile,InputFile* inputFile);

void readFileToArray(InputFile* inputFile);

