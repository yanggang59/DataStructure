#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"


struct linked_list* merge_sorted_list(struct linked_list* list1, struct linked_list* list2)
{
    struct linked_list *head = NULL, *tail = NULL;
    struct linked_list dummy;

    tail = &dummy;
    dummy.next = NULL;

    if(!list1)
        return list2;

    if(!list2)
        return list1;

    while(list1 && list2) {
        if(list1->val < list2->val) {
            tail = tail->next = create_linked_list_node(list1->val);
            list1 = list1->next;
        } else if (list1->val > list2->val) {
            tail = tail->next = create_linked_list_node(list2->val);
            list2 = list2->next;
        } else {
            tail = tail->next = create_linked_list_node(list1->val);
            //tail = tail->next = create_linked_list_node(list2->val);
            list1 = list1->next;
            list2 = list2->next;
        }
    }

    while(list1) {
        tail = tail->next = create_linked_list_node(list1->val);
        list1 = list1->next;
    }

    while(list2) {
        tail = tail->next = create_linked_list_node(list2->val);
        list2 = list2->next;
    }

    return dummy.next;
}

struct linked_list* reverse_list(struct linked_list* head) 
{
    struct linked_list* cur = NULL, *next = NULL, *pre = NULL;

    if(!head || (!head->next)) {
        return head;
    }

    cur = head->next;
    pre = head;

    while(cur) {
        next = cur->next;
        pre->next = NULL;
        cur->next = head;
        head = cur;
        cur = next;
    }

    return head;
}

struct linked_list* select_sort_list(struct linked_list* head) 
{
    struct linked_list* cur = NULL, *next = NULL, *tmp = NULL;
    struct linked_list* inner_pre = NULL, *inner_tail = NULL;

    if(!head || (!head->next)) {
        return head;
    }

    struct linked_list* dummy_head = (struct linked_list*)malloc(sizeof(struct linked_list));
    dummy_head->next = head;
    cur = head->next;
    inner_tail = head;
    while(cur) {
        next = cur->next;
        inner_tail->next = NULL; // break connectin
        cur->next = NULL;
        for(tmp = dummy_head->next, inner_pre = dummy_head; tmp; tmp = tmp->next, inner_pre = inner_pre->next) {
            if (tmp->val >= cur->val) { // find a value > cur->val
                cur->next = tmp;
                inner_pre->next = cur;
                break;
            } else if (tmp == inner_tail) { //no value is over cur->val
                tmp->next = cur;
                inner_tail = cur; //update inner_tail
                break;
            }
        }
        cur = next;
    }

    return dummy_head->next;

}

struct linked_list* insert_sort_list(struct linked_list* head) 
{
    //Insert Sort Algorithm
    struct linked_list* cur = NULL, *next = NULL, *tmp = NULL;
    struct linked_list* inner_pre = NULL, *inner_tail = NULL;

    if(!head || (!head->next)) {
        return head;
    }

    struct linked_list* dummy_head = (struct linked_list*)malloc(sizeof(struct linked_list));
    dummy_head->next = head;
    cur = head->next;
    inner_tail = head;
    while(cur) {
        next = cur->next;
        inner_tail->next = NULL; // break connectin
        cur->next = NULL;
        for(tmp = dummy_head->next, inner_pre = dummy_head; tmp; tmp = tmp->next, inner_pre = inner_pre->next) {
            if (tmp->val >= cur->val) { // find a value > cur->val
                cur->next = tmp;
                inner_pre->next = cur;
                break;
            } else if (tmp == inner_tail) { //no value is over cur->val
                tmp->next = cur;
                inner_tail = cur; //update inner_tail
                break;
            }
        }
        cur = next;
    }

    return dummy_head->next;

}

int main()
{
    int array_1[] = {1, 2 ,4, 5, 7, 11, 18};
    int array_2[] = {1, 3, 4};

    int array_3[] = {8,5,7,3,4,9,1};

    struct linked_list* list1 = create_linked_list(array_1, sizeof(array_1)/sizeof(int));
    struct linked_list* list2 = create_linked_list(array_2, sizeof(array_2)/sizeof(int));
    struct linked_list* list3 = create_linked_list(array_3, sizeof(array_3)/sizeof(int));

    dump_linked_list(list1);
    dump_linked_list(list2);

    struct linked_list* result = merge_sorted_list(list1, list2);
    dump_linked_list(result);

    struct linked_list* reverse_list1 = reverse_list(list1);
    dump_linked_list(reverse_list1);

    printf("original list3 \r\n");
    dump_linked_list(list3);
    list3 = insert_sort_list(list3);
    printf("list3 after sorting \r\n");
    dump_linked_list(list3);

    destroy_linked_list(list1);
    destroy_linked_list(list2);
    destroy_linked_list(list3);
    destroy_linked_list(result);
}