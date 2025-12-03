#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "array.h"

int* create_array(int size, int step, int start)
{
    int i = 0;
    int* array = malloc(size * sizeof(int));
    for(i = 0; i < size; i++) {
        array[i] = start + step * i + 1;
    }
    return array;
}

int* gen_random_array(int size)
{
    int i = 0;
    int* array = malloc(size * sizeof(int));
    for(i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }
    return array;
}

void dump_array(int* array, int size)
{
    int i;
    for(i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\r\n");
}