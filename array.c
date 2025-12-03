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

void bubble_sort_array(int* array, int size)
{

    int pos;
    int tmp;
    int i, j;

    if(size <= 1) {
        return;
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
}

static int partition(int* array, int left, int right)
{
    int pivot = array[left];
    while (right > left) {
        while ((right > left) && (array[right] >= pivot)) right--;
            array[left] = array[right];
        while ((right > left) && (array[left] <= pivot)) left++;
            array[right] = array[left];
    }
    array[left] = pivot;
    return left;
}

static void __quick_sort(int* array, int left, int right)
{
    int pos;
    if (right > left) {
        pos = partition(array, left, right);
        __quick_sort(array, left, pos - 1);
        __quick_sort(array, pos + 1, right);
    }
    return;
}

void quick_sort(int* array, int size)
{
    if (size > 1) {
        __quick_sort(array, 0, size - 1);
    }
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

int* merge_sorted_arrays(int* arr0, int size0, int* arr1, int size1)
{
    int pos0 = 0, pos1 = 0, pos = 0;
    int* result;

    if (!size0) {
        return arr1;
    }

    if (!size1) {
        return arr0;
    }

    result = malloc(sizeof(int) * (size0 + size1));

    while ( (pos0 < size0) && (pos1 < size1)) {
        if (arr0[pos0] < arr1[pos1])
            result[pos++] = arr0[pos0++];
        else if (arr0[pos0] > arr1[pos1])
            result[pos++] = arr1[pos1++];
        else {
            result[pos++] = arr0[pos0++];
            result[pos++] = arr0[pos1++];
        }
    }
    while(pos0 < size0) {
        result[pos++] = arr1[pos0++];
    }
    while(pos1 < size1) {
        result[pos++] = arr1[pos1++];
    }
    return result;
}



int main()
{
    int size = 20;
    int* array_0, *array_1, *array_2, *array_3, *array_4;
    int* merged;
    
    array_0 = gen_random_array(size);
    array_1 = gen_random_array(size);

    printf("[Info] array_0 : ");
    dump_array(array_0, size);
    printf("[Info] array_1 : ");
    dump_array(array_1, size);

    bubble_sort_array(array_0, size);
    bubble_sort_array(array_1, size);

    printf("[Info] array_0 after sorting : ");
    dump_array(array_0, size);
    printf("[Info] array_1 after sorting : ");
    dump_array(array_1, size);

    merged = merge_sorted_arrays(array_0, size, array_1, size);
    printf("[Info] merged array_0 and array_1 : ");
    dump_array(merged, size + size);


    printf("[Info] array_2 : ");
    array_2 = create_array(size, 1, 1);
    dump_array(array_2, size);
    array_2 = reverse_array(array_2, size);
    printf("[Info] reverse array : ");
    dump_array(array_2, size);

    size = 10;
    array_3 = gen_random_array(size);
    printf("[Info] array_3 : ");
    dump_array(array_3, size);
    bubble_sort_array(array_3, size);
    printf("[Info] bubble sort array_3 : ");
    dump_array(array_3, size);

    size = 40;
    array_4 = gen_random_array(size);
    printf("[Info] array_4 : ");
    dump_array(array_4, size);
    quick_sort(array_4, size);
    printf("[Info] quick sort array_4 : ");
    dump_array(array_4, size);


    free(array_0);
    free(array_1);
    free(array_2);
    free(array_3);
    free(array_4);
    free(merged);
}