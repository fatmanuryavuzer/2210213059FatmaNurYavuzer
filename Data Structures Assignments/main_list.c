#include <stdio.h>
#include <stdlib.h>

/* =========================
   1) SINGLY LINKED LIST
   - Recursive delete all
   - Print
   ========================= */

typedef struct SNode {
    int data;
    struct SNode* next;
} SNode;

SNode* s_create_node(int x) {
    SNode* n = (SNode*)malloc(sizeof(SNode));
    if (!n) { perror("malloc"); exit(1); }
    n->data = x;
    n->next = NULL;
    return n;
}

void s_push_back(SNode** head, int x) {
    SNode* n = s_create_node(x);
    if (*head == NULL) {
        *head = n;
        return;
    }
    {
        SNode* cur = *head;
        while (cur->next) cur = cur->next;
        cur->next = n;
    }
}

void s_print(const SNode* head) {
    const SNode* cur = head;
    printf("[");
    while (cur) {
        printf("%d", cur->data);
        cur = cur->next;
        if (cur) printf(" -> ");
    }
    printf("]\n");
}

/* Linked listteki tüm elemanlarý recursive silme */
void s_delete_all_recursive(SNode* head) {
    if (head == NULL) return;
    s_delete_all_recursive(head->next);
    free(head);
}

/* =========================
   2) DOUBLY LINKED LIST
   - Append (sona ekleme)
   - Insert between (araya ekleme)
   - Print forward/backward
   - Free
   ========================= */

typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

DNode* d_create_node(int x) {
    DNode* n = (DNode*)malloc(sizeof(DNode));
    if (!n) { perror("malloc"); exit(1); }
    n->data = x;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

/* Double linked listte listenin sonuna eleman ekleme */
void d_append(DNode** head, int x) {
    DNode* n = d_create_node(x);

    if (*head == NULL) {
        *head = n;
        return;
    }

    {
        DNode* tail = *head;
        while (tail->next) tail = tail->next;
        tail->next = n;
        n->prev = tail;
    }
}

/* Yardýmcý: index’teki düðümü bul (0-based). Yoksa NULL */
DNode* d_get_at(DNode* head, int index) {
    int i = 0;
    DNode* cur = head;
    while (cur && i < index) {
        cur = cur->next;
        i++;
    }
    return cur;
}

/* Double linked listte araya ekleme: after düðümünden SONRA ekler */
void d_insert_after(DNode* after, int x) {
    DNode* n;

    if (after == NULL) return;

    n = d_create_node(x);

    n->prev = after;
    n->next = after->next;

    if (after->next) {
        after->next->prev = n;
    }
    after->next = n;
}

/* Alternatif: index’e göre araya ekleme
   - index 0: baþa ekler
   - index >= len: sona ekler */
void d_insert_at(DNode** head, int index, int x) {
    if (index <= 0 || *head == NULL) {
        /* baþa ekle */
        DNode* n = d_create_node(x);
        n->next = *head;
        if (*head) (*head)->prev = n;
        *head = n;
        return;
    }

    {
        DNode* cur = d_get_at(*head, index);
        if (cur == NULL) {
            /* index listeden büyükse sona ekle */
            d_append(head, x);
            return;
        }

        /* cur index’teki düðüm; onun ÖNÜNE ekle (araya) */
        {
            DNode* n = d_create_node(x);
            n->next = cur;
            n->prev = cur->prev;

            if (cur->prev) cur->prev->next = n;
            cur->prev = n;
        }
    }
}

void d_print_forward(const DNode* head) {
    const DNode* cur = head;
    printf("[");
    while (cur) {
        printf("%d", cur->data);
        cur = cur->next;
        if (cur) printf(" <-> ");
    }
    printf("]\n");
}

void d_print_backward(const DNode* head) {
    const DNode* tail;
    const DNode* cur;

    if (!head) { printf("[]\n"); return; }

    tail = head;
    while (tail->next) tail = tail->next;

    printf("[");
    cur = tail;
    while (cur) {
        printf("%d", cur->data);
        cur = cur->prev;
        if (cur) printf(" <-> ");
    }
    printf("]\n");
}

void d_free(DNode* head) {
    DNode* cur = head;
    while (cur) {
        DNode* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
}

/* =========================
   3) CIRCULAR SINGLY LIST
   ========================= */

typedef struct CNode {
    int data;
    struct CNode* next;
} CNode;

CNode* c_create_node(int x) {
    CNode* n = (CNode*)malloc(sizeof(CNode));
    if (!n) { perror("malloc"); exit(1); }
    n->data = x;
    n->next = NULL;
    return n;
}

void c_push_back(CNode** head, int x) {
    CNode* n = c_create_node(x);

    if (*head == NULL) {
        *head = n;
        n->next = n;
        return;
    }

    {
        CNode* tail = *head;
        while (tail->next != *head) tail = tail->next;
        tail->next = n;
        n->next = *head;
    }
}

void c_print_n(const CNode* head, int count) {
    int i;
    const CNode* cur;

    printf("[");
    if (!head || count <= 0) { printf("]\n"); return; }

    cur = head;
    for (i = 0; i < count; i++) {
        printf("%d", cur->data);
        cur = cur->next;
        if (i != count - 1) printf(" -> ");
    }
    printf("]\n");
}

void c_free(CNode* head) {
    CNode* cur;
    if (!head) return;

    cur = head->next;
    while (cur != head) {
        CNode* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    free(head);
}

/* =========================
   4) SORT (Bubble)
   ========================= */

static void swap_int(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

void s_bubble_sort(SNode* head) {
    int swapped;

    if (!head) return;

    do {
        SNode* cur = head;
        swapped = 0;

        while (cur->next) {
            if (cur->data > cur->next->data) {
                swap_int(&cur->data, &cur->next->data);
                swapped = 1;
            }
            cur = cur->next;
        }
    } while (swapped);
}

void c_bubble_sort(CNode* head) {
    int swapped;

    if (!head || head->next == head) return;

    do {
        CNode* cur = head;
        swapped = 0;

        while (cur->next != head) {
            if (cur->data > cur->next->data) {
                swap_int(&cur->data, &cur->next->data);
                swapped = 1;
            }
            cur = cur->next;
        }
    } while (swapped);
}

/* =========================
   DEMO MAIN
   ========================= */

int main(void) {
    int i;
    int arr[5] = {7, 3, 9, 1, 5};

    printf("=== DLL: sona ekleme + araya ekleme ===\n");
    {
        DNode* dhead = NULL;
        d_append(&dhead, 10);
        d_append(&dhead, 30);
        d_append(&dhead, 40);
        d_print_forward(dhead);

        d_insert_at(&dhead, 1, 20); /* 10 20 30 40 */
        d_print_forward(dhead);

        {
            DNode* node30 = d_get_at(dhead, 2); /* 30 */
            d_insert_after(node30, 35);         /* 10 20 30 35 40 */
        }
        d_print_forward(dhead);
        printf("Backward: ");
        d_print_backward(dhead);

        d_free(dhead);
    }

    printf("\n=== SLL: recursive delete all ===\n");
    {
        SNode* shead = NULL;
        s_push_back(&shead, 5);
        s_push_back(&shead, 1);
        s_push_back(&shead, 4);
        s_print(shead);

        s_delete_all_recursive(shead);
        shead = NULL;
        printf("Liste silindi.\n");
    }

    printf("\n=== Normal vs Circular: bubble sort gozlem ===\n");
    {
        SNode* s2 = NULL;
        CNode* chead = NULL;

        for (i = 0; i < 5; i++) s_push_back(&s2, arr[i]);
        printf("Normal before: ");
        s_print(s2);
        s_bubble_sort(s2);
        printf("Normal after : ");
        s_print(s2);

        for (i = 0; i < 5; i++) c_push_back(&chead, arr[i]);
        printf("Circular before (5): ");
        c_print_n(chead, 5);
        c_bubble_sort(chead);
        printf("Circular after  (5): ");
        c_print_n(chead, 5);

        s_delete_all_recursive(s2);
        c_free(chead);
    }

    return 0;
}

