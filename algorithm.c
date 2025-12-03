#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "array.h"
#include "linked_list.h"

static void bubble_sort_array(int *array, int size)
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

static int quick_select(int *array, int left, int right, int target_idx)
{
    int idx = partition(array, left, right);
    if (idx == target_idx) return array[idx];
    else if (idx < target_idx) return quick_select(array, idx + 1, right, target_idx);
    else return quick_select(array, left, idx - 1, target_idx);
}

int find_k_th_largest(int *array, int size, int k)
{
    if((size < 1) || (k > size)) return -1;
    return quick_select(array, 0, size - 1, size - k);
}

/**
* TOPK Problem
*/
int test_topk()
{
    int size = 20;
    int *array;
    int topk = 0;
    int k = 4;

    printf("***************** test topk start *****************\r\n");

    if ( k > size) {
        printf("[Error] Invalid k : %d\r\n", k);
        return -1;
    }
    
    array = gen_random_array(size);
    dump_array(array, size);

    topk = find_k_th_largest(array, size, k);

    printf("Top %d largest = %d \r\n", 4, topk);

    bubble_sort_array(array, size);
    dump_array(array, size);

    free(array);
    printf("***************** test topk end *****************\r\n\n\n");

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

static int brutal_force_trap(int *height, int size)
{
    int i, j;
    int water = 0;
    int left_max, right_max;

    for(i = 1; i < size - 1; i++) {
        left_max = right_max = 0;
        
        // find the highest bar to the left, not including height[i]
        for(j = 0; j < i; j++)
            left_max = max(height[j], left_max);

        // find the highest bar to the right, not including height[i]
        for(j = i + 1 ; j < size; j++)
            right_max = max(height[j], right_max);

        // if height[i] is the highest, then this bar cannot hold water, continue
        if ((left_max < height[i]) || (right_max < height[i])) {
            continue;
        }

        water += (min(left_max, right_max) - height[i]);
    }
    return water;
}

static int brutal_force_trap_optimize_1(int *height, int n)
{
    int i;
    int water = 0;
    int l_max[n];
    int r_max[n];

    l_max[0] = height[0];
    r_max[n - 1] = height[n - 1];

    // find the left highest bar height
    for (i = 1; i < n; i++)
        l_max[i] = max(l_max[i - 1], height[i]);

    // find the right highest bar height
    for (i = n - 2; i >= 0; i--)
        r_max[i] = max(r_max[i + 1], height[i]);

    for (i = 1; i < n - 1; i++)
        water += (min(l_max[i - 1], r_max[i + 1]) > height[i]) ? (min(l_max[i - 1], r_max[i + 1]) - height[i]) : 0;
    return water;
}

static int brutal_force_trap_optimize_2(int *height, int n)
{
    int i;
    int left_max, right_max;
    int left =0, right = n - 1;
    int water = 0;

    left_max = height[0];
    right_max = height[n - 1];

    while(left <= right) {
        left_max = max(left_max, height[left]);
        right_max = max(right_max, height[right]);

        if (left_max < right_max) {
            water += left_max - height[left];
            left++;
        } else {
            water += right_max - height[right];
            right--;
        }
    }

    return water;
}

int test_trap()
{
    int size = 20;
    int *array;
    int water = 0;

    printf("***************** test trap start *****************\r\n");
    array = gen_random_array(size);
    dump_array(array, size);

    if (size < 3) {
        printf("Not enough bars to trap water\r\n");
        free(array);
        return -1;
    }
    water = brutal_force_trap(array, size);
    printf("brutal force trapped water = %d \r\n", water);

    water = brutal_force_trap_optimize_1(array, size);
    printf("brutal force optimize 1 trapped water = %d \r\n", water);

    water = brutal_force_trap_optimize_2(array, size);
    printf("brutal force optimize 2 trapped water = %d \r\n", water);

    free(array);
    printf("***************** test trap end  *****************\r\n\n\n");

    return 0;
}

/**
* slinding window
*/
static int find_longest_substring_length(const char *str)
{
    unsigned long length, max_sub_str_len = 0;
    int chars[256] = {0};
    int left = 0, right = 0;

    length = strlen(str);
    while( right < length) {
        if (chars[str[right]] == 0) {
            chars[str[right]] = 1;
            right++;
            max_sub_str_len = (right - left) > max_sub_str_len ? (right - left) : max_sub_str_len;
        } else {
            chars[str[left]] = 0;
            left++;
        }
    }
    return max_sub_str_len;
}

int test_find_longest_substring()
{
    int length;
    const char *test_string = "aabcbcdabcdabcdeaaaabcdefgabcccdfs";

    printf("*********** test longest substring length start ************\r\n");

    length = find_longest_substring_length(test_string);

    printf("longest substring length = %d\r\n", length);

    printf("*********** test longest substring length done ************\r\n\n\n");

    return 0;
}

static int find_longest_increasing_subsequence(int *array, int size)
{
    return 0;
}

int test_longest_increasing_subsequence()
{
    int size = 20;
    int *array;
    int length = 0;

    printf("********* test longest_increasing_subsequence start **********\r\n");
    array = gen_random_array(size);
    dump_array(array, size);

    length = find_longest_increasing_subsequence(array, size);
    printf("longest increasing subsequence length = %d\r\n", length);

    printf("********* test longest_increasing_subsequence start **********\r\n\n\n");
    return 0;
}

static struct linked_list *handle_odd_even_list(struct linked_list *head)
{
    struct linked_list *odd, *even, *even_head;
    /**
    *  if (1) list is null
    *     (2) list has only one element
    *  just return list
    */ 

    if (!head || !head->next) return head;

    odd = head;
    even_head = even = head->next;
    while(head) {
        head = head->next;
    }
    return head;
}

static int test_odd_even_list()
{
    struct linked_list *list = NULL;
    int *array;
    int size = 21;
    
    array = create_array(size, 1, 1);
    list = create_linked_list(array, size);
    dump_linked_list(list);

    list = handle_odd_even_list(list);
    dump_linked_list(list);

    return 0;
}

int main()
{
    int ret;

    ret = test_topk();
    if (ret) {
        printf("[Error] test topk failed\r\n");
    }

    ret = test_trap();
    if (ret) {
        printf("[Error] test trap failed\r\n");
    }

    ret = test_find_longest_substring();
    if (ret) {
        printf("[Error] test find longest substring failed\r\n");
    }

    ret = test_longest_increasing_subsequence();
    if (ret) {
        printf("[Error] test find longest increasing subsequence failed\r\n");
    }

    ret = test_odd_even_list();
    if (ret) {
        printf("[Error] test_odd_even_list failed\r\n");
    }

    return ret;
}