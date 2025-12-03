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

int* reverse_array(int* array, int size)
{
    int i;
    int tmp;
    for(i = 0; i < size / 2; i++) {
        tmp = array[i];
        array[i] = array[size - i - 1];
        array[size - i - 1] = tmp;
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

static int partition(int *array, int left, int right)
{
    int pivot = array[left];
    while(right > left) {
        while ((right > left) && array[right] > pivot) right--;
        array[left] = array[right];
        while ((right > left) && array[left] <= pivot) left++;
        array[right] = array[left]; 
    }
    array[left] = pivot;
    return left;
}

static int qselect(int* array, int left, int right, int target_idx)
{
    int idx = partition(array, left, right);
    if (idx == target_idx) return array[idx];
    else if (idx < target_idx) return qselect(array, idx + 1, right, target_idx);
    else return qselect(array, left, idx - 1, target_idx);
}


int find_k_th_largest(int *array, int size, int k)
{
    if((size < 1) || (k > size)) return -1;
    return qselect(array, 0, size - 1, size - k);
}


/**
* TOPK Problem
*/
int test_find_k_th_largest()
{
    int size = 20;
    int* array;
    int topk = 0;
    int k = 4;
    
    array = gen_random_array(size);
    dump_array(array, size);

    topk = find_k_th_largest(array, size, k);

    printf("Top %d largest = %d \r\n", 4, topk);

    bubble_sort_array(array, size);
    dump_array(array, size);

    free(array);

    return 0;
}

static int max(int a, int b)
{
    return (a > b) ? a : b;
}

static int min(int a, int b)
{
    return (a < b) ? a : b;
}

static int brutal_force_trap(int* height, int size)
{
    int i, j;
    int water = 0;

    for(i = 1; i < size - 1; i++) {
        int left_max = 0, right_max = 0;

        for(j = 0; j < i; j++)
            left_max = max(height[j], left_max);

        for(j = i + 1; j < size; j++)
            right_max = max(height[j], right_max);
        
        if (left_max == height[i] && right_max == height[i]) {
            continue;
        }
        
        water += min(left_max, right_max) - height[i];
    }
    return water;
}

int test_trap()
{
    int size = 20;
    int* array;
    int water = 0;

    array = gen_random_array(size);
    dump_array(array, size);

    if (size < 3) {
        printf("Not enough bars to trap water\r\n");
        free(array);
        return -1;
    }
    water = brutal_force_trap(array, size);
    printf("Trapped water = %d \r\n", water);

    free(array);

    return 0;
}


int main()
{
    int ret;

    ret = test_find_k_th_largest();

    ret = test_trap();

    return ret;
}