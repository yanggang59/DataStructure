#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

struct linked_list {
    int val;
    struct linked_list *next;
 };

struct linked_list* create_linked_list_node(int val);
void dump_linked_list(struct linked_list* list);
struct linked_list* create_linked_list(int* data, int size);
void destroy_linked_list(struct linked_list* head);

#endif