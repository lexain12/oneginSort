#define ASSERT(condition) if(!(condition))          \
{                                                    \
    printf("Error in condition:%s line:%d\n", #condition, __LINE__); \
}

struct Line
{
    size_t length   = 0;
    char* charArray = nullptr;
};

struct InputFile   
{
    char*  fileName      = nullptr;
    size_t numberOfLines = 0;
    Line*  arrayOfLines  = nullptr;
    char*  text          = nullptr;
};

int isBigger(const char* line1, const char* line2);
  
int countLines(FILE *intputFile);

void sortOnegin(InputFile* inputFile);

void swapLines(char* line1, char* line2);

void readLines(char **arrayOfLines, FILE *inputFile, size_t numberOfLines);

void printArrayInFile(const char* outputFile,InputFile* inputFile);

void readFileToArray(InputFile* inputFile);

void readFile(InputFile *inputFile);

void splitIntoLines(InputFile *inputFile);

void addArrayInFile(const char* outputFile,InputFile* inputFile);

