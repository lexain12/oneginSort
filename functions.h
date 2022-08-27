bool isBigger(const char* line1, const char* line2);

int countLines(FILE *intputFile);

void sortOnegin(char** arrayOfLines, int numberOfLines);

void swapLines(char* line1, char* line2);

void readLines(char **arrayOfLines, FILE *inputFile, int numberOfLines);

int readFileToArray(const char* fileName, char*** arrayOfLines);
