#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void initArray(int a[]) {
    for (int i = 0; i < MAX; i++) {
        a[i] = -1;
    }
}

void createFullTreeArray(int a[], int n) {
    for (int i = 1; i <= n; i++) {
        a[i] = i;
    }
}

void createLeftSkewedArray(int a[], int n) {
    int index = 1;

    for (int i = 1; i <= n; i++) {
        a[index] = i;
        index = index * 2;
    }
}

void createRightSkewedArray(int a[], int n) {
    int index = 1;

    for (int i = 1; i <= n; i++) {
        a[index] = i;
        index = index * 2 + 1;
    }
}

void createZigzagArray(int a[], int n) {
    int index = 1;

    for (int i = 1; i <= n; i++) {
        a[index] = i;

        if (i % 2 == 1)
            index = index * 2;
        else
            index = index * 2 + 1;
    }
}

void printArrayTree(int a[]) {
    printf("Vi tri\tGia tri\n");

    for (int i = 1; i < MAX; i++) {
        if (a[i] != -1) {
            printf("%d\t%d\n", i, a[i]);
        }
    }
}

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int x) {
    Node* p = (Node*)malloc(sizeof(Node));

    p->data = x;
    p->left = NULL;
    p->right = NULL;

    return p;
}

Node* createFullTreeLinked(int i, int n) {
    if (i > n)
        return NULL;

    Node* root = createNode(i);

    root->left = createFullTreeLinked(2 * i, n);
    root->right = createFullTreeLinked(2 * i + 1, n);

    return root;
}

Node* createLeftSkewedLinked(int n) {
    if (n <= 0)
        return NULL;

    Node* root = createNode(1);
    Node* current = root;

    for (int i = 2; i <= n; i++) {
        current->left = createNode(i);
        current = current->left;
    }

    return root;
}

Node* createRightSkewedLinked(int n) {
    if (n <= 0)
        return NULL;

    Node* root = createNode(1);
    Node* current = root;

    for (int i = 2; i <= n; i++) {
        current->right = createNode(i);
        current = current->right;
    }

    return root;
}

Node* createZigzagLinked(int n) {
    if (n <= 0)
        return NULL;

    Node* root = createNode(1);
    Node* current = root;

    for (int i = 2; i <= n; i++) {
        if (i % 2 == 0) {
            current->left = createNode(i);
            current = current->left;
        } else {
            current->right = createNode(i);
            current = current->right;
        }
    }

    return root;
}

void preorder(Node* root) {
    if (root == NULL)
        return;

    printf("%d ", root->data);

    preorder(root->left);
    preorder(root->right);
}

void freeTree(Node* root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}

int main() {
    int n;
    int a[MAX];
    Node* root = NULL;

    printf("Nhap so nut cua cay: ");
    scanf("%d", &n);

    printf("\nCAY DAY DU - TUAN TU\n");
    initArray(a);
    createFullTreeArray(a, n);
    printArrayTree(a);

    printf("\nCAY LECH TRAI - TUAN TU\n");
    initArray(a);
    createLeftSkewedArray(a, n);
    printArrayTree(a);

    printf("\nCAY LECH PHAI - TUAN TU\n");
    initArray(a);
    createRightSkewedArray(a, n);
    printArrayTree(a);

    printf("\nCAY ZIGZAG - TUAN TU\n");
    initArray(a);
    createZigzagArray(a, n);
    printArrayTree(a);

    printf("\nCAY DAY DU - MOC NOI\n");
    root = createFullTreeLinked(1, n);
    printf("Duyet NLR: ");
    preorder(root);
    freeTree(root);

    printf("\n\nCAY LECH TRAI - MOC NOI\n");
    root = createLeftSkewedLinked(n);
    printf("Duyet NLR: ");
    preorder(root);
    freeTree(root);

    printf("\n\nCAY LECH PHAI - MOC NOI\n");
    root = createRightSkewedLinked(n);
    printf("Duyet NLR: ");
    preorder(root);
    freeTree(root);

    printf("\n\nCAY ZIGZAG - MOC NOI\n");
    root = createZigzagLinked(n);
    printf("Duyet NLR: ");
    preorder(root);
    freeTree(root);

    return 0;
}