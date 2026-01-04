#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

/* Yeni düðüm oluþturma */
Node* createNode(int x) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (n == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    n->data = x;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* Inorder Traversal (Left - Root - Right) */
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

/* Belleði temizleme */
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    /* Binary Tree oluþturma */
    Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(3);
    root->left->right = createNode(7);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}

