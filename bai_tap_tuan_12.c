#include <stdio.h>

void printArray(int a[], int n) {
    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && a[left] > a[largest])
        largest = left;

    if(right < n && a[right] > a[largest])
        largest = right;

    if(largest != i) {
        swap(&a[i], &a[largest]);

        printf("Doi %d va %d: ", a[largest], a[i]);
        printArray(a, n);

        heapify(a, n, largest);
    }
}

void buildMaxHeap(int a[], int n) {
    for(int i = n/2 - 1; i >= 0; i--) {
        printf("\nVun dong tai i = %d\n", i);
        heapify(a, n, i);
    }
}

int main() {
    int a[] = {11, 54, 32, 106, 38, 78, 203, 16, 84, 17, 39, 15};
    int n = sizeof(a)/sizeof(a[0]);

    printf("Mang ban dau:\n");
    printArray(a, n);

    printf("\n=== BUILD MAX HEAP ===\n");

    buildMaxHeap(a, n);

    printf("\nMax Heap:\n");
    printArray(a, n);

    return 0;
}