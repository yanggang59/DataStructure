#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

struct linked_list* create_linked_list_node(int val)
{
    struct linked_list* tmp = (struct linked_list*)malloc(sizeof(struct linked_list));
    tmp->val = val;
    tmp->next = NULL;
    return tmp;
}

void dump_linked_list(struct linked_list* list)
{
    while(list) {
        printf("%d ", list->val);
        list = list->next;
    }
    printf("\r\n");
}

struct linked_list* create_linked_list(int* data, int size)
{
    int i;
    struct linked_list* head = NULL, *tail = NULL;
    for(i = 0; i < size; i++) {
        struct linked_list* tmp = create_linked_list_node(data[i]);
        if (!head) {
            head = tail = tmp;
        } else {
            tail->next = tmp;
            tail = tmp;
        }
    }
    return head;
}

void destroy_linked_list(struct linked_list* head)
{
    struct linked_list *tmp = NULL;
    while(head) {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}