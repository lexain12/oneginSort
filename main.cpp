#include <stdio.h>
#include <assert.h>

#include "functions.h"

int main() 
{
    const char *line2 = "  Lords, ladies, Officers, Soldiers, Sailors, Messengers, Attendants.";
    const char *line1 = "Ghost of Hamlet's Father.";

    printf("%d\n", isBigger(line1, line2));

    char** arrayOfLines = nullptr;

    int numberOfLines = readFileToArray("HamletOrig.txt", &arrayOfLines);

    assert(arrayOfLines != nullptr);

    sortOnegin(arrayOfLines, numberOfLines);

    fprintf(stderr, "Ok\n");
    printArrayInFile("HamletOutput.txt", (const char***) &arrayOfLines, numberOfLines);

    return 0;
}


