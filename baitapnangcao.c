#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node* taoNode(int x)
{
    struct Node *p;

    p = (struct Node*)malloc(sizeof(struct Node));

    p->data = x;
    p->next = NULL;

    return p;
}

struct Node* taoDanhSachVong(int n)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;

    for (int i = 1; i <= n; i++)
    {
        struct Node *p = taoNode(i);

        if (head == NULL)
        {
            head = tail = p;
            tail->next = head;
        }
        else
        {
            tail->next = p;
            tail = p;
            tail->next = head;
        }
    }

    return head;
}

int josephus(int n, int m)
{
    if (n <= 0)
        return -1;

    struct Node *cur = taoDanhSachVong(n);
    struct Node *prev = cur;

    while (prev->next != cur)
    {
        prev = prev->next;
    }

    printf("\nThu tu bi loai: ");

    while (cur->next != cur)
    {
        for (int i = 0; i < m; i++)
        {
            prev = cur;
            cur = cur->next;
        }

        printf("%d ", cur->data);

        prev->next = cur->next;

        free(cur);

        cur = prev->next;
    }

    printf("\nNguoi chien thang: %d\n", cur->data);

    int winner = cur->data;

    free(cur);

    return winner;
}

int main()
{
    int n, m;

    printf("Nhap N: ");
    scanf("%d", &n);

    printf("Nhap M: ");
    scanf("%d", &m);

    josephus(n, m);

    return 0;
}