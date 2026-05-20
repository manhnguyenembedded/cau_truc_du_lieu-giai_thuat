#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(char x) {
    Node* p = (Node*)malloc(sizeof(Node));

    p->data = x;
    p->left = NULL;
    p->right = NULL;

    return p;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

Node* buildExpressionTree(char postfix[]) {
    Node* stack[100];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isalnum(c)) {
            stack[++top] = createNode(c);
        }
        else if (isOperator(c)) {
            Node* right = stack[top--];
            Node* left = stack[top--];

            Node* newNode = createNode(c);

            newNode->left = left;
            newNode->right = right;

            stack[++top] = newNode;
        }
    }

    return stack[top];
}

void preorder(Node* root) {
    if (root == NULL)
        return;

    printf("%c ", root->data);

    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);

    printf("%c ", root->data);

    inorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);

    printf("%c ", root->data);
}

void freeTree(Node* root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}

int main() {
    char postfix[100] = "ab*c+d/ef*h-g^-";

    Node* root = buildExpressionTree(postfix);

    printf("Bieu thuc hau to: %s\n", postfix);

    printf("\nDuyet truoc (Prefix): ");
    preorder(root);

    printf("\n\nDuyet giua (Infix): ");
    inorder(root);

    printf("\n\nDuyet sau (Postfix): ");
    postorder(root);

    freeTree(root);

    return 0;
}