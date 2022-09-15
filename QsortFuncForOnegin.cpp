#include <stdio.h> 
#include <assert.h>
#include <time.h>
#include <cstring>
#include <ctype.h>
#include "functions.h"


int cmpint(const void* arg1, const void* arg2)
{
    assert(arg1 != NULL);
    assert(arg2 != NULL);

    if (*((int*) arg1) > *((int*) arg2))
        return 1;
    else if (*((int*)arg1) == *((int*)arg2))
        return 0;
    else 
        return -1;
}

int strcmp1(const char* arg1, const char* arg2)
{
    assert(arg1 != NULL);
    assert(arg2 != NULL);

    while (*arg1 != '\0' && *arg2 != '\0')
    {
        while (!isalpha(*arg1) && *arg1 != '\0')
            ++arg1;
        while (!isalpha(*arg2) && *arg2 != '\0')
            ++arg2;

        if (*arg1 != *arg2 && arg1 && arg2)
            return toupper(*arg1) - toupper(*arg2);
        ++arg1;
        ++arg2;
    }

    return *arg1 - *arg2;
}

int cmpstr(const void* arg1, const void* arg2)
{
    assert(arg1 != NULL);
    assert(arg2 != NULL);
    
    const char** str1 = ((const char**)arg1);
    const char** str2 = ((const char**)arg2);

    return isBigger(*str1, *str2);
}

int cmpstruct(const void* arg1, const void* arg2)
{
    assert(arg1 != NULL);
    assert(arg2 != NULL);
    
    const char* str1 = ((Line*) arg1)->charArray;
    const char* str2 = ((Line*) arg2)->charArray;

//    fprintf(stderr, "%s %s\n", str1, str2);

    return isBigger(str1, str2);
}

int cmpstructReverse(const void* arg1, const void* arg2)
{
    assert(arg1 != NULL);
    assert(arg2 != NULL);
    
    const char*  line1   = ((Line*) arg1)->charArray;
    const char*  line2   = ((Line*) arg2)->charArray;
    const size_t length1 = ((Line*) arg1)->length;
    const size_t length2 = ((Line*) arg2)->length;
    const char*  index1  = length1 + line1 - 1;
    const char*  index2  = length2 + line2 - 1;
//    fprintf(stderr, "%s %d\n", line1, sizeOfLine1);
//    fprintf(stderr, "%s %d\n", line2, sizeOfLine2);

    if (*line1 == '\0' || *line2 == '\0' || *line1 == '\n' || *line2 == '\n')
    {
        return *line2 - *line1;
    }

    assert(*index1 != '\0');
    assert(*index2 != '\0');

    while (index1 != line1 && index2 != line2) 
    {
        if (isalpha(*index1) && isalpha(*index2))
        {
            if (toupper(*index1) != toupper(*index2))
                return toupper(*index1) - toupper(*index2);

            --index1;
            --index2;
        }
        while (!isalpha(*index1) && index1 != line1) 
            --index1;

        while (!isalpha(*index2) && index2 != line2)
            --index2;
    }

    return *index1 - *index2;
}

void swap(void* first, void* second, size_t size) 
{
    assert(first  != NULL);
    assert(second != NULL);

    for (size_t index = 0; index < size; index++)
    {
        char tmp = *((char*) first + index);
        *((char*) first  + index) = *((char*) second + index);
        *((char*) second + index) = tmp;
    }
}

void Qsort(void* array, size_t n, size_t size, int (*cmp)(const void*, const void*))
{
    assert(array != NULL);

    char* base = (char*) array;

    size_t right = n - 1; 
    size_t left  = 0;

    if (left >= right || n == 0)
        return;

    swap(base + left * size, base + ((right + left) / 2) * size, size);

    size_t last = left;

    for (int i = left + 1; i <= right; i++)
    {
        if ((*cmp)(base + left*size, base + i*size) > 0)
            swap((void*) (base + (++last) * size), (void*) (base + i * size), size);
    }

    swap((void*) (base + left * size), (void*) (base + last * size), size); // base
    Qsort(base + left*size, last-left, size, cmp);
    Qsort(base + (last + 1) * size, n - 1 - last, size, cmp);
}

