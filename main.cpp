#include <stdio.h>
#include <assert.h>

#include "functions.h"

int main() 
{
    const char *line2 = "  Lords, ladies, Officers, Soldiers, Sailors, Messengers, Attendants.";
    const char *line1 = "Ghost of Hamlet's Father.";

    printf("%d\n", isBigger(line1, line2));

    char** arrayOfLines = nullptr;

    int numberOfLines = readFileToArray("HamletTest.txt", &arrayOfLines);

    assert(arrayOfLines != nullptr);

    sortOnegin(arrayOfLines, numberOfLines);

    for (int i = 0; i < numberOfLines; ++i)
    {
        printf("%s", arrayOfLines[i]);
    }

}


