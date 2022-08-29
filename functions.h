#define ASSERT(condition) if(!(condition))          \
{                                                    \
    printf("Error in condition:%s line:%d\n", #condition, __LINE__); \
}

struct InputFile   
{
    char*  fileName      = nullptr;
    size_t numberOfLines = 0;
    char** arrayOfLines  = nullptr;
};

bool isBigger(const char* line1, const char* line2);

int countLines(FILE *intputFile);

void sortOnegin(InputFile* inputFile);

void swapLines(char* line1, char* line2);

void readLines(char **arrayOfLines, FILE *inputFile, size_t numberOfLines);

void printArrayInFile(const char* outputFile,InputFile* inputFile);

void readFileToArray(InputFile* inputFile);

