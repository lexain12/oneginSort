#include <stdio.h>

int main()
{
    int array[10] = {4, 3, 2, 7, 4, 3, 2, 2, 9, 3};

    
    for (int i = 0; i < 10; ++i)
    {
        for (int j = i; j < 10; ++j) 
        {
            if (array[i] > array[j])
            {
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    }
    for (int i = 0; i < 10; ++i)
    {
        printf("%d", array[i]);
    }
}
