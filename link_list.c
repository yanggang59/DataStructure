#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
 };

static struct ListNode* create_node(int val)
{
    struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
    tmp->val = val;
    tmp->next = NULL;
    return tmp;
}

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode* result = NULL, *tail = NULL, *cur_l1 = NULL, *cur_l2 = NULL, *tmp = NULL;
    if(!list1)
        return list2;
    if(!list2)
        return list1;
    cur_l1 = list1;
    cur_l2 = list2;
    while(cur_l1 && cur_l2) {
        if(cur_l1->val < cur_l2->val) {
            tmp = create_node(cur_l1->val);
            if(!result) {
                result = tail = tmp;
            } else {
                tail->next = tmp;
                tail = tmp;
            }
            cur_l1 = cur_l1->next;
        } else if (cur_l1->val > cur_l2->val) {
            tmp = create_node(cur_l2->val);
            if(!result) {
                result = tail = tmp;
            } else {
                tail->next = tmp;
                tail = tmp;
            }
            cur_l2 = cur_l2->next;
        } else {
            tmp = create_node(cur_l1->val);
            tmp->next = create_node(cur_l1->val);
            tmp->val = cur_l1->val;
            tmp->next->val = cur_l2->val;
            if(!result) {
                result = tmp;
                tail = tmp->next;
            } else {
                tail->next = tmp;
                tail = tmp->next;
            }
            cur_l1 = cur_l1->next;
            cur_l2 = cur_l2->next;
        }
    }

    while(cur_l1) {
        tail->next = cur_l1;
        cur_l1 = cur_l1->next;
    }

    while(cur_l2) {
        tail->next = cur_l2;
        cur_l2 = cur_l2->next;
    }

    return result;
}

static void dump_link_list(struct ListNode* list)
{
    while(list) {
        printf("%d ", list->val);
        list = list->next;
    }
    printf("\r\n");
}

static struct ListNode* create_link_list(int* data, int size)
{
    int i;
    struct ListNode* head = NULL, *tail = NULL;
    for(i = 0; i < size; i++) {
        struct ListNode* tmp = create_node(data[i]);
        if (!head) {
            head = tail = tmp;
        } else {
            tail->next = tmp;
            tail = tmp;
        }
    }
    return head;
}

int main()
{
    int array_1[] = {1, 2 ,4};
    int array_2[] = {1, 3, 4};

    struct ListNode* list1 = create_link_list(array_1, sizeof(array_1)/sizeof(int));
    struct ListNode* list2 = create_link_list(array_2, sizeof(array_2)/sizeof(int));

    dump_link_list(list1);
    dump_link_list(list2);

    struct ListNode* result = mergeTwoLists(list1, list2);
    dump_link_list(result);
    
}