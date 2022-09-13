#include <stdio.h> 
#include <assert.h>
#include <time.h>

int cmpint(const void* arg1, const void* arg2);

void swap(size_t size, void* pointer1, void* pointer2); // void *first, void *second, size_t size;

void Qsort(void* array, size_t n, size_t size, int (*cmp)(const void*, const void*));
