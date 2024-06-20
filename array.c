#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



int dump_array(int* array, int size)
{
    int i;
    for(i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\r\n");
}

int* bubble_sort_array(int* array, int size)
{

    int pos;
    int tmp;
    int i, j;

    if(size <= 1) {
        return array;
    }

    for(i = 0; i < size ; i++) {
        for(j = 0; j < size - 1 - i; j++) {
            if(array[j] > array[j + 1]) {
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }

    return array;
}

int* reverse_array(int* array, int size)
{
    int i;
    int tmp;
    for(i = 0; i < size / 2; i++) {
        tmp = array[i];
        array[i] = array[size-i-1];
        array[size-i-1] = tmp;
    }
    return array;
}

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

int* merge_arrays(int* arr0, int size0, int* arr1, int size1)
{
    int pos0 = 0, pos1 = 0, pos = 0;
    if(!size0) {
        return arr1;
    }

    if(!size1) {
        return arr0;
    }

    int* result = malloc(sizeof(int) * (size0 + size1));
    while( (pos0 < size0) && (pos1 < size1)) {
        if(arr0[pos0] < arr1[pos1]) {
            result[pos] = arr0[pos0];
            pos0++;
            pos++;
        } else if (arr0[pos0] > arr1[pos1]) {
            result[pos] = arr1[pos1];
            pos1++;
            pos++;
        } else {
            result[pos] = arr0[pos0];
            pos0++;
            pos++;
            result[pos] = arr0[pos1];
            pos1++;
            pos++;
        }
    }
    while(pos0 < size0) {
        result[pos] = arr1[pos0];
        pos++;
        pos0++;
    }
    while(pos1 < size1) {
        result[pos] = arr1[pos1];
        pos++;
        pos1++;
    }
    return result;
}



int main()
{
    int size = 6;
    int* array_0 = create_array(size, 3, 4);
    int* array_1 = create_array(size, 5, 2);

    printf("[Info] merge array \r\n");
    dump_array(array_0, size);
    dump_array(array_1, size);

    int* merged = merge_arrays(array_0, size, array_1, size);
    dump_array(merged, size + size);


    printf("[Info] reverse array \r\n");
    int* array_2 = create_array(size, 1, 1);
    dump_array(array_2, size);
    array_2 = reverse_array(array_2, size);
    dump_array(array_2, size);


    printf("[Info] sort array \r\n");
    size = 10;
    int* array_3 = gen_random_array(size);
    dump_array(array_3, size);
    array_3 = bubble_sort_array(array_3, size);
    dump_array(array_3, size);

    free(array_0);
    free(array_1);
    if(!size)
        free(merged);
    free(array_2);
}