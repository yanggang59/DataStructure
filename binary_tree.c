#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} Node;

static void visit(Node* node)
{
    if(node) {
        printf("%d ", node->data);
        fflush(stdout);
    }
}

Node* insert(Node* node, int data) {
    if (node == NULL) {
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = data;
        temp->left = temp->right = NULL;
        return temp;
    }
 
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
 
    return node;
}
 
void preorder(Node* node) {
    if (node == NULL)
        return;
 
    visit(node);
    preorder(node->left);
    preorder(node->right);
}
 
void inorder(Node* node) {
    if (node == NULL)
        return;
 
    inorder(node->left);
    visit(node);
    inorder(node->right);
}
 
void postorder(Node* node) {
    if (node == NULL)
        return;
 
    postorder(node->left);
    postorder(node->right);
    visit(node);
}
 
Node* search(Node* node, int data) {
    if (node == NULL)
        return NULL;
 
    if (node->data == data)
        return node;
 
    Node* temp = search(node->left, data);
    if (temp != NULL)
        return temp;
 
    return search(node->right, data);
}
 
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}
 
Node* deleteNode(Node* root, int data) {
    // step 1: Find the node
    if (root == NULL)
        return root;
 
    // If the node is found, delete it
    if (data == root->data) {
        // node with only one child or no child
        if (root->left == NULL)
            return root->right;
        else if (root->right == NULL)
            return root->left;
 
        // node with two children: Get the inorder successor (smallest in the right subtree)
        Node* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->data = temp->data;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    } else if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else {
        root->right = deleteNode(root->right, data);
    }
 
    return root;
}

#define MAX_STACK_SIZE 1024

typedef struct stack {
    Node nodes[MAX_STACK_SIZE];
    int top;
} Stack;


void InitStack(Stack* S)
{
	S->top = -1;
}
 

bool IsEmpty(Stack* S)
{
	if (S->top == -1)
		return true;
	else
		return false;
}
 
bool Push(Stack* S, Node* x)
{
	if (S->top == MAX_STACK_SIZE - 1)
		return false;
	S->nodes[++(S->top)] = *x;
	return true;
}
 
bool Pop(Stack* S, Node* x)
{
	if (S->top == -1)
		return false;
	*x = S->nodes[S->top];
    S->nodes[S->top].data = 0;
    S->top--;
	return true;
}

void preorder_non_recursive(Node* node) {
    if (node == NULL)
        return;
    Stack S;
    InitStack(&S);
    Node* p_tmp = node, tmp;
    while(p_tmp || (!IsEmpty(&S))) {
        if(p_tmp) {
            visit(p_tmp);
            Push(&S, p_tmp);
            p_tmp = p_tmp->left;
        } else {
            Pop(&S, &tmp);
            p_tmp = tmp.right;
        }
    }
}

void inorder_non_recursive(Node* node)
{
    if (node == NULL)
        return;
    Stack S;
    InitStack(&S);
    Node* p_tmp = node, tmp;
    while(p_tmp || (!IsEmpty(&S))) {
        if(p_tmp) {
            Push(&S, p_tmp);
            p_tmp = p_tmp->left;
        } else {
            Pop(&S, &tmp);
            visit(&tmp);
            p_tmp = tmp.right;
        }
    }
}

void postorder_non_recursive(Node* node) {
    if (node == NULL)
        return;
    Stack S;
    InitStack(&S);
    Node* p_tmp = node, tmp;
    Node* test;
    while(p_tmp || (!IsEmpty(&S))) {
        if(p_tmp) {
            Push(&S, p_tmp);
            p_tmp = p_tmp->left;
        } else {
            Pop(&S, &tmp);
            if(tmp.right && (test != &tmp)) {
                Push(&S, &tmp);
                test = &tmp;
            } else {
                visit(&tmp);
            }
            p_tmp = tmp.right;
        }
    }
}

int main() 
{
    Node* root = NULL;
 
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 90);
    root = insert(root, 10);
    root = insert(root, 80);
    root = insert(root, 120);
    root = insert(root, 100);
    root = insert(root, 110);
 
    printf("Preorder traversal of the created binary tree is: \n");
    preorder(root);
 
    printf("\r\nInorder traversal of the created binary tree is: \n");
    inorder(root);

    printf("\r\nPostorder traversal of the created binary tree is: \n");
    postorder(root);

    printf("\r\n******************************************************* \r\n");

    printf("Nonrecursive Preorder traversal of the created binary tree is \n");
    preorder_non_recursive(root);

    printf("\r\nNonrecursive Inorder traversal of the created binary tree is \n");
    inorder_non_recursive(root);

    printf("\r\nNonrecursive postorder traversal of the created binary tree is \n");
    postorder_non_recursive(root);
 
    printf("\r\n");
}