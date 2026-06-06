#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[50];
    int birthYear;
} Student;

typedef struct Node {
    Student data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(Student s) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = s;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, Student s) {
    if (root == NULL)
        return createNode(s);

    if (s.birthYear < root->data.birthYear)
        root->left = insert(root->left, s);
    else if (s.birthYear > root->data.birthYear)
        root->right = insert(root->right, s);
    else
        printf("Nam sinh %d da ton tai, khong them.\n", s.birthYear);

    return root;
}

Node* search(Node* root, int year) {
    if (root == NULL || root->data.birthYear == year)
        return root;

    if (year < root->data.birthYear)
        return search(root->left, year);
    else
        return search(root->right, year);
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%s - %d\n", root->data.name, root->data.birthYear);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;

    Student ds[] = {
        {"An", 2004},
        {"Binh", 2003},
        {"Chi", 2005},
        {"Dung", 2002},
        {"Ha", 2006}
    };

    int n = sizeof(ds) / sizeof(ds[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, ds[i]);
    }

    printf("Cay BST sau khi tao:\n");
    inorder(root);

    Student newStudent = {"Minh", 2001};
    root = insert(root, newStudent);

    printf("\nCay BST sau khi them nut:\n");
    inorder(root);

    int year;
    printf("\nNhap nam sinh can tim: ");
    scanf("%d", &year);

    Node* result = search(root, year);

    if (result != NULL) {
        printf("Tim thay: %s - %d\n",
               result->data.name,
               result->data.birthYear);
    } else {
        printf("Khong tim thay sinh vien co nam sinh %d\n", year);
    }

    return 0;
}