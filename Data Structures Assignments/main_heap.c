#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int size;   /* kaç eleman var */
    int isMin;  /* 0 = MaxHeap, 1 = MinHeap */
} Heap;

/* parent ile child yer deðiþtirmeli mi? */
int needSwap(Heap *h, int parentIndex, int childIndex) {
    if (h->isMin) {
        /* MinHeap: parent > child ise swap gerekir */
        return h->data[parentIndex] > h->data[childIndex];
    } else {
        /* MaxHeap: parent < child ise swap gerekir */
        return h->data[parentIndex] < h->data[childIndex];
    }
}

void heapifyUp(Heap *h, int index) {
    int i = index;
    int parent;
    int temp;

    while (i > 0) {
        parent = (i - 1) / 2;

        if (!needSwap(h, parent, i))
            break;

        /* swap */
        temp = h->data[parent];
        h->data[parent] = h->data[i];
        h->data[i] = temp;

        i = parent;
    }
}

void heapifyDown(Heap *h, int index) {
    int i = index;
    int left, right, best;
    int temp;
    int n = h->size;

    while (1) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        best = i;

        if (left < n && needSwap(h, best, left))
            best = left;
        if (right < n && needSwap(h, best, right))
            best = right;

        if (best == i)
            break;

        /* swap */
        temp = h->data[i];
        h->data[i] = h->data[best];
        h->data[best] = temp;

        i = best;
    }
}

void initHeap(Heap *h, int isMin) {
    h->size = 0;
    h->isMin = isMin;
}

void insertHeap(Heap *h, int value) {
    if (h->size >= MAX) {
        printf("Heap dolu!\n");
        return;
    }
    h->data[h->size] = value;
    heapifyUp(h, h->size);
    h->size++;
}

int getRoot(Heap *h, int *ok) {
    if (h->size == 0) {
        printf("Heap bos!\n");
        *ok = 0;
        return 0;
    }
    *ok = 1;
    return h->data[0];
}

void deleteRoot(Heap *h) {
    if (h->size == 0) {
        printf("Heap zaten bos!\n");
        return;
    }
    h->data[0] = h->data[h->size - 1];
    h->size--;
    if (h->size > 0)
        heapifyDown(h, 0);
}

void printHeap(Heap *h) {
    int i;
    if (h->size == 0) {
        printf("(bos)\n");
        return;
    }
    for (i = 0; i < h->size; i++)
        printf("%d ", h->data[i]);
    printf("\n");
}

int main() {
    Heap maxHeap;
    Heap minHeap;
    int choice;
    int value;
    int ok;
    int running = 1;

    initHeap(&maxHeap, 0); /* 0 = MaxHeap */
    initHeap(&minHeap, 1); /* 1 = MinHeap */

    /* örnek birkaç eleman ekleyelim */
    insertHeap(&maxHeap, 10);
    insertHeap(&maxHeap, 4);
    insertHeap(&maxHeap, 15);
    insertHeap(&maxHeap, 7);

    insertHeap(&minHeap, 10);
    insertHeap(&minHeap, 4);
    insertHeap(&minHeap, 15);
    insertHeap(&minHeap, 7);

    while (running) {
        printf("\n===== HEAP MENU =====\n");
        printf("1) MaxHeap'e eleman ekle\n");
        printf("2) MaxHeap root'u (max) goster\n");
        printf("3) MaxHeap root'u sil\n");
        printf("4) MaxHeap yazdir\n");
        printf("5) MinHeap'e eleman ekle\n");
        printf("6) MinHeap root'u (min) goster\n");
        printf("7) MinHeap root'u sil\n");
        printf("8) MinHeap yazdir\n");
        printf("0) Cikis\n");
        printf("Secim: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Eklenecek deger: ");
            scanf("%d", &value);
            insertHeap(&maxHeap, value);
            break;
        case 2:
            value = getRoot(&maxHeap, &ok);
            if (ok) printf("MaxHeap root (max): %d\n", value);
            break;
        case 3:
            deleteRoot(&maxHeap);
            break;
        case 4:
            printf("MaxHeap: ");
            printHeap(&maxHeap);
            break;
        case 5:
            printf("Eklenecek deger: ");
            scanf("%d", &value);
            insertHeap(&minHeap, value);
            break;
        case 6:
            value = getRoot(&minHeap, &ok);
            if (ok) printf("MinHeap root (min): %d\n", value);
            break;
        case 7:
            deleteRoot(&minHeap);
            break;
        case 8:
            printf("MinHeap: ");
            printHeap(&minHeap);
            break;
        case 0:
            running = 0;
            break;
        default:
            printf("Gecersiz secim!\n");
        }
    }

    return 0;
}

