#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STACK_SIZE   1024

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
} Node;

typedef struct stack{
    int top;
    Node* nodes[MAX_STACK_SIZE];
} Stack;

void init_stack(Stack* stack)
{
    stack->top = -1;
}

bool is_stack_full(Stack* stack)
{
    return (stack->top == MAX_STACK_SIZE - 1);
}

bool is_stack_empty(Stack* stack)
{
    return (stack->top == -1);
}

bool push(Stack* stack, Node* node)
{
    if(is_stack_full(stack)) 
        return false;
    stack->nodes[++stack->top] = node;
    return true;
}

bool pop(Stack* stack, Node** node)
{
    if(is_stack_empty(stack)) 
        return false;
    *node = stack->nodes[stack->top--];
    return true;
}

Node* top(Stack* stack)
{
    if(!is_stack_empty) return stack->nodes[stack->top];
    return NULL;
}


typedef struct queue_node{
    Node* node;
    struct queue_node* next;
}QueueNode;

typedef struct queue {
    QueueNode* head;
    QueueNode* tail;
} Queue;


void init_queue(Queue* queue)
{
    if(!queue) return;
    queue->head = queue->tail = NULL;
}

void enqueue(Queue* queue, Node* node)
{
    if(!queue || !node) return;
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    new_node->node = node;
    if(!queue->head) {
        queue->head = queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
}

Node* dequeue(Queue* queue)
{
    if(!queue) return NULL;
    if(!queue->head) return NULL;
    Node* node_tmp = NULL;
    QueueNode* q_tmp = queue->head;
    queue->head = q_tmp->next;
    node_tmp  = q_tmp->node;
    free(q_tmp);
    return node_tmp;
}

Node* create_node(int data)
{
    Node* node = malloc(sizeof(Node));
    if(!node) return NULL;
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

void insert_node(Node* root, Node* left, Node* right)
{
    if(!root) return;
    root->left = left;
    root->right = right;
}

void visit(Node* node)
{
    if(!node) {
        return;
    }
    printf("%d ", node->data);
    fflush(stdout);
}
 
void preorder_recursive(Node* root)
{
    if(!root) return;
    visit(root);
    preorder_recursive(root->left);
    preorder_recursive(root->right);
}

void inorder_recursive(Node* root)
{
    if(!root) return;
    inorder_recursive(root->left);
    visit(root);
    inorder_recursive(root->right);
}

void postorder_recursive(Node* root)
{
    if(!root) return;
    postorder_recursive(root->left);
    postorder_recursive(root->right);
    visit(root);
}


void preorder_nonrecursive(Node* root)
{
    if(!root) return;
    Stack stack;
    init_stack(&stack);
    Node* p_tmp = root;
    while(p_tmp || (!is_stack_empty(&stack))) {
        if(p_tmp) {
            visit(p_tmp);
            if(!push(&stack, p_tmp)) {
                printf("[Error] stack full \r\n");
                return;
            }
            p_tmp = p_tmp->left;
        } else {
            if(!pop(&stack, &p_tmp)) {
                printf("[Error] stack empty \r\n");
                return;
            }
            p_tmp = p_tmp->right;
        }
    }
    printf("\r\n");
    return;
}

void inorder_nonrecursive(Node* root)
{
    if(!root) return;
    Stack stack;
    init_stack(&stack);
    Node* p_tmp = root;
    while(p_tmp || (!is_stack_empty(&stack))) {
        if(p_tmp) {
            if(!push(&stack, p_tmp)) {
                printf("[Error] stack full \r\n");
                return;
            }
            p_tmp = p_tmp->left;
        } else {
            if(!pop(&stack, &p_tmp)) {
                printf("[Error] stack empty \r\n");
                return;
            }
            visit(p_tmp);
            p_tmp = p_tmp->right;
        }
    }

    printf("\r\n");
}

void postorder_nonrecursive(Node* root)
{
    if(!root) return;
    Stack stack;
    init_stack(&stack);
    Node* p_tmp = root;
    Node* popped_once = NULL;
    while(p_tmp || (!is_stack_empty(&stack))) {
        if(p_tmp) {
            push(&stack, p_tmp);
            p_tmp = p_tmp->left;
        } else {
            pop(&stack, &p_tmp);
            // if current node has right child and its right child has never been accessed
            // then we need to push this node into stack, and put current to its right child
            if(p_tmp->right && (popped_once != p_tmp->right)) {
                push(&stack, p_tmp);
                p_tmp = p_tmp->right;
            } else {
                visit(p_tmp);
                popped_once = p_tmp;
                p_tmp = NULL;
            }
        }
    }

    printf("\r\n");
}

void level_order_nonrecursive(Node* root)
{
    if(!root) return;
    Queue queue;
    init_queue(&queue);

    enqueue(&queue, root);
    while (queue.head != NULL) {
        Node *node = dequeue(&queue);
        visit(node);
 
        if (node->left) {
            enqueue(&queue, node->left);
        }
 
        if (node->right) {
            enqueue(&queue, node->right);
        }
    }

    printf("\r\n");
}

int main()
{
    Node* root = create_node(0);
    Node* node1 = create_node(1);
    Node* node2 = create_node(2);
    Node* node3 = create_node(3);
    Node* node4 = create_node(4);
    Node* node5 = create_node(5);
    Node* node6 = create_node(6);
    Node* node7 = create_node(7);
    Node* node8 = create_node(8);
    Node* node9 = create_node(9);
    Node* node10 = create_node(10);
    Node* node11 = create_node(11);
    Node* node12 = create_node(12);
    Node* node13 = create_node(13);
    Node* node14 = create_node(14);

    insert_node(root, node1, node2);
    insert_node(node1, node3, node4);
    insert_node(node2, node5, node6);
    insert_node(node3, NULL, node7);
    insert_node(node4, node8, NULL);
    insert_node(node7, node9, node10);
    insert_node(node10, node11, node12);
    insert_node(node12, NULL, node13);
    insert_node(node13, NULL, node14);

    printf("********************** Recursive Traverse **********************\r\n");
    printf("preorder recursive\r\n");
    preorder_recursive(root);
    printf("\r\n");
    printf("inorder recursive\r\n");
    inorder_recursive(root);
    printf("\r\n");
    printf("postorder recursive\r\n");
    postorder_recursive(root);
    printf("\r\n");

    printf("********************** Non Recursive Traverse **********************\r\n");
    printf("preorder nonrecursive\r\n");
    preorder_nonrecursive(root);

    printf("inorder nonrecursive\r\n");
    inorder_nonrecursive(root);

    printf("postorder nonrecursive\r\n");
    postorder_nonrecursive(root);


    printf("levelorder nonrecursive\r\n");
    level_order_nonrecursive(root);
}   